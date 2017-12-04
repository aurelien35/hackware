#include "WeatherData.h"
#include <WiFi.h>
#include <HTTPClient.h>

WeatherData::Entry::Entry()
	: clouds			(-1)
	, temperatureStart	(-1)
	, temperatureEnd	(-1)
	, windSpeed			(-1)
	, rainProbability	(-1)
{
}
//
WeatherData::WeatherData()
	: _isValid			(false)
	, _serverResponse	()
	, _entries			()
{
}
//
bool WeatherData::download()
{
    Serial.println("WeatherData::download...");

	// Reset values
	_isValid = false;
	_serverResponse = String();

	// Connect
	Serial.println("WeatherData::download : connecting...");
	if (connectWifi() == false)
	{
		Serial.println("WeatherData::download : connection error !");
		return false;
	}
	Serial.print("WeatherData::download : connected ( ");Serial.print(WiFi.localIP());Serial.println(")");

	// Download
	Serial.println("WeatherData::download : downloading...");
	if (downloadData() == false)
	{
		Serial.println("WeatherData::download : download error !");
		return false;
	}
	Serial.println("WeatherData::download : download ok");

	// Parsing
	Serial.println("WeatherData::download : parsing...");
	if (parseData() == false)
	{
		Serial.println("WeatherData::download : parse error !");
		return false;
	}
	Serial.println("WeatherData::download : parse ok");

	_isValid = true;
	return true;
}
//
bool WeatherData::connectWifi()
{
    WiFi.begin("Numericable-e943", "odrelbibou");

	int statusLed = HIGH;
	int tryLimit = 200;		// 20s
    while (   (WiFi.status() != WL_CONNECTED)
		   && (tryLimit > 0) )
    {
		digitalWrite(WeatherData::PIN_WIFI_STATUS, statusLed);
        Serial.print(".");

		statusLed = (statusLed==HIGH)?LOW:HIGH;
		tryLimit--;

        delay(100);
    }
    Serial.println(".");

	if (WiFi.status() == WL_CONNECTED)
	{
		return true;
	}

	return false;
}
//
bool WeatherData::downloadData()
{
	bool result = false;
	HTTPClient client; 
  
	if (client.begin("http://echo.jsontest.com/key/value/one/two") == false)
	{
		Serial.println("WeatherData::downloadData : client connection failed");
	}
	else
	{
		int clientResultCode = client.GET();
		if (clientResultCode != 200)
		{
			Serial.print("WeatherData::downloadData : query failed (result=");
			Serial.print(clientResultCode);
			Serial.println(")");
			Serial.println("======= Response =======");
			Serial.println(client.getString());
			Serial.println("======================");
		}
		else
		{
			_serverResponse = client.getString();
			result = true;
		}
	}

	client.end();
	return result;
}
//
bool WeatherData::parseData()
{
	DynamicJsonBuffer jsonBuffer(JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + 8*JSON_OBJECT_SIZE(5) + 740);
  
	JsonObject& root = jsonBuffer.parseObject(_serverResponse.c_str()); 
  
	if (root.success() == true)
	{
		const JsonObject& today		= root["today"];
		const JsonObject& tomorrow	= root["tomorrow"];

		parseEntry(today["7h"],		IOBoard::POSITION_1);
		parseEntry(today["10h"],	IOBoard::POSITION_2);
		parseEntry(today["13h"],	IOBoard::POSITION_3);
		parseEntry(today["16h"],	IOBoard::POSITION_4);

		parseEntry(tomorrow["7h"],	IOBoard::POSITION_5);
		parseEntry(tomorrow["10h"],	IOBoard::POSITION_6);
		parseEntry(tomorrow["13h"],	IOBoard::POSITION_7);
		parseEntry(tomorrow["16h"],	IOBoard::POSITION_8);

		return true;
	}

	return false;
}
//
void WeatherData::parseEntry(const JsonObject& data, IOBoard::Position position)
{
	_entries[position].clouds			= data["clouds"];
	_entries[position].rainProbability	= data["rainProbability"];
	_entries[position].temperatureEnd	= data["temperatureEnd"];
	_entries[position].temperatureStart	= data["temperatureStart"];
	_entries[position].windSpeed		= data["windSpeed"];
}
//
bool WeatherData::isValid() const
{
	return _isValid;
}
//
const WeatherData::Entry& WeatherData::entry(IOBoard::Position position) const
{
	return _entries[position];
}
