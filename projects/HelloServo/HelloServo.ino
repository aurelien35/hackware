#include "CheapStepper.h"


CheapStepper stepper(8, 9, 10, 11);

boolean moveClockwise = true;

void setup()
{
  Serial.begin(9600);
  Serial.println("Ready to start moving!");
}

void loop()
{
  for (int s=0; s<4096; s++)
  {
    // this will loop 4096 times
    // 4096 steps = full rotation using default values
    /* Note:
     * you could alternatively use 4076 steps... 
     * if you think your 28BYJ-48 stepper's internal gear ratio is 63.68395:1 (measured) rather than 64:1 (advertised)
     * for more info, see: http://forum.arduino.cc/index.php?topic=71964.15)
     */
    
    stepper.step(moveClockwise);

    // now let's get the current step position of motor
    int nStep = stepper.getStep();

    // and if it's divisible by 64...    
    if (nStep%64 == 0)
    { 
      Serial.print("current step position: "); Serial.print(nStep);
      Serial.println();      
    }
  }

  delay(1000);  
  moveClockwise = !moveClockwise;
}

