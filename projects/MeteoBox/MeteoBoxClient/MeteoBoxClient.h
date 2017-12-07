/****************** UTF-8 Encoding Markér -- Do not remove ******************/

#ifndef METEOBOX_CLIENT_H
#define METEOBOX_CLIENT_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <esp_deep_sleep.h>

class MeteoBoxClient
{
public:
	typedef enum
	{
		PIN_IO_BOARD_POWER_ON		= 2,
		PIN_DISPLAY_BOARD_POWER_ON	= 4,
		PIN_WIFI_STATUS  			= 18,
		PIN_DATA_STATUS  			= 19,
		PIN_SDA						= 21,
		PIN_SCL						= 22,
		PIN_MOTOR_CLOUDS_MAIN_ICON	= 25,
		PIN_MOTOR_CLOUDS_DECORATION	= 26,
		PIN_MOTOR_RAIN_PROBABILTY	= 27,
		PIN_MOTOR_TEMPERATURE_START	= 28,
		PIN_MOTOR_TEMPERATURE_END	= 29,
		PIN_MOTOR_WIND_SPEED		= 30
	} Pin;

	typedef enum
	{
		POSITION_UNKNOW  = -1,
		POSITION_1       =  0,
		POSITION_2       =  1,
		POSITION_3       =  2,
		POSITION_4       =  3,
		POSITION_5       =  4,
		POSITION_6       =  5,
		POSITION_7       =  6,
		POSITION_8       =  7,
		POSITION_COUNT   =  8
	} Position;
};

#endif
