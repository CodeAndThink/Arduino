void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(16,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = analogRead(16);
  Serial.println(a);
  delay(100);
}
