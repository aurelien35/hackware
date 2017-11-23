# -*- coding: utf-8 -*-

from urllib2 import urlopen
import bs4 as BeautifulSoup

def extractForecast(content):
	result = {}
	result["7h"]	= extractHourlyForecast(content, "7h")
	result["10h"]	= extractHourlyForecast(content, "10h")
	result["13h"]	= extractHourlyForecast(content, "13h")
	result["16h"]	= extractHourlyForecast(content, "16h")
	
	return result
	
def extractHourlyForecast(content, hourString):
	result = {}
	result["clouds"]			= ""
	result["temperature"]		= ""
	result["windSpeed"]			= ""
	result["rainProbability"]	= ""
	
	forecastsList = content.findAll("li", recursive=False)
	# print "============="
	# print hourString
	for forecast in forecastsList :
		if "tomorrow" not in forecast["class"] :
			time = forecast.find("time", attrs={"datetime":hourString})
			if time is not None :
				dayContent = forecast.find("div", attrs={"class":"content"})
				if dayContent is not None :
					clouds			= dayContent.find("li", attrs={"class":"day-summary-label"}).text.strip()
					temperature		= dayContent.find("li", attrs={"class":"day-summary-tress-start"}).text.strip()
					windSpeed		= dayContent.find("li", attrs={"class":"day-summary-wind"}).text.strip()
					rainProbability	= dayContent.find("div", attrs={"class":"day-probabilities"}).div.ul.li.strong.text.strip()
					
					temperature		= temperature.replace("Ressenti ", "").replace(u"°C", "")
					windSpeed		= windSpeed.replace(" km/h", "")
					rainProbability	= rainProbability.replace(" %", "")
					
					result["clouds"]			= clouds
					result["temperature"]		= temperature
					result["windSpeed"]			= windSpeed
					result["rainProbability"]	= rainProbability
					
	# print "         clouds :", result["clouds"]
	# print "    temperature :", result["temperature"]
	# print "      windSpeed :", result["windSpeed"]
	# print "rainProbability :", result["rainProbability"]
	# print "============="
	
	return result

def main():
	html            = urlopen("http://www.meteofrance.com/previsions-meteo-france/rennes/35000").read()
	soup            = BeautifulSoup.BeautifulSoup(html, "html.parser")
	forecasts       = soup.find("div", attrs={"class":"prevision-ville"})
	hourlyForecasts = forecasts.findAll("ul",attrs={"class":"prevision-horaire"}, limit=2, recursive=False)

	todayForecast		= extractForecast(hourlyForecasts[0])
	tomorrowForecast	= extractForecast(hourlyForecasts[1])
	
	print "d0-7h-clouds:",todayForecast["7h"]["clouds"]
	print "d0-7h-temperature:",todayForecast["7h"]["temperature"]
	print "d0-7h-windSpeed:",todayForecast["7h"]["windSpeed"]
	print "d0-7h-rainProbability:",todayForecast["7h"]["rainProbability"]
	print "d0-10h-clouds:",todayForecast["10h"]["clouds"]
	print "d0-10h-temperature:",todayForecast["10h"]["temperature"]
	print "d0-10h-windSpeed:",todayForecast["10h"]["windSpeed"]
	print "d0-10h-rainProbability:",todayForecast["10h"]["rainProbability"]
	print "d0-13h-clouds:",todayForecast["13h"]["clouds"]
	print "d0-13h-temperature:",todayForecast["13h"]["temperature"]
	print "d0-13h-windSpeed:",todayForecast["13h"]["windSpeed"]
	print "d0-13h-rainProbability:",todayForecast["13h"]["rainProbability"]
	print "d0-16h-clouds:",todayForecast["16h"]["clouds"]
	print "d0-16h-temperature:",todayForecast["16h"]["temperature"]
	print "d0-16h-windSpeed:",todayForecast["16h"]["windSpeed"]
	print "d0-16h-rainProbability:",todayForecast["16h"]["rainProbability"]

	print "d1-7h-clouds:",tomorrowForecast["7h"]["clouds"]
	print "d1-7h-temperature:",tomorrowForecast["7h"]["temperature"]
	print "d1-7h-windSpeed:",tomorrowForecast["7h"]["windSpeed"]
	print "d1-7h-rainProbability:",tomorrowForecast["7h"]["rainProbability"]
	print "d1-10h-clouds:",tomorrowForecast["10h"]["clouds"]
	print "d1-10h-temperature:",tomorrowForecast["10h"]["temperature"]
	print "d1-10h-windSpeed:",tomorrowForecast["10h"]["windSpeed"]
	print "d1-10h-rainProbability:",tomorrowForecast["10h"]["rainProbability"]
	print "d1-13h-clouds:",tomorrowForecast["13h"]["clouds"]
	print "d1-13h-temperature:",tomorrowForecast["13h"]["temperature"]
	print "d1-13h-windSpeed:",tomorrowForecast["13h"]["windSpeed"]
	print "d1-13h-rainProbability:",tomorrowForecast["13h"]["rainProbability"]
	print "d1-16h-clouds:",tomorrowForecast["16h"]["clouds"]
	print "d1-16h-temperature:",tomorrowForecast["16h"]["temperature"]
	print "d1-16h-windSpeed:",tomorrowForecast["16h"]["windSpeed"]
	print "d1-16h-rainProbability:",tomorrowForecast["16h"]["rainProbability"]
	
if __name__ == "__main__":
	main()
