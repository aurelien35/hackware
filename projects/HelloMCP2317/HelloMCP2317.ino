#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp;
  
void setup() {  
  Serial.begin(9600);
  while (!Serial);
  
  mcp.begin();      // use default address 0

  mcp.pinMode(0, INPUT);
//  mcp.pullUp(0, HIGH);  // turn on a 100K pullup internally

  pinMode(13, OUTPUT);  // use the p13 LED as debugging

  Serial.println("Start");
}



void loop() {
  // The LED will 'echo' the button
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
  delay(50);
}
