/****************** UTF-8 Encoding Markér -- Do not remove ******************/

#include "MeteoBoxClient.h"
#include "IOBoard.h"
#include "DisplayBoard.h"
#include "WeatherData.h"


#include "ESP32Servo.h"
ESP32Servo				_servoTest;

void setup()
{
	// Configure pins
	pinMode(MeteoBoxClient::PIN_IO_BOARD_POWER_ON,		OUTPUT);
	pinMode(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON,	OUTPUT);
	pinMode(MeteoBoxClient::PIN_WIFI_STATUS,			OUTPUT);
	pinMode(MeteoBoxClient::PIN_DATA_STATUS,			OUTPUT);

	// Configure wake up
	esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, HIGH);

	// Write default values
	digitalWrite(MeteoBoxClient::PIN_IO_BOARD_POWER_ON,			LOW);
	digitalWrite(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON,	LOW);
	digitalWrite(MeteoBoxClient::PIN_WIFI_STATUS,				LOW);
	digitalWrite(MeteoBoxClient::PIN_DATA_STATUS,				LOW);

	// Start serial
	Serial.begin(9600);
	while (!Serial);
	Serial.println("Serial comunication started");

	_servoTest.attach(MeteoBoxClient::PIN_MOTOR_CLOUDS_MAIN_ICON,   ESP32Servo::CHANNEL_NOT_ATTACHED, 0, 180);
}

void loop()
{
	Serial.println("0");
	_servoTest.write(0);
	delay(5000);

	Serial.println("45");
	_servoTest.write(45);
	delay(5000);

	Serial.println("90");
	_servoTest.write(90);
	delay(5000);

	Serial.println("135");
	_servoTest.write(135);
	delay(5000);

	Serial.println("170");
	_servoTest.write(180);
	delay(5000);

/*
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

			displayBoard.displayData(weatherData.entry(currentPosition));

			// Extend time before sleep
			stopTime = currentTime + 60000;
		}

		delay(100);
		currentTime	= millis();
	}
  
	// Stop IOBoard
	ioBoard.shutDown();

	// Stop DisplayBoard
	displayBoard.shutDown();
	
	// Stop all outputs
	digitalWrite(MeteoBoxClient::PIN_IO_BOARD_POWER_ON,			LOW);
	digitalWrite(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON,	LOW);
	digitalWrite(MeteoBoxClient::PIN_WIFI_STATUS,				LOW);
	digitalWrite(MeteoBoxClient::PIN_DATA_STATUS,				LOW);

	// Stop ESP32
	Serial.println("Shutdown...");
	esp_deep_sleep_start();
	*/
}


