#define fA 3
#define rA 5
#define fB 6
#define rB 9
#define left A1
#define right A0
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
}

void MotorControl(int forward, int revease, int fspeed, int rspeed)
{
  analogWrite(forward, fspeed);
  analogWrite(revease, rspeed);
}

void loop() {
  Serial.print("left=");
  Serial.print(analogRead(left));
  Serial.print(", right=");
  Serial.print(analogRead(right));
  Serial.println();
  if(digitalRead(left) == 0 && digitalRead(right) == 0)
  {
    MotorControl(fA, rA, 200, 0);
    MotorControl(fB, rB, 200, 0);
  }
  if(digitalRead(right) == 1 && digitalRead(left) == 0)
  {
    MotorControl(fA, rA, 0, 200);
    MotorControl(fB, rB, 255, 0);
  }
  if(digitalRead(left) == 1 && digitalRead(right) == 0)
  {
    MotorControl(fA, rA, 255, 0);
    MotorControl(fB, rB, 0, 200);
  }
  if(digitalRead(left) == 1 && digitalRead(right) == 1)
  {
    MotorControl(fA, rA, 0, 0);
    MotorControl(fB, rB, 0, 0);
  }
}
