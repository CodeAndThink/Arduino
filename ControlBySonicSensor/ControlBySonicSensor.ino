#include <Servo.h>
Servo myservo;
const unsigned int TRIG_PIN=13;
const unsigned int ECHO_PIN=12;
const unsigned int SERVO_PIN=11;
#define R1 3
#define R2 5
#define L1 6
#define L2 9

int limitdis = 20;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(R1, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(SERVO_PIN);
  myservo.write(90);
}
int GetDisFront()
{
  myservo.write(90);
  delay(500);
  return UltraVoiceDistance();
  delay(500);
}
int GetDisLeft()
{
  myservo.write(180);
  delay(500);
  return UltraVoiceDistance();
  delay(500);
}
int GetDisRight()
{
  myservo.write(0);
  delay(500);
  return UltraVoiceDistance();
  delay(500);
}
//
//Calculate distance
int UltraVoiceDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN,  HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
  int distance= duration/58;
  if(duration==0){
    Serial.println("Warning: no pulse from sensor");
  }  
  else{
    Serial.print("distance to nearest object:");
    Serial.println(distance);
    Serial.println(" cm");
    return distance;
  }delay(200);
}
//Control motors speed
void MotorSpeed(int motor, int speed)
{
  if(motor == 1)
  {
    if(speed >= 0)
    {
      analogWrite(R1, speed);
      analogWrite(R2, 0);      
    }else{
      analogWrite(R1, 0);
      analogWrite(R2, abs(speed));      
    }
  }
  if(motor == 2)
  {
    if(speed >= 0)
    {
      analogWrite(L1, speed);
      analogWrite(L2, 0);      
    }else{
      analogWrite(L1, 0);
      analogWrite(L2, abs(speed));      
    }
  }
}
//Control motors direction
void TurnLeft()
{
  MotorSpeed(1, 255);
  MotorSpeed(2, -255);
}
void TurnRight()
{
  MotorSpeed(1, -255);
  MotorSpeed(2, 255);  
}
void TurnBack()
{
  MotorSpeed(1, -255);
  MotorSpeed(2, -255);
}
void GoStrange()
{
  MotorSpeed(1, 255);
  MotorSpeed(2, 255);
}
void Stop()
{
  MotorSpeed(1, 0);
  MotorSpeed(2, 0); 
}
//Mode 1: Control by Sonic distance calculate
void ControlByDistance()
{
  int leftdis;
  int rightdis;
  int frontdis;
  int speed;
  frontdis = GetDisFront();
  if(frontdis < limitdis)
  {
    Stop();
    leftdis = GetDisLeft();
    rightdis = GetDisRight();
    myservo.write(90);
    if(leftdis > limitdis && rightdis < limitdis)
    {
      TurnLeft();
      speed = 0; 
      delay(200);   
    }else if(leftdis < limitdis && rightdis > limitdis)
    {
      TurnRight();
      speed = 0; 
      delay(200);
    }else if(leftdis < limitdis && rightdis < limitdis)
    {
      Stop();
      speed = 0; 
    }
  }else{
      GoStrange();
      speed = 200;    
  }
  Serial.println(speed);
  delay(2000);
}
void loop() {
  // put your main code here, to run repeatedly:
  ControlByDistance();
}
