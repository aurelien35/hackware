#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid      = "Numericable-e943";
const char* password  = "odrelbibou";

struct Weather
{
  bool success;
  String errorMessage;
  String response;
  String one;
  String two;
//  int value;
} weather;

void setup()
{
    Serial.begin(115200);
    delay(10);

    Serial.println("===");
    Serial.print("Connecting to SSID : ");
    Serial.println(ssid);
    Serial.println("===");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("===");
    Serial.println("WiFi connected");
    Serial.print("IP address : ");
    Serial.println(WiFi.localIP());
    Serial.println("===");
}

void parseWeather()
{
  DynamicJsonBuffer jsonBuffer(JSON_OBJECT_SIZE(4) + 2000);
  
  JsonObject& root = jsonBuffer.parseObject(weather.response.c_str()); 
  
  if (root.success() == false)
  {
    weather.success       = false;
    weather.errorMessage  = "Parsing error";
  }
  else
  {
    weather.success       = true;
    weather.errorMessage  = "";
    weather.one           = root["one"].asString();
    weather.two           = root["two"].asString();
//  int weather.value     = root["Value"];
  }
}

void queryWeather(String url)
{
  HTTPClient client; 
  
  if (client.begin(url.c_str()) == false)
  {
    weather.success       = false;
    weather.errorMessage  = "Connection failed";
    weather.response      = "";
  }
  else
  {
    int result = client.GET();
    if (result != 200)
    {
      weather.success       = false;
      weather.errorMessage  = String("Query failed : ") + result;
      weather.response      = client.getString();
    }
    else
    {
      weather.response = client.getString();
      parseWeather();
    }
  }
  client.end();
}
  
void loop()
{
  queryWeather("http://echo.jsontest.com/key/value/one/two");
  
  Serial.println("===");
  Serial.println("Response :");
  Serial.println(weather.response);
  Serial.println("===");
  
  if (weather.success == true)
  {
    Serial.println("===");
    Serial.print("one : "); Serial.println(weather.one);
    Serial.print("two : "); Serial.println(weather.two);
    Serial.println("===");
  }
  else
  {
    Serial.println("===");
    Serial.print("Error : "); Serial.println(weather.errorMessage);
    Serial.println("===");
  }
  Serial.println("===");
  
  delay(30000);
}

