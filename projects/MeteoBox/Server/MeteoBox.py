# -*- coding: utf-8 -*-
import pprint
import urllib.parse
import urllib.request
import json
import bs4

# Global objects
PrettyPrinter = pprint.PrettyPrinter(indent=4)

# Main application : call the requested application if available
def application(env, start_response):
	parsedUrl = urllib.parse.urlparse(env["REQUEST_URI"])
	parsedQuery = urllib.parse.parse_qs(parsedUrl.query)
	
	# print("=================")
	# PrettyPrinter.pprint(env)
	# PrettyPrinter.pprint(parsedUrl)
	# PrettyPrinter.pprint(parsedQuery)
	# print("=================")

	if ( (parsedUrl.path == '/meteobox') and ('cityId' in parsedQuery) and (len(parsedQuery['cityId']) == 1) ):
		cityId = parsedQuery['cityId'][0]
		weather = scrapWeather(cityId)
		response = json.dumps(weather).encode('utf-8')
		# PrettyPrinter.pprint(weather)
		# print(response)
		start_response('200 OK', [('Content-Type','text/json')])
		return [response]
	
	start_response('444 No Response', [])
	return []

def scrapWeather(cityId):
	html            		= urllib.request.urlopen("http://www.meteofrance.com/previsions-meteo-france/" + cityId).read()
	soup            		= bs4.BeautifulSoup(html, "html.parser")
	forecastElements  	 	= soup.find("div", attrs={"class":"prevision-ville"})
	hourlyForecastElements 	= forecastElements.findAll("ul",attrs={"class":"prevision-horaire"}, limit=2, recursive=False)

	result				= {}
	result["today"]		= extractForecast(hourlyForecastElements[0])
	result["tomorrow"]	= extractForecast(hourlyForecastElements[1])
	return result

	
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
					if (windSpeed == '< 5'):
						windSpeed = '0'

					result["clouds"]			= cloudsStringToValue(clouds)
					result["temperatureStart"]	= numberStringToValue(temperatureStart)
					result["temperatureEnd"]	= numberStringToValue(temperatureEnd)
					result["windSpeed"]			= numberStringToValue(windSpeed)
					result["rainProbability"]	= numberStringToValue(rainProbability)
	
	return result
