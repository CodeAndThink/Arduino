#include <SoftwareSerial.h>
SoftwareSerial mySerial (7, 8);

#define A1 3
#define A2 5
#define B1 6
#define B2 9
int speed = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(A1, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B2, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int input = mySerial.read();
  Serial.println(input);
  if(input == 49)
  {
    analogWrite(A1, speed);
    analogWrite(B1, 0);
    analogWrite(A2, 0);
    analogWrite(B2, 0);
    delay(3000);
    analogWrite(A1, 0);
    analogWrite(B1, 0);
    analogWrite(A2, 0);
    analogWrite(B2, 0);  
    mySerial.println("0");    
  }else if(input == 50)
  {
    analogWrite(A1, 0);
    analogWrite(B1, speed);
    analogWrite(A2, 0);
    analogWrite(B2, 0);
    delay(3000);
    analogWrite(A1, 0);
    analogWrite(B1, 0);
    analogWrite(A2, 0);
    analogWrite(B2, 0); 
    mySerial.println("0");
  }else if(input == 51)
  {
    analogWrite(A1, 0);
    analogWrite(B1, 0);
    analogWrite(A2, speed);
    analogWrite(B2, speed);
    delay(3000);
    analogWrite(A1, 0);
    analogWrite(B1, 0);
    analogWrite(A2, 0);
    analogWrite(B2, 0); 
    mySerial.println(-speed);
  }else if(input == 52)
  {
    analogWrite(A1, 0);
    analogWrite(B1, 0);
    analogWrite(A2, 0);
    analogWrite(B2, 0);  
    mySerial.println("0");    
  }else if(input == 48)
  {
    analogWrite(A1, speed);
    analogWrite(B1, speed);
    analogWrite(A2, 0);
    analogWrite(B2, 0);
    mySerial.println(speed);
  }
  delay(500);
}
