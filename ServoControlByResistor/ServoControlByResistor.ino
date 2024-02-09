#include <Servo.h>      // Thư viện điều khiển servo
Servo myservo;          
 
int bientro = A2;       // Khai báo chân analog đọc biến trở điều khiển servo
int servoPin = 3;       // Khai báo chân điều khiển servo

unsigned long nowtime1 = 0;
unsigned long time;
int timedelayServo = 100;
 
void setup ()
{
    // Cài đặt chức năng điều khiển servo cho chân servoPin
    myservo.attach(servoPin); 
    Serial.begin(9600); // Mở giao tiếp Serial ở baudrate 9600
}
 
void loop ()
{
    time = millis();
    int giatri = map(analogRead(bientro),0,1018,0,180);
    if (millis()>=nowtime1+ timedelayServo) {
      nowtime1+=timedelayServo;
      Serial.print("Bien tro");
      Serial.print(giatri);
      Serial.println();
      myservo.write(0);
    }
}