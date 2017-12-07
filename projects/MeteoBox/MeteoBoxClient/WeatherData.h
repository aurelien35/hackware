/****************** UTF-8 Encoding Markér -- Do not remove ******************/

#ifndef METEOBOX_WEATHERDATA_H
#define METEOBOX_WEATHERDATA_H

#include "MeteoBoxClient.h"

class WeatherData
{
public:
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
	bool						_isValid;
	String						_serverResponse;
	WeatherData::Entry			_entries[MeteoBoxClient::POSITION_COUNT];
	
public:
	WeatherData();
	
	bool						download();
	bool						isValid() const;
	const WeatherData::Entry&	entry(MeteoBoxClient::Position position) const;

protected:
	bool						connectWifi();
	bool						downloadData();
	bool						parseData();
	bool						parseEntry(const JsonObject& data, MeteoBoxClient::Position position);
};

#endif
