#define POWER_PIN  7
#define SIGNAL_PIN A3

int value = 0; // variable to store the sensor value

void setup() {
  Serial.begin(9600);
}

void loop() {
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  Serial.print("Sensor value: ");
  Serial.println(value);
  delay(1000);
}
