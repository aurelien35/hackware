#include "DisplayBoard.h"

DisplayBoard::DisplayBoard()
	: _isConnected		(false)
{
}
//
bool DisplayBoard::startUp()
{
	Serial.println("DisplayBoard::startUp...");
	
	// Reset default values
	_isConnected = false;
	
	// Power on the board
	digitalWrite(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON, HIGH);
	delay(500);
	
	_isConnected = true;
	Serial.println("DisplayBoard::startUp : ok !");
	return true;
}
//
void DisplayBoard::shutDown()
{
	Serial.println("DisplayBoard::shutDown...");
	digitalWrite(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON, LOW);
	_isConnected = false;
	Serial.println("DisplayBoard::shutDown : ok !");
}
//
bool DisplayBoard::isConnected() const
{
	return _isConnected;
}
//
bool DisplayBoard::update()
{
	return false;
}
