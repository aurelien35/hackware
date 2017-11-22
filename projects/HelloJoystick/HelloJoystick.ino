#include "Joystick.h"

Joystick_ Joystick(0x03, JOYSTICK_TYPE_JOYSTICK, 4, 0, true, true, false, false, false, false, false, false, false, false, false);

void setup()
{
  // Set Range Values
  Joystick.setXAxisRange(0, 2047);
  
  Joystick.begin();
}

void loop()
{
  Joystick.setXAxis(1024 + analogRead(A0));

  delay(2);
}

