# -*- coding: utf-8 -*-

# Ensoleillé                    #   Soleil                    #   Rien
# Éclaircies                    #   Soleil + nuages           #   Rien
# Très nuageux                  #   Nuages                    #   Rien
# Brume                         #   Soleil + brume            #   Rien
# Pluie                         #   Soleil + nuages           #   Pluie
# Averses                       #   Soleil + nuages           #   Pluie
# Rares averses                 #   Soleil + nuages           #   Petite pluie
# Pluies éparses                #   Soleil + nuages           #   Petite pluie
# Pluie forte                   #   Soleil + nuages + pluie   #   Pluie
# Averses de neige              #   Soleil + nuages           #   Flocons
# Averses orageuses             #   Soleil + nuages           #   Pluie et orage
# Quelques flocons              #   Soleil                    #   Flocons
# Neige                         #   Soleil + nuages           #   Flocons
# Pluies orageuses              #   Soleil + nuages + pluie   #   Pluie et orage
# Pluie et neige                #   Soleil + nuages + pluie   #   Flocons
# Bancs de brouillard           #   Brume                     #   Rien
# Brouillard givrant            #   Brume                     #   Verglas
# Pluie verglaçante             #   Soleil + nuages + pluie   #   Verglas
# Ciel voilé                    #   Soleil + brume            #   Rien
# Nuit claire                   #   Soleil                    #   Rien


#   Soleil                    
#   Soleil + nuages           
#   Nuages                    
#   Soleil + brume            
#   Soleil + nuages + pluie   

#   Rien
#   Pluie
#   Petite pluie
#   Flocons
#   Pluie et orage
#   Verglas

from urllib2 import urlopen
import bs4 as BeautifulSoup
import json

def cloudsStringToValue(cloudsString):
	if (cloudsString == u"Ensoleillé"):				return 1
	elif (cloudsString == u"Éclaircies"):			return 2
	elif (cloudsString == u"Très nuageux"):			return 3
	elif (cloudsString == u"Brume"):			    return 4
	elif (cloudsString == u"Pluie"):			    return 5
	elif (cloudsString == u"Averses"):			    return 6
	elif (cloudsString == u"Rares averses"):		return 7
	elif (cloudsString == u"Pluies éparses"):		return 8
	elif (cloudsString == u"Pluie forte"):			return 9
	elif (cloudsString == u"Averses de neige"):		return 10
	elif (cloudsString == u"Averses orageuses"):	return 11
	elif (cloudsString == u"Quelques flocons"):		return 12
	elif (cloudsString == u"Neige"):			    return 13
	elif (cloudsString == u"Pluies orageuses"):		return 14
	elif (cloudsString == u"Pluie et neige"):		return 15
	elif (cloudsString == u"Bancs de brouillard"):	return 16
	elif (cloudsString == u"Brouillard givrant"):	return 17
	elif (cloudsString == u"Pluie verglaçante"):	return 18
	elif (cloudsString == u"Ciel voilé"):			return 19
	elif (cloudsString == u"Nuit claire"):			return 20
	return -1
	
def numberStringToValue(numberString):
	try:
		return int(numberString)
	except ValueError:
		return -1


def extractForecast(content):
	result = {}
	result["7h"]	= extractHourlyForecast(content, "7h")
	result["10h"]	= extractHourlyForecast(content, "10h")
	result["13h"]	= extractHourlyForecast(content, "13h")
	result["16h"]	= extractHourlyForecast(content, "16h")
	
	return result
	
def extractHourlyForecast(content, hourString):
	result = {}
	result["clouds"]			= -1
	result["temperatureStart"]	= -1
	result["temperatureEnd"]	= -1
	result["windSpeed"]			= -1
	result["rainProbability"]	= -1
	
	forecastsList = content.findAll("li", recursive=False)
	# print "============="
	# print hourString
	for forecast in forecastsList :
		if "tomorrow" not in forecast["class"] :
			time = forecast.find("time", attrs={"datetime":hourString})
			if time is not None :
				dayContent = forecast.find("div", attrs={"class":"content"})
				if dayContent is not None :
					temperatureStart	= dayContent.find("li", attrs={"class":"day-summary-tress-start"}).text.strip()
					temperatureEnd		= dayContent.find("li", attrs={"class":"day-summary-tress-end"}).text.strip()
					windSpeed			= dayContent.find("li", attrs={"class":"day-summary-wind"}).text.strip()
					rainProbability		= dayContent.find("div", attrs={"class":"day-probabilities"}).div.ul.li.strong.text.strip()
					clouds				= dayContent.find("li", attrs={"class":"day-summary-label"}).text.strip()
					
					temperatureStart	= temperatureStart.replace("Ressenti ", "").replace(u"°C", "")
					temperatureEnd		= temperatureEnd.replace("Ressenti ", "").replace(u"°C", "")
					windSpeed			= windSpeed.replace(" km/h", "")
					rainProbability		= rainProbability.replace(" %", "")

					result["clouds"]			= cloudsStringToValue(clouds)
					result["temperatureStart"]	= numberStringToValue(temperatureStart)
					result["temperatureEnd"]	= numberStringToValue(temperatureEnd)
					result["windSpeed"]			= numberStringToValue(windSpeed)
					result["rainProbability"]	= numberStringToValue(rainProbability)
	
	return result

def scrapWeather(cityId):
	html            		= urlopen("http://www.meteofrance.com/previsions-meteo-france/" + cityId).read()
	soup            		= BeautifulSoup.BeautifulSoup(html, "html.parser")
	forecastElements  	 	= soup.find("div", attrs={"class":"prevision-ville"})
	hourlyForecastElements 	= forecastElements.findAll("ul",attrs={"class":"prevision-horaire"}, limit=2, recursive=False)

	result				= {}
	result["today"]		= extractForecast(hourlyForecastElements[0])
	result["tomorrow"]	= extractForecast(hourlyForecastElements[1])
	return result
	
if __name__ == "__main__":
	forecast = scrapWeather("rennes/35000")
	print json.dumps(forecast, indent=4, sort_keys=True)
