#include "MeteoBoxClient.h"
#include "IOBoard.h"
#include "DisplayBoard.h"
#include "WeatherData.h"

void setup()
{
	// Configure pins
	pinMode(MeteoBoxClient::PIN_IO_BOARD_POWER_ON,		OUTPUT);
	pinMode(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON,	OUTPUT);
	pinMode(MeteoBoxClient::PIN_WIFI_STATUS,			OUTPUT);
	pinMode(MeteoBoxClient::PIN_DATA_STATUS,			OUTPUT);
	esp_deep_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1);

	// Start serial
	Serial.begin(9600);
	while (!Serial);
	Serial.println("Serial comunication started");
}

void loop()
{
	Serial.println("MeteoBox started");

	IOBoard ioBoard;
	DisplayBoard displayBoard;
	WeatherData weatherData;
	MeteoBoxClient::Position currentPosition = MeteoBoxClient::POSITION_UNKNOW;

	unsigned long currentTime	= millis();
	unsigned long stopTime		= currentTime + 60000;

	while (currentTime < stopTime)	// in case of overflow, no loop :-)
	{
		// Start IOBoard
		if (ioBoard.isConnected() == false)
		{
			ioBoard.startUp();
			delay(1000);
		}

		// Download data
		if (weatherData.isValid() == false)
		{
			weatherData.download();
			delay(1000);
		}

		// Display data
		if (   (ioBoard.isConnected() == true)
			&& (weatherData.isValid() == true)
			&& (ioBoard.update() == true)
			&& (currentPosition != ioBoard.sensorPosition()) )
		{
			currentPosition = ioBoard.sensorPosition();

			// TODO : display data
			
			delay(100);
			stopTime = currentTime + 60000;
		}

		currentTime	= millis();
	}
  
	// Stop IOBoard
	ioBoard.shutDown();
	
	// Stop ESP32
	Serial.println("Shutdown...");
	esp_deep_sleep_start();
}


