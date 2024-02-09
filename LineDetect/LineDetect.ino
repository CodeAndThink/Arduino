#define S1 A1
#define S2 A2
#define S3 A3
#define S4 A4
#define S5 A5

void setup() {
  // put your setup code here, to run once:
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(S1));
  Serial.print(" ");
  Serial.print(analogRead(S2));
  Serial.print(" ");
  Serial.print(analogRead(S3));
  Serial.print(" ");
  Serial.print(analogRead(S4));
  Serial.print(" ");
  Serial.print(analogRead(S5));
  Serial.println();
  delay(500);
}
