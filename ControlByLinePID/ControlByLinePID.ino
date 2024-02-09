#include <SoftwareSerial.h>
//
//Code dành cho Arduino Uno R3
//Code điều khiển xe tự hành sử dụng cảm  biến hồng ngoại nhằm đi theo vạch kẻ đường tạo sẵn. 
//Có giao tiếp với ESP8266 nhằm theo dõi tốc độ xe trên website
//
#define R1 3 // Định nghĩa tiến 
#define R2 5
#define L1 6
#define L2 9
#define S1 A1 // Định nghĩa cổng của cảm biến hồng ngoại thứ nhất 
#define S2 A2 // Định nghĩa cổng của cảm biến hồng ngoại thứ hai 
#define S3 A3 // Định nghĩa cổng của cảm biến hồng ngoại thứ ba  
#define S4 A4 // Định nghĩa cổng của cảm biến hồng ngoại thứ tư 
#define S5 A5 // Định nghĩa cổng của cảm biến hồng ngoại thứ năm 
SoftwareSerial mySerial (7, 8); // Tạo cổng giao tiếp nối tiếp ảo với Rx là cổng D7 và Tx là cổng D8 để truyền dữ liệu cho ESP8266 nhằm đưa dữ liệu lên website để theo dõi

unsigned long now = 0; //Sử dụng timer ngắt 
unsigned long time;
int timeDelay = 2000; //Cứ sau mỗi 2000ms tiến hành ngắt một lần

int P, D, I, previousError, PIDvalue, error; //định nghĩa biến cho điều khiển sử dụng PID controller
int lsp, rsp; // Định nghĩa biến tốc độ cho bánh xe bên phải (rsp) và bánh xe bên trái (lsp)
int lfspeed = 200; //Định nghĩa tốc độ mặc định
//Định nghĩa các giá trị của hàm PID controller
float Kp = 0;
float Kd = 0;
float Ki = 0;
// Định nghĩa các giá trị so sánh cho các cảm biến hồng ngoại
int minValues[5] = {53, 53, 53, 53, 53}
, maxValues[5] = {926,926,926,926,926}
, threshold[5] = {489,489,489,489,489}; 

void setup() {
  // Định nghĩa cho các chân:
  // Định nghĩa cho các chân driver motor
  pinMode(R1, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L2, OUTPUT);
  //Định nghĩa cho các chân cảm biến
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  // Định nghĩa giao tiếp 
  Serial.begin(9600); //Định nghĩa giao tiếp nối tiếp với band = 9600 qua cổng Tx, Rx mặc định
  mySerial.begin(9600); //Định nghĩa giao tiếp nối tiếp với band = 9600 qua cổng Tx, Rx ảo
}
void Stop() //Hàm dừng xe
{
  MotorSpeed(1, 0);
  MotorSpeed(2, 0); 
}
void MotorSpeed(int motor, int speed) // Hàm truyền tốc độ cho xe
{
  if(motor == 1) // nếu motor là motor số 1
  {
    if(speed >= 0)
    {
      analogWrite(R1, speed);
      analogWrite(R2, 0);
    }else{
      analogWrite(R1, 0);
      analogWrite(R2, -speed);
    }
  }
  if(motor == 2)// nếu motor là motor số 2
  {
    if(speed >= 0)
    {
      analogWrite(L1, speed);
      analogWrite(L2, 0);
    }else{
      analogWrite(L1, 0);
      analogWrite(L2, -speed);
    }
  }
}
void linefollow() // Hàm tính toán tốc độ dựa trên cảm biến hồng ngoại
{
  int error = (analogRead(S2) - analogRead(S4)); // So sánh độ chênh lệch của 2 cảm biến 
  P = error;
  I = I + error;
  D = error - previousError;

  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D); // Hàm điều khiển tốc độ sử dụng PID controller
  previousError = error;

  lsp = lfspeed + PIDvalue; //Gán giá trị tốc độ cho motor bên trái 
  rsp = lfspeed - PIDvalue; //gán giá trị tốc độ cho motor bên phải

  if (lsp > 255) { // giới hạn giá trị tốc độ do chân điều khiển PWM của Arduino chỉ có độ phân giải là 8 bit (2^8 = 256) 
    lsp = 255;
  }
  if (rsp > 255) {
    rsp = 255;
  }
  /*if (lsp < 0) {
    lsp = 0;
  }
  if (rsp < 0) {
    rsp = 0;
  }*/
  if(time - now >= timeDelay) // thực hiện ngắt để truyền dữ liệu cho ESP8266 nhằm đưa dữ liệu lên website để theo dõi
  {
    now = millis();
    if(abs(rsp) > abs(lsp))
    {
      mySerial.println(rsp);
    }else{
      mySerial.println(lsp);
    }
  }
  Serial.print("Left: ");
  Serial.print(lsp);
  Serial.print("  Right: ");
  Serial.print(rsp);
  Serial.println();  
  MotorSpeed(1, rsp); // Truyền dữ liệu tốc độ cho motor 
  MotorSpeed(2, lsp);
}
void ControlByLine()
{
  time = millis(); //Sử dụng millis để ngắt
  if (analogRead(S1) > threshold[0] && analogRead(S5) < threshold[4] ) //Nếu cảm biến ngoài cùng bên trái của xe chạm vạch: thực hiện rẽ bên trái
  {
    MotorSpeed(1, -lfspeed);
    MotorSpeed(2, lfspeed);   
    if(time - now >= timeDelay)// Thực hiên truyền dữ liệu cho ESP8266
    {
      now = millis();
      mySerial.println(lfspeed);
    }
  }

  else if (analogRead(S5) > threshold[4] && analogRead(S1) < threshold[0])//Nếu cảm biến ngoài cùng bên phải của xe chạm vạch: thực hiện rẽ bên phải
  { 
    MotorSpeed(1, lfspeed);
    MotorSpeed(2, -lfspeed);
    if(time - now >= timeDelay)// Thực hiên truyền dữ liệu cho ESP8266
    {
      now = millis();
      mySerial.println(lfspeed);
    }
  }
  else if(analogRead(S3) > threshold[2]) // Nếu xe chưa đi đúng vạch, sử dụng điều khiển PID để căn chỉnh lại tốc độ
  {
    Kp = 0.003 * (1000 - analogRead(S3));
    Kd = 12 * Kp;
    Ki = 0.001;
    linefollow();
  }else if(analogRead(S1) > threshold[0] && analogRead(S2) > threshold[1] && analogRead(S3) < threshold[2] && analogRead(S4) > threshold[3] && analogRead(S5) > threshold[4]) 
  // Nếu xe đi đúng vạch, tốc độ xe bằng với tốc độ mặc định
  {
    MotorSpeed(1, lfspeed);
    MotorSpeed(2, lfspeed); 
    if(time - now >= timeDelay)
    {
      now = millis();
      mySerial.println(lfspeed);
    }  
  }else if(analogRead(S1) < threshold[0] && analogRead(S2) < threshold[1] && analogRead(S3) < threshold[2] && analogRead(S4) < threshold[3] && analogRead(S5) < threshold[4]) 
  //Nếu toàn bộ cảm biến chạm vạch, xe dừng lại
  {
    Stop();
    if(time - now >= timeDelay)
    {
      now = millis();
      mySerial.println(0);
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  ControlByLine(); // Sử dụng chế độ điều khiển theo vạch kẻ đường
}
