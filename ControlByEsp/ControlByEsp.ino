#include <SoftwareSerial.h>
SoftwareSerial mySerial (7, 8);

#define A1 3
#define A2 5
#define B1 6
#define B2 9
int speed = 255;
int speed_coeff = 55;

void setup() {
  // put your setup code here, to run once:
  pinMode(A1, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B2, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}
void goAhead()
{
  analogWrite(A1, speed);
  analogWrite(B1, speed);
  analogWrite(A2, 0);
  analogWrite(B2, 0);  
}
void turnBack()
{
  analogWrite(A1, 0);
  analogWrite(B1, 0);
  analogWrite(A2, speed);
  analogWrite(B2, speed);   
}
void turnRight()
{
  analogWrite(A1, 0);
  analogWrite(B1, speed);
  analogWrite(A2, speed);
  analogWrite(B2, 0);
}
void turnLeft()
{
  analogWrite(A1, speed);
  analogWrite(B1, 0);
  analogWrite(A2, 0);
  analogWrite(B2, speed);
}
void goAheadRight()
{
  analogWrite(A1, speed - speed_coeff);
  analogWrite(B1, speed);
  analogWrite(A2, 0);
  analogWrite(B2, 0);  
}
void goAheadLeft()
{
  analogWrite(A1, speed);
  analogWrite(B1, speed - speed_coeff);
  analogWrite(A2, 0);
  analogWrite(B2, 0);
}
void turnBackRight()
{
  analogWrite(A1, 0);
  analogWrite(B1, 0);
  analogWrite(A2, speed - speed_coeff);
  analogWrite(B2, speed);
}
void turnBackLeft()
{
  analogWrite(A1, 0);
  analogWrite(B1, 0);
  analogWrite(A2, speed);
  analogWrite(B2, speed - speed_coeff);
}
void stop()
{
  analogWrite(A1, 0);
  analogWrite(B1, 0);
  analogWrite(A2, 0);
  analogWrite(B2, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int input = mySerial.read();
  Serial.println(input);
  
}
