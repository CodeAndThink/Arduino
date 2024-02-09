#define A 7
#define B 8
#define C 9
#define D 10
#define E 11
#define F 12
#define G 13
#define DP 14
#define Res A0
int number = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(Res, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = analogRead(Res);
    if(a <= 340)
  {
    digitalWrite(A, LOW);digitalWrite(B, HIGH);digitalWrite(C, HIGH);digitalWrite(D, LOW);digitalWrite(E, LOW);digitalWrite(F, LOW);digitalWrite(G, LOW);
  }else if(a <= 680)
  {
    digitalWrite(A, LOW);digitalWrite(B, HIGH);digitalWrite(C, HIGH);digitalWrite(D, LOW);digitalWrite(E, LOW);digitalWrite(F, HIGH);digitalWrite(G, HIGH);
  }else
  {
    digitalWrite(A, HIGH);digitalWrite(B, HIGH);digitalWrite(C, HIGH);digitalWrite(D, LOW);digitalWrite(E, LOW);digitalWrite(F, LOW);digitalWrite(G, LOW);
  }
}

