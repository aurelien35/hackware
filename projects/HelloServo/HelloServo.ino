#include <Servo.h>

Servo servo;

void setup()
{
  Serial.begin(9600);

  // Attache le servomoteur à la broche D9
  servo.attach(9);
}

void loop()
{
	Serial.println("Position : 0");
	servo.write(0);
    delay(2000);
/*
	Serial.println("Position : 45");
	servo.write(45);
    delay(2000);

	Serial.println("Position : 90");
	servo.write(90);
    delay(2000);

	Serial.println("Position : 135");
	servo.write(135);
    delay(2000);

	Serial.println("Position : 180");
	servo.write(180);
    delay(5000);
	*/
}
