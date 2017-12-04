#ifndef METEOBOX_IOBOARD_H
#define METEOBOX_IOBOARD_H

#include <Wire.h>
#include "MCP23017.h"

class IOBoard
{
public:
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
	
private:
	MCP23017				_mcp;
	bool					_isConnected;
	bool					_sensorValues[IOBoard::POSITION_COUNT];
	IOBoard::Position		_lastSensorPosition;
	
public:
	IOBoard();
	
	void					startUp();
	void					shutDown();
	
	void					update();
	bool					isConnected() const;
	IOBoard::Position		lastSensorPosition() const;
};

#endif
