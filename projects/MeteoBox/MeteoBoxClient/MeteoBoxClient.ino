#include <Wire.h>
#include <esp_deep_sleep.h>
#include "IOBoard.h"

IOBoard ioBoard;

void setup()
{
	// Configure pins
	pinMode(IOBoard::PIN_POWER_ON, OUTPUT);
	esp_deep_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1);

	// Start serial
	Serial.begin(9600);
	while (!Serial);
	Serial.println("Serial comunication started");
	
	// Start IOBoard
	ioBoard.startUp();
}

void shutDown()
{
	Serial.println("Shutdown...");
  
	// Stop IOBoard
	ioBoard.shutDown();
	
	// Stop ESP32
	esp_deep_sleep_start();
}

void loop()
{
	for (int i=0; i<200; i++)
	{
		ioBoard.update();
		delay(100);
	}
  
	shutDown();
}


