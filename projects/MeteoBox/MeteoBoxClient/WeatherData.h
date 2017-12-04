#ifndef METEOBOX_WEATHERDATA_H
#define METEOBOX_WEATHERDATA_H

#include "IOBoard.h"
#include <ArduinoJson.h>

class WeatherData
{
public:
	typedef enum
	{
		PIN_WIFI_STATUS  = 14
	} Pin;

	struct Entry
	{
		int clouds;
		int temperatureStart;
		int temperatureEnd;
		int windSpeed;
		int rainProbability;

		Entry();
	};
	
private:
	bool					_isValid;
	String					_serverResponse;
	WeatherData::Entry		_entries[IOBoard::POSITION_COUNT];
	
public:
	WeatherData();
	
	bool						download();
	bool						isValid() const;
	const WeatherData::Entry&	entry(IOBoard::Position position) const;

protected:
	bool						connectWifi();
	bool						downloadData();
	bool						parseData();
	void						parseEntry(const JsonObject& data, IOBoard::Position position);
};

#endif
