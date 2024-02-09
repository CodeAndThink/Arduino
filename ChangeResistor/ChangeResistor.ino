#define Res A0
#define LED 6
int Giatribiendoi = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(Res, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Level = analogRead(Res);
  Giatribiendoi = map(Level, 0, 1023, 0, 255);
  analogWrite(LED, Giatribiendoi);
  delay(50);
}
