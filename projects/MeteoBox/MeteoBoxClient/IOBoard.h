#ifndef METEOBOX_IOBOARD_H
#define METEOBOX_IOBOARD_H

#include "MeteoBoxClient.h"
#include "MCP23017.h"

class IOBoard
{
private:
	MCP23017					_mcp;
	bool						_isConnected;
	uint8_t						_sensorValues;
	MeteoBoxClient::Position	_sensorPosition;
	
public:
	IOBoard();
	
	bool						startUp();
	void						shutDown();
	
	bool						update();
	bool						isConnected() const;
	MeteoBoxClient::Position	sensorPosition() const;
};

#endif
