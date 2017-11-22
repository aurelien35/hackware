#include <Servo.h>

Servo servo;

void setup()
{
  // Attache le servomoteur à la broche D9
  servo.attach(9);
}

void loop()
{
  // Fait bouger le bras de 0° à 180°
  for (int position = 0; position <= 180; position++) {
    servo.write(position);
    delay(15);
  }
  
  // Fait bouger le bras de 180° à 10°
  for (int position = 180; position >= 0; position--) {
    servo.write(position);
    delay(15);
  }
  
  servo.write(0);
  delay(1500);
}
