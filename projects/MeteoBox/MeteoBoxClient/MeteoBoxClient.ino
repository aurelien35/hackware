#include <Wire.h>
#include <esp_deep_sleep.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp;

#define PIN_SDA 21
#define PIN_SCL 22

#define POSITION_UNKNOW  -1
#define POSITION_1        0
#define POSITION_2        1
#define POSITION_3        2
#define POSITION_4        3
#define POSITION_5        4
#define POSITION_6        5
#define POSITION_7        6
#define POSITION_8        7

struct DataStruct
{
  int sliderPosition;

  DataStruct()
    : sliderPosition (POSITION_UNKNOW)
  {
  };
};

DataStruct data;

void startSerial()
{
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Start serial");
}

void startMCP()
{
  Serial.println("Start MCP...");
  Wire.begin(PIN_SDA, PIN_SCL);

  mcp.begin();                // use default address 0

  mcp.pinMode(0, INPUT);      //  mcp.pullUp(0, HIGH);  // turn on a 100K pullup internally
  mcp.pinMode(1, INPUT);
  mcp.pinMode(2, INPUT);
  mcp.pinMode(3, INPUT);
  mcp.pinMode(4, INPUT);
  mcp.pinMode(5, INPUT);
  mcp.pinMode(6, INPUT);
  mcp.pinMode(7, INPUT);
  mcp.pinMode(8, OUTPUT);
  mcp.pinMode(9, OUTPUT);
  mcp.pinMode(10, OUTPUT);
  mcp.pinMode(11, OUTPUT);
  mcp.pinMode(12, OUTPUT);
  mcp.pinMode(13, OUTPUT);
  mcp.pinMode(14, OUTPUT);
  mcp.pinMode(15, OUTPUT);

  Serial.println("MCP started !");
}

void readSensorPosition()
{
  if (mcp.digitalRead(0) == 0) data.sliderPosition = POSITION_1;
  else if (mcp.digitalRead(1) == 0) data.sliderPosition = POSITION_2;
  else if (mcp.digitalRead(2) == 0) data.sliderPosition = POSITION_3;
  else if (mcp.digitalRead(3) == 0) data.sliderPosition = POSITION_4;
  else if (mcp.digitalRead(4) == 0) data.sliderPosition = POSITION_5;
  else if (mcp.digitalRead(5) == 0) data.sliderPosition = POSITION_6;
  else if (mcp.digitalRead(6) == 0) data.sliderPosition = POSITION_7;
  else if (mcp.digitalRead(7) == 0) data.sliderPosition = POSITION_8;
  else data.sliderPosition = POSITION_UNKNOW;

  Serial.print("readSensorPosition : ");
  Serial.println(data.sliderPosition);
}

void updateDisplayPosition()
{
  mcp.digitalWrite(8, (data.sliderPosition == POSITION_1)?HIGH:LOW);
  mcp.digitalWrite(9,   (data.sliderPosition == POSITION_2)?HIGH:LOW);
  mcp.digitalWrite(10,  (data.sliderPosition == POSITION_3)?HIGH:LOW);
  mcp.digitalWrite(11,  (data.sliderPosition == POSITION_4)?HIGH:LOW);
  mcp.digitalWrite(12,  (data.sliderPosition == POSITION_5)?HIGH:LOW);
  mcp.digitalWrite(13,  (data.sliderPosition == POSITION_6)?HIGH:LOW);
  mcp.digitalWrite(14,  (data.sliderPosition == POSITION_7)?HIGH:LOW);
  mcp.digitalWrite(15,  (data.sliderPosition == POSITION_8)?HIGH:LOW);
}

void setup()
{
  esp_deep_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1);
  
  startSerial();
  startMCP();
}

void shutdown()
{
  Serial.println("Shutdown...");
  
  esp_deep_sleep_start();
}

void loop()
{
  for (int i=0; i<10; i++)
  {
    readSensorPosition();
    updateDisplayPosition();
    delay(1000);
  }
  
  shutdown();
  Serial.print("Input = ");
  Serial.print(mcp.digitalRead(0));
  Serial.print(mcp.digitalRead(1));
  Serial.print(mcp.digitalRead(2));
  Serial.print(mcp.digitalRead(3));
  Serial.print(mcp.digitalRead(4));
  Serial.print(mcp.digitalRead(5));
  Serial.print(mcp.digitalRead(6));
  Serial.println(mcp.digitalRead(7));

  mcp.digitalWrite(8, mcp.digitalRead(0));
  mcp.digitalWrite(9, mcp.digitalRead(1));
  mcp.digitalWrite(10, mcp.digitalRead(2));
  mcp.digitalWrite(11, mcp.digitalRead(3));
  mcp.digitalWrite(12, mcp.digitalRead(4));
  mcp.digitalWrite(13, mcp.digitalRead(5));
  mcp.digitalWrite(14, mcp.digitalRead(6));
  mcp.digitalWrite(15, mcp.digitalRead(7));

  digitalWrite(13, mcp.digitalRead(0));
  Serial.print("Input = ");
  Serial.print(mcp.digitalRead(0));
  Serial.print(mcp.digitalRead(1));
  Serial.print(mcp.digitalRead(2));
  Serial.print(mcp.digitalRead(3));
  Serial.print(mcp.digitalRead(4));
  Serial.print(mcp.digitalRead(5));
  Serial.print(mcp.digitalRead(6));
  Serial.println(mcp.digitalRead(7));
  */
}


