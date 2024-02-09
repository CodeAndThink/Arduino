int Vx = A0;
int Vy = A1;
void setup() {
  // put your setup code here, to run once:
  pinMode(Vx, INPUT);
  pinMode(Vy, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print(analogRead(Vx));
  //Serial.print(" - ");
  //Serial.print(analogRead(Vy));
  //Serial.println();
  Serial.println("Hello");
  delay(200);
}
