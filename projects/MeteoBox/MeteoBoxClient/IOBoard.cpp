#include "IOBoard.h"

IOBoard::IOBoard()
	: _mcp					(0x20)
	, _isConnected			(false)
//	, _sensorValues			()
	, _lastSensorPosition	(IOBoard::POSITION_UNKNOW)
{
	// TODO : init pin 13 ?
	
	_sensorValues[POSITION_1] = false;
	_sensorValues[POSITION_2] = false;
	_sensorValues[POSITION_3] = false;
	_sensorValues[POSITION_4] = false;
	_sensorValues[POSITION_5] = false;
	_sensorValues[POSITION_6] = false;
	_sensorValues[POSITION_7] = false;
	_sensorValues[POSITION_8] = false;
}
void IOBoard::startUp()
{
}
void IOBoard::shutDown()
{
}
void IOBoard::update()
{
}
bool IOBoard::isConnected() const
{
	return _isConnected;
}
IOBoard::Position IOBoard::lastSensorPosition() const
{
	return _lastSensorPosition;
}
