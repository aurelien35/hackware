# -*- coding: utf-8 -*-

from urllib2 import urlopen
import bs4 as BeautifulSoup

def extractForecast(content):
	result = {}
	result["1h"]	= extractHourlyForecast(content, "1h")
	result["4h"]	= extractHourlyForecast(content, "4h")
	result["7h"]	= extractHourlyForecast(content, "7h")
	result["10h"]	= extractHourlyForecast(content, "10h")
	result["13h"]	= extractHourlyForecast(content, "13h")
	result["16h"]	= extractHourlyForecast(content, "16h")
	result["19h"]	= extractHourlyForecast(content, "19h")
	result["22h"]	= extractHourlyForecast(content, "22h")
	result["day"]	= extractHourlyForecast(content, "day")
	
	return result
	
def extractHourlyForecast(content, hourString):
	result = {}
	result["clouds"] = ""
	
	forecastsList = content.findAll("li", recursive=False)
	for forecast in forecastsList :
		if "tomorrow" not in forecast["class"] :
			time = forecast.find("time", attrs={"datetime":hourString})
			if time is not None :
				dayContent = forecast.find("div", attrs={"class":"content"})
				if dayContent is not None :
					result["clouds"] = dayContent.find("li", attrs={"class":"day-summary-label"}).text.strip()
			else :
				time = forecast.find("time")
				if time is None :
					dayContent = forecast.find("div", attrs={"class":"content"})
					if dayContent is not None :
						result["clouds"] = dayContent.find("li", attrs={"class":"day-summary-label"}).text.strip()
	
	return result

def scrapClouds(cityId, allValues):
	html            = urlopen("http://www.meteofrance.com/previsions-meteo-france/" + cityId).read()
	soup            = BeautifulSoup.BeautifulSoup(html, "html.parser")
	forecasts       = soup.find("div", attrs={"class":"prevision-ville"})
	hourlyForecasts = forecasts.findAll("ul",attrs={"class":"prevision-horaire"}, recursive=False)

	for hourlyForecast in hourlyForecasts :
		data = extractForecast(hourlyForecast)
		for entry in data:
			value = data[entry]["clouds"]
			if value is not "":
				if value not in allValues :
					allValues.append(value)
					print value
	
def main():
	allCloudsValues = []
	scrapClouds("bourg-en-bresse/01000", allCloudsValues)
	scrapClouds("laon/02000", allCloudsValues)
	scrapClouds("moulins/03000", allCloudsValues)
	scrapClouds("digne-les-bains/04000", allCloudsValues)
	scrapClouds("gap/05000", allCloudsValues)
	scrapClouds("nice/06000", allCloudsValues)
	scrapClouds("privas/07000", allCloudsValues)
	scrapClouds("charleville-mezieres/08000", allCloudsValues)
	scrapClouds("foix/09000", allCloudsValues)
	scrapClouds("troyes/10000", allCloudsValues)
	scrapClouds("carcassonne/11000", allCloudsValues)
	scrapClouds("rodez/12000", allCloudsValues)
	scrapClouds("marseille/13000", allCloudsValues)
	scrapClouds("caen/14000", allCloudsValues)
	scrapClouds("aurillac/15000", allCloudsValues)
	scrapClouds("angouleme/16000", allCloudsValues)
	scrapClouds("la-rochelle/17000", allCloudsValues)
	scrapClouds("bourges/18000", allCloudsValues)
	scrapClouds("tulle/19000", allCloudsValues)
	scrapClouds("dijon/21000", allCloudsValues)
	scrapClouds("saint-brieuc/22000", allCloudsValues)
	scrapClouds("gueret/23000", allCloudsValues)
	scrapClouds("perigueux/24000", allCloudsValues)
	scrapClouds("besancon/25000", allCloudsValues)
	scrapClouds("valence/26000", allCloudsValues)
	scrapClouds("evreux/27000", allCloudsValues)
	scrapClouds("chartres/28000", allCloudsValues)
	scrapClouds("quimper/29000", allCloudsValues)
	scrapClouds("nimes/30000", allCloudsValues)
	scrapClouds("toulouse/31000", allCloudsValues)
	scrapClouds("auch/32000", allCloudsValues)
	scrapClouds("bordeaux/33000", allCloudsValues)
	scrapClouds("montpellier/34000", allCloudsValues)
	scrapClouds("rennes/35000", allCloudsValues)
	scrapClouds("chateauroux/36000", allCloudsValues)
	scrapClouds("tours/37000", allCloudsValues)
	scrapClouds("grenoble/38000", allCloudsValues)
	scrapClouds("lons-le-saunier/39000", allCloudsValues)
	scrapClouds("mont-de-marsan/40000", allCloudsValues)
	scrapClouds("blois/41000", allCloudsValues)
	scrapClouds("saint-etienne/42000", allCloudsValues)
	scrapClouds("le-puy-en-velay/43000", allCloudsValues)
	scrapClouds("nantes/44000", allCloudsValues)
	scrapClouds("orleans/45000", allCloudsValues)
	scrapClouds("cahors/46000", allCloudsValues)
	scrapClouds("agen/47000", allCloudsValues)
	scrapClouds("mende/48000", allCloudsValues)
	scrapClouds("angers/49000", allCloudsValues)
	scrapClouds("saint-lo/50000", allCloudsValues)
	scrapClouds("chalons-en-champagne/51000", allCloudsValues)
	scrapClouds("chaumont/52000", allCloudsValues)
	scrapClouds("laval/53000", allCloudsValues)
	scrapClouds("nancy/54000", allCloudsValues)
	scrapClouds("bar-le-duc/55000", allCloudsValues)
	scrapClouds("vannes/56000", allCloudsValues)
	scrapClouds("metz/57000", allCloudsValues)
	scrapClouds("nevers/58000", allCloudsValues)
	scrapClouds("lille/59000", allCloudsValues)
	scrapClouds("beauvais/60000", allCloudsValues)
	scrapClouds("alencon/61000", allCloudsValues)
	scrapClouds("arras/62000", allCloudsValues)
	scrapClouds("clermont-ferrand/63000", allCloudsValues)
	scrapClouds("pau/64000", allCloudsValues)
	scrapClouds("tarbes/65000", allCloudsValues)
	scrapClouds("perpignan/66000", allCloudsValues)
	scrapClouds("strasbourg/67000", allCloudsValues)
	scrapClouds("colmar/68000", allCloudsValues)
	scrapClouds("lyon/69000", allCloudsValues)
	scrapClouds("vesoul/70000", allCloudsValues)
	scrapClouds("macon/71000", allCloudsValues)
	scrapClouds("le-mans/72000", allCloudsValues)
	scrapClouds("chambery/73000", allCloudsValues)
	scrapClouds("annecy/74000", allCloudsValues)
	scrapClouds("rouen/76000", allCloudsValues)
	scrapClouds("melun/77000", allCloudsValues)
	scrapClouds("versailles/78000", allCloudsValues)
	scrapClouds("niort/79000", allCloudsValues)
	scrapClouds("amiens/80000", allCloudsValues)
	scrapClouds("albi/81000", allCloudsValues)
	scrapClouds("montauban/82000", allCloudsValues)
	scrapClouds("toulon/83000", allCloudsValues)
	scrapClouds("avignon/84000", allCloudsValues)
	scrapClouds("la-roche-sur-yon/85000", allCloudsValues)
	scrapClouds("poitiers/86000", allCloudsValues)
	scrapClouds("limoges/87000", allCloudsValues)
	scrapClouds("epinal/88000", allCloudsValues)
	scrapClouds("auxerre/89000", allCloudsValues)
	scrapClouds("belfort/90000", allCloudsValues)
	scrapClouds("evry/91000", allCloudsValues)
	scrapClouds("nanterre/92000", allCloudsValues)
	scrapClouds("bobigny/93000", allCloudsValues)
	scrapClouds("creteil/94000", allCloudsValues)
	scrapClouds("cergy/95000", allCloudsValues)
	scrapClouds("bonneval-sur-arc/73480", allCloudsValues)
	scrapClouds("aussois/73500", allCloudsValues)
	scrapClouds("val-d-isere/73150", allCloudsValues)
	scrapClouds("saint-christophe-en-oisans/38520", allCloudsValues)
	scrapClouds("villar-d-arene/05480", allCloudsValues)
	scrapClouds("pelvoux/05340", allCloudsValues)
	scrapClouds("tignes/73320", allCloudsValues)
	
if __name__ == "__main__":
	main()
