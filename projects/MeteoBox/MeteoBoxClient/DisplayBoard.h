#ifndef METEOBOX_DISPLAYBOARD_H
#define METEOBOX_DISPLAYBOARD_H

#include "MeteoBoxClient.h"
#include "WeatherData.h"

class DisplayBoard
{
public:
	DisplayBoard();
	
	void					shutDown();
	bool					displayData(const WeatherData::Entry& entry);
};

#endif
