/****************** UTF-8 Encoding Markér -- Do not remove ******************/

#include "DisplayBoard.h"

//		# 1       # Ensoleillé                    #   Soleil                         #   Rien
//		# 2       # Éclaircies                    #   Soleil + nuages                #   Rien
//		# 3       # Très nuageux                  #   Soleil + gros nuages           #   Rien
//		# 4       # Brume                         #   Soleil + brume                 #   Rien
//		# 5       # Pluie                         #   Soleil + gros nuages           #   Pluie
//		# 6       # Averses                       #   Soleil + nuages                #   Pluie
//		# 7       # Rares averses                 #   Soleil + nuages                #   Petite pluie
//		# 8       # Pluies éparses                #   Soleil + nuages                #   Petite pluie
//		# 9       # Pluie forte                   #   Soleil + gros nuages + pluie   #   Pluie
//		# 10      # Averses de neige              #   Soleil + nuages                #   Flocons
//		# 11      # Averses orageuses             #   Soleil + gros nuages           #   Pluie et orage
//		# 12      # Quelques flocons              #   Soleil                         #   Flocons
//		# 13      # Neige                         #   Soleil + nuages                #   Flocons
//		# 14      # Pluies orageuses              #   Soleil + gros nuages + pluie   #   Pluie et orage
//		# 15      # Pluie et neige                #   Soleil + gros nuages + pluie   #   Flocons
//		# 16      # Bancs de brouillard           #   Brume                          #   Rien
//		# 17      # Brouillard givrant            #   Brume                          #   Verglas
//		# 18      # Pluie verglaçante             #   Soleil + gros nuages + pluie   #   Verglas
//		# 19      # Ciel voilé                    #   Soleil + brume                 #   Rien
//		# 20      # Nuit claire                   #   Soleil                         #   Rien
//		
//		
//		#   Rien
//		#   Soleil                    
//		#   Brume
//		#   Soleil + nuages           
//		#   Soleil + gros nuages
//		#   Soleil + brume            
//		#   Soleil + gros nuages + pluie   
//		
//		#   Rien
//		#   Pluie
//		#   Petite pluie
//		#   Flocons
//		#   Pluie et orage
//		#   Verglas

DisplayBoard::DisplayBoard()
{
	if (   (_motorCloudsMainIcon.         attach(MeteoBoxClient::PIN_MOTOR_CLOUDS_MAIN_ICON,   ESP32Servo::CHANNEL_NOT_ATTACHED, 0, 360) == false)
		|| (_motorCloudsDecoration.       attach(MeteoBoxClient::PIN_MOTOR_CLOUDS_DECORATION,  ESP32Servo::CHANNEL_NOT_ATTACHED, 0, 360) == false)
		|| (_motorCloudsRainProbability.  attach(MeteoBoxClient::PIN_MOTOR_RAIN_PROBABILTY,    ESP32Servo::CHANNEL_NOT_ATTACHED, 0, 180) == false)
		|| (_motorCloudsTemperatureStart. attach(MeteoBoxClient::PIN_MOTOR_TEMPERATURE_START,  ESP32Servo::CHANNEL_NOT_ATTACHED, 0, 180) == false)
		|| (_motorCloudsTemperatureEnd.   attach(MeteoBoxClient::PIN_MOTOR_TEMPERATURE_END,    ESP32Servo::CHANNEL_NOT_ATTACHED, 0, 180) == false)
		|| (_motorCloudsWindSpeed.        attach(MeteoBoxClient::PIN_MOTOR_WIND_SPEED,         ESP32Servo::CHANNEL_NOT_ATTACHED, 0, 180) == false) )
	{
		Serial.println("DisplayBoard : servo pin attachment error");
	}
}
//
void DisplayBoard::shutDown()
{
	Serial.println("DisplayBoard::shutDown...");

	WeatherData::Entry invalidData;

	displayData(invalidData);

	Serial.println("DisplayBoard::shutDown : ok !");
}
//
bool DisplayBoard::displayData(const WeatherData::Entry& entry)
{
	int cloudsMainIconAngle		= 0;
	int cloudsDecorationAngle	= 0;
	int rainProbabilityAngle	= 0;
	int temperatureStartAngle	= 0;
	int temperatureEndAngle		= 0;
	int windSpeedAngle			= 0;

	// Send values to motors
	_motorCloudsMainIcon.write(cloudsMainIconAngle);
	_motorCloudsDecoration.write(cloudsDecorationAngle);
	_motorCloudsRainProbability.write(rainProbabilityAngle);
	_motorCloudsTemperatureStart.write(temperatureStartAngle);
	_motorCloudsTemperatureEnd.write(temperatureEndAngle);
	_motorCloudsWindSpeed.write(windSpeedAngle);

	// Power on the board
	digitalWrite(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON, HIGH);

	// Wait for motors to reach their position
	delay(3000);

	// Power off the board
	digitalWrite(MeteoBoxClient::PIN_DISPLAY_BOARD_POWER_ON, LOW);

	return false;
}
