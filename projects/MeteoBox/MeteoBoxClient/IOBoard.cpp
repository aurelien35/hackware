#include "IOBoard.h"

IOBoard::IOBoard()
	: _mcp				(0x20)
	, _isConnected		(false)
	, _sensorValues		(0)
	, _sensorPosition	(MeteoBoxClient::POSITION_UNKNOW)
{
}
//
bool IOBoard::startUp()
{
	Serial.println("IOBoard::startUp...");
	
	// Reset default values
	_isConnected	= false;
	_sensorValues	= 0;
	_sensorPosition	= MeteoBoxClient::POSITION_UNKNOW;
	
	// Power on the board
	digitalWrite(MeteoBoxClient::PIN_IO_BOARD_POWER_ON, HIGH);
	delay(500);
	
	// Start I2C
	Wire.begin(MeteoBoxClient::PIN_SDA, MeteoBoxClient::PIN_SCL);
	delay(500);
	
	// Test connexion and configuration
	if (_mcp.exists() == true)
	{
		if (_mcp.setMode(MCP23017::PORT_A, MCP23017::INPUT_MODE) == true)
		{
			if (_mcp.setMode(MCP23017::PORT_B, MCP23017::OUTPUT_MODE) == true)
			{
				_isConnected = true;
				Serial.println("IOBoard::startUp : ok !");
				return true;
			}
		}
	}
	
	Serial.println("IOBoard::startUp : error !");
	return false;
}
//
void IOBoard::shutDown()
{
	Serial.println("IOBoard::shutDown...");

	digitalWrite(MeteoBoxClient::PIN_IO_BOARD_POWER_ON, LOW);
	delay(500);
	_isConnected = false;

	Serial.println("IOBoard::shutDown : ok !");
}
//
bool IOBoard::update()
{
	_sensorValues = 0;
	_sensorPosition = MeteoBoxClient::POSITION_UNKNOW;
	
	if (_isConnected == false)
	{
		Serial.println("IOBoard::update : Not connected");
		_mcp.debugDump();
		return false;
	}

	// Read sensors
	int newSensorsValues = _mcp.getGPIO(MCP23017::PORT_A);
	if (newSensorsValues < 0)
	{
		Serial.println("IOBoard::update : read values error");
		_mcp.debugDump();
		return false;
	}
	
	// Write LEDS
	if (_mcp.setGPIO(MCP23017::PORT_A, (uint8_t) newSensorsValues) == false)
	{
		Serial.println("IOBoard::update : write values error");
		_mcp.debugDump();
		return false;
	}

	// Store values	
	_sensorValues = (uint8_t) newSensorsValues;
	
	if (bitRead(_sensorValues, MeteoBoxClient::POSITION_1) == true) _sensorPosition = MeteoBoxClient::POSITION_1;
	else if (bitRead(_sensorValues, MeteoBoxClient::POSITION_2) == true) _sensorPosition = MeteoBoxClient::POSITION_2;
	else if (bitRead(_sensorValues, MeteoBoxClient::POSITION_3) == true) _sensorPosition = MeteoBoxClient::POSITION_3;
	else if (bitRead(_sensorValues, MeteoBoxClient::POSITION_4) == true) _sensorPosition = MeteoBoxClient::POSITION_4;
	else if (bitRead(_sensorValues, MeteoBoxClient::POSITION_5) == true) _sensorPosition = MeteoBoxClient::POSITION_5;
	else if (bitRead(_sensorValues, MeteoBoxClient::POSITION_6) == true) _sensorPosition = MeteoBoxClient::POSITION_6;
	else if (bitRead(_sensorValues, MeteoBoxClient::POSITION_7) == true) _sensorPosition = MeteoBoxClient::POSITION_7;
	else if (bitRead(_sensorValues, MeteoBoxClient::POSITION_8) == true) _sensorPosition = MeteoBoxClient::POSITION_8;
	else _sensorPosition = MeteoBoxClient::POSITION_UNKNOW;
	
	Serial.print("IOBoard::update : values=");
	Serial.print(_sensorValues, BIN);
	Serial.print(" - position=");
	Serial.print(_sensorPosition);
	Serial.println("");
		
	return true;
}
//
bool IOBoard::isConnected() const
{
	return _isConnected;
}
//
MeteoBoxClient::Position IOBoard::sensorPosition() const
{
	return _sensorPosition;
}
