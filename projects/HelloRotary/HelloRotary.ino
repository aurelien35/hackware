#include "ClickEncoder.h"
#include "TimerOne.h"

ClickEncoder* encoder = NULL;
int sensorValue = 0;
int encoderPosition = 0;

void timerIsr()
{
  encoder->service();
}

void setup()
{
  Serial.begin(9600);
  
  encoder = new ClickEncoder(A2, A1, A3);
  
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
}

void loop()
{
  // Read encoder position
  {
    int encoderDelta = encoder->getValue();
    
    if (abs(encoderDelta) > 0)
    {
      encoderPosition += encoderDelta;
      Serial.print("Encoder position : ");
      Serial.println(encoderPosition);
    }  
  }

  // Read encoder button
  {
    ClickEncoder::Button button = encoder->getButton();
    if (button != ClickEncoder::Open)
    {
      Serial.print("Button: ");
      switch (button)
      {
        case ClickEncoder::Pressed :
          Serial.println("ClickEncoder::Pressed");
          break;
        case ClickEncoder::Held :
          Serial.println("ClickEncoder::Held");
          break;
        case ClickEncoder::Released :
          Serial.println("ClickEncoder::Released");
          break;
        case ClickEncoder::Clicked :
          Serial.println("ClickEncoder::Clicked");
          break;
        case ClickEncoder::DoubleClicked :
          Serial.println("ClickEncoder::DoubleClicked");
            encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
            Serial.print("  Acceleration is ");
            Serial.println((encoder->getAccelerationEnabled()) ? "enabled" : "disabled");
          break;
      }
    }
  }
  
  // Read analog input
  {
    int newSensorValue = analogRead(A0);
    int sensorDelta = sensorValue - newSensorValue;
    if (abs(sensorDelta) > 5)
    {
      sensorValue = newSensorValue;
      //Serial.print("Sensor Value : ");
      //Serial.println(sensorValue);
    }
  }

  delay(2);
}
