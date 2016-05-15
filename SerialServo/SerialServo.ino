#include <SoftwareServo.h>

SoftwareServo servo1;

int servoValue = 0;
long timeStamp = 0;

void setup()
{
  servo1.attach(8);
  timeStamp = millis();
  pinMode(3, OUTPUT);

}



void loop()
{
          
  if(millis() - timeStamp > 1000)
  {
    servoValue = servoValue + 10;
    if(servoValue > 150) servoValue = 0;
    timeStamp = millis();
  }
  servo1.write(servoValue);
  SoftwareServo::refresh();
  analogWrite(3, 128);
}
