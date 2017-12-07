/****************** UTF-8 Encoding Markér -- Do not remove ******************/

#include "WeatherData.h"

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
		digitalWrite(MeteoBoxClient::PIN_WIFI_STATUS, statusLed);
        Serial.print(".");

		statusLed = (statusLed==HIGH)?LOW:HIGH;
		tryLimit--;

        delay(100);
    }
    Serial.println(".");

	if (WiFi.status() == WL_CONNECTED)
	{
		digitalWrite(MeteoBoxClient::PIN_WIFI_STATUS, HIGH);
		return true;
	}

	digitalWrite(MeteoBoxClient::PIN_WIFI_STATUS, LOW);
	return false;
}
//
bool WeatherData::downloadData()
{
	digitalWrite(MeteoBoxClient::PIN_DATA_STATUS, LOW);

	bool result = false;
	HTTPClient client; 
  
	if (client.begin("http://www.hackware.radiopochard.com:4016/meteobox?cityId=rennes/35000") == false)
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
	digitalWrite(MeteoBoxClient::PIN_DATA_STATUS, (result==true)?HIGH:LOW);
	return result;
}
//
bool WeatherData::parseData()
{
	StaticJsonBuffer<JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + 8*JSON_OBJECT_SIZE(5) + 1000> jsonBuffer;
  
	JsonObject& root = jsonBuffer.parseObject(_serverResponse.c_str()); 
  
	if (   (root.success() == true)
		&& (root.containsKey("today") == true)
		&& (root.containsKey("tomorrow") == true) )
	{
		const JsonObject& today		= root["today"];
		const JsonObject& tomorrow	= root["tomorrow"];

		if (   (today.containsKey("7h") == true)
			&& (today.containsKey("10h") == true)
			&& (today.containsKey("13h") == true)
			&& (today.containsKey("16h") == true)
			&& (tomorrow.containsKey("7h") == true)
			&& (tomorrow.containsKey("10h") == true)
			&& (tomorrow.containsKey("13h") == true)
			&& (tomorrow.containsKey("16h") == true) )
		{
			if (   (parseEntry(today["7h"],		MeteoBoxClient::POSITION_1) == true)
				&& (parseEntry(today["10h"],	MeteoBoxClient::POSITION_2) == true)
				&& (parseEntry(today["13h"],	MeteoBoxClient::POSITION_3) == true)
				&& (parseEntry(today["16h"],	MeteoBoxClient::POSITION_4) == true)
				&& (parseEntry(tomorrow["7h"],	MeteoBoxClient::POSITION_5) == true)
				&& (parseEntry(tomorrow["10h"],	MeteoBoxClient::POSITION_6) == true)
				&& (parseEntry(tomorrow["13h"],	MeteoBoxClient::POSITION_7) == true)
				&& (parseEntry(tomorrow["16h"],	MeteoBoxClient::POSITION_8) == true) )
			{
				return true;
			}
		}
	}

	Serial.println("WeatherData::parseData : parseError");
	Serial.println("======= Response =======");
	Serial.println(_serverResponse.c_str());
	Serial.println("======================");
			
	return false;
}
//
bool WeatherData::parseEntry(const JsonObject& data, MeteoBoxClient::Position position)
{
	if (   (data.containsKey("clouds") == true)
		&& (data.containsKey("rainProbability") == true)
		&& (data.containsKey("temperatureEnd") == true)
		&& (data.containsKey("temperatureStart") == true)
		&& (data.containsKey("windSpeed") == true)
		&& (data["clouds"].is<int>() == true)
		&& (data["rainProbability"].is<int>() == true)
		&& (data["temperatureEnd"].is<int>() == true)
		&& (data["temperatureStart"].is<int>() == true)
		&& (data["windSpeed"].is<int>() == true) )
	{
		_entries[position].clouds			= data["clouds"];
		_entries[position].rainProbability	= data["rainProbability"];
		_entries[position].temperatureEnd	= data["temperatureEnd"];
		_entries[position].temperatureStart	= data["temperatureStart"];
		_entries[position].windSpeed		= data["windSpeed"];
		
		return true;
	}
	
	return false;
}
//
bool WeatherData::isValid() const
{
	return _isValid;
}
//
const WeatherData::Entry& WeatherData::entry(MeteoBoxClient::Position position) const
{
	return _entries[position];
}
