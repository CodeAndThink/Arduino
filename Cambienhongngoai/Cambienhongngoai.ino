void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = !digitalRead(A0);
  int b = !a;
    Serial.println(a);
    Serial.println(b);
    delay(100);
}
