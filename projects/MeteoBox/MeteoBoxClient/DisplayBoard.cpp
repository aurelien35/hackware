#include "DisplayBoard.h"

DisplayBoard::DisplayBoard()
{
}
//
void DisplayBoard::shutDown()
{
	Serial.println("DisplayBoard::shutDown...");

	// Power on the board
	digitalWrite(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON, HIGH);
	delay(100);

	// TODO : display invalid data

	// Power off the board
	digitalWrite(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON, LOW);
	delay(100);

	Serial.println("DisplayBoard::shutDown : ok !");
}
//
bool DisplayBoard::displayData(const WeatherData::Entry& entry)
{
	// Power on the board
	digitalWrite(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON, HIGH);
	delay(100);

	// TODO : display data

	// Power off the board
	digitalWrite(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON, LOW);
	delay(100);

	return false;
}
