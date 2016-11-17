#include <SoftwareServo.h>

SoftwareServo myservo;

int servoPos = 0;
int motorSpeed = 0;
long timestamp = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(3);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Switch: ");
  Serial.print(digitalRead(10));
  Serial.print("  Pot: ");
  Serial.print(analogRead(A0));
  
  if(millis() - timestamp > 500) {
    servoPos += 10;
    timestamp = millis();
  }
  if(servoPos > 180)
    servoPos = 0;
  myservo.write(servoPos);
  Serial.print("  Servo: ");
  Serial.print(servoPos);
  SoftwareServo::refresh();
  
  motorSpeed = analogRead(A0)/4;
  analogWrite(9, motorSpeed);
  Serial.print("  Motor: ");
  Serial.println(motorSpeed);
}
