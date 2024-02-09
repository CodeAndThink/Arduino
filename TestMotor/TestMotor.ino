#include <Servo.h>
#include <SoftwareSerial.h>
//
Servo myservo;
SoftwareSerial mySerial (7, 8);
//define pin of Sonic Distance Calculate
const unsigned int TRIG_PIN=13;
const unsigned int ECHO_PIN=12;
const unsigned int SERVO_PIN=11;
//
//Define pin of Motors
#define R1 3
#define R2 5
#define L1 6
#define L2 9
//
//Define pin for line tracking sensor
#define S1 A1
#define S2 A2
#define S3 A3
#define S4 A4
#define S5 A5
//
//Define mode control
#define Btn A0
int mode = 2;
//
//Define limit distance
int limitdis = 20;
//Define PID controller
int P, D, I, previousError, PIDvalue, error;
int lsp, rsp;
int lfspeed = 200;
float Kp = 0;
float Kd = 0;
float Ki = 0 ;
int minValues[5], maxValues[5], threshold[5];
//
void setup() {
  pinMode(R1, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(SERVO_PIN);
  myservo.write(90);
}
//Function control servo 
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
//
//Control by Website
void ControlByWeb()
{
  int input = mySerial.read();
    Serial.println(input);
    if(input == 49)
    {
      TurnLeft();
      delay(2000);
      Stop();     
    }else if(input == 50)
    {
      TurnRight();
      delay(2000);
      Stop(); 
    }else if(input == 51)
    {
      TurnBack();
    }else if(input == 52)
    {
      Stop();      
    }else if(input == 48)
    {
      GoStrange();
    }
    delay(500);
}
//Control by line
void linefollow()
{
  int error = (analogRead(S2) - analogRead(S4));
  P = error;
  I = I + error;
  D = error - previousError;

  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  previousError = error;

  lsp = lfspeed - PIDvalue;
  rsp = lfspeed + PIDvalue;

  if (lsp > 255) {
    lsp = 255;
  }
  if (lsp < 0) {
    lsp = 0;
  }
  if (rsp > 255) {
    rsp = 255;
  }
  if (rsp < 0) {
    rsp = 0;
  }
  MotorSpeed(1, rsp);
  MotorSpeed(2, lsp);
}
void ControlByLine()
{
  calibrate();
  while (1)
  {
    if (analogRead(S1) > threshold[0] && analogRead(S5) < threshold[4] )
    {
      lsp = 0; rsp = lfspeed;
      MotorSpeed(1, 0);
      MotorSpeed(2, lfspeed);
    }

    else if (analogRead(S5) > threshold[4] && analogRead(S1) < threshold[0])
    { lsp = lfspeed; rsp = 0;
      MotorSpeed(1, lfspeed);
      MotorSpeed(2, 0);
    }
    else if (analogRead(S3) > threshold[2])
    {
      Kp = 0.0009 * (1000 - analogRead(S3));
      Kd = 10 * Kp;
      Ki = 0.0001;
      linefollow();
    }
  }
}
void calibrate()
{
  minValues[0] = analogRead(S1);
  minValues[1] = analogRead(S2);
  minValues[2] = analogRead(S3);
  minValues[3] = analogRead(S4);
  minValues[4] = analogRead(S5);
  maxValues[0] = analogRead(S1);
  maxValues[1] = analogRead(S2);
  maxValues[2] = analogRead(S3);
  maxValues[3] = analogRead(S4);
  maxValues[4] = analogRead(S5);
  for (int i = 0; i < 5000; i++)
  {
    if(minValues[0] > analogRead(S1))
    {
      minValues[0] = analogRead(S1);
    }
    if(minValues[1] > analogRead(S2))
    {
      minValues[1] = analogRead(S2);
    }
    if(minValues[2] > analogRead(S3))
    {
      minValues[2] = analogRead(S3);
    }
    if(minValues[3] > analogRead(S4))
    {
      minValues[3] = analogRead(S4);
    }
    if(minValues[4] > analogRead(S5))
    {
      minValues[4] = analogRead(S5);
    }
    if(maxValues[0] < analogRead(S1))
    {
      maxValues[0] = analogRead(S1);
    }
    if(maxValues[1] < analogRead(S2))
    {
      maxValues[1] = analogRead(S2);
    }
    if(maxValues[2] < analogRead(S3))
    {
      maxValues[2] = analogRead(S3);
    }
    if(maxValues[3] < analogRead(S4))
    {
      maxValues[3] = analogRead(S4);
    }
    if(maxValues[4] < analogRead(S5)) 
    {
      maxValues[4] = analogRead(S5);
    }
  }
  for ( int i = 1; i < 5; i++)
  {
    threshold[i] = (minValues[i] + maxValues[i]) / 2;
    Serial.print(threshold[i]);
    Serial.print("   ");
  }
  Serial.println();  
  Stop();
}
//
void loop() {
  if(mode == 0)
  {
    ControlByWeb();
  }
  if(mode == 1)
  {
    ControlByDistance();    
  }
  if(mode == 2)
  {
    ControlByLine();
  }
}
