#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
#define DHTPIN A2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
unsigned long nowDHT = 0;
unsigned long time;
int timedelayDHT = 2000;

int paso [4][4] =
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Data");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  time = millis();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (millis()>=nowDHT+ timedelayDHT) {
    nowDHT+=timedelayDHT;
    if (!isnan(humidity) && !isnan(temperature)) {
      // In ra Serial Monitor
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.print("%\tTemperature: ");
      Serial.print(temperature);
      Serial.println("°C");

      // Hiển thị dữ liệu lên màn hình LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Humidity: ");
      lcd.print(humidity);
      lcd.print("%");

      lcd.setCursor(0, 1);
      lcd.print("Temperature: ");
      lcd.print(temperature);
      lcd.print("C");
    } else {
      Serial.println("Failed to read data from DHT11 sensor!");
    }  
    // for (int i = 0; i < 4; i++)
    // {
    //   digitalWrite(IN1, paso[i][0]);
    //   digitalWrite(IN2, paso[i][1]);
    //   digitalWrite(IN3, paso[i][2]);
    //   digitalWrite(IN4, paso[i][3]);
    //   delay(5)
    // }
  }    
}
