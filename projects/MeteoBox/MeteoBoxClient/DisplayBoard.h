/****************** UTF-8 Encoding Markér -- Do not remove ******************/

#ifndef METEOBOX_DISPLAYBOARD_H
#define METEOBOX_DISPLAYBOARD_H

#include "MeteoBoxClient.h"
#include "WeatherData.h"
#include "ESP32Servo.h"

class DisplayBoard
{
private:
	ESP32Servo				_motorCloudsMainIcon;
	ESP32Servo				_motorCloudsDecoration;
	ESP32Servo				_motorCloudsRainProbability;
	ESP32Servo				_motorCloudsTemperatureStart;
	ESP32Servo				_motorCloudsTemperatureEnd;
	ESP32Servo				_motorCloudsWindSpeed;

public:
	DisplayBoard();
	
	void					shutDown();
	bool					displayData(const WeatherData::Entry& entry);
};

#endif
