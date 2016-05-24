#include <SoftwareServo.h>

SoftwareServo rotator;

int servoValue = 100;
long timeStamp = 0;

void setup()
{
  rotator.attach(3);
  timeStamp = millis();
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
  
}

void loop()
{
  if(digitalRead(10))
  {

    if(millis() - timeStamp > 1000)
    {
      servoValue += 5;
       if(servoValue > 115) servoValue = 80;
      timeStamp = millis();
    }
   
  }
  rotator.write(servoValue);
  SoftwareServo::refresh();
  
  int motorSpeed = map(analogRead(A0), 0, 1023, 0, 255);
  analogWrite(9, motorSpeed);
  Serial.println(motorSpeed);
  delay(50);

}
