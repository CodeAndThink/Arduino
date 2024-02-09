#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#define DHTTYPE DHT11
#define DHTPIN 7
#define REDLED 6
#define BLUELED 5
#define GREENLED 3
#define RESISPIN A0
#define BUTTON 13
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

int modeLed = 0;
unsigned long nowDHt = 0;
unsigned long nowLED = 0;
unsigned long time;
int timeDelayDHTsensor = 2000;
int timeDelayLED = 300;
int giatribiendoi = 0;

byte customChar[] = {
  0x00,
  0x0E,
  0x0A,
  0x0E,
  0x00,
  0x00,
  0x00,
  0x00
};

void setup()
{
  pinMode(DHTPIN, INPUT);
  pinMode(REDLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(RESISPIN, INPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  dht.begin();
  lcd.init();  
  lcd.backlight();
  lcd.clearWriteError();
  lcd.print("Nhiet do: ");
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  lcd.createChar(0, customChar);
}

void loop()
{
  int resistor = analogRead(RESISPIN);
  giatribiendoi = map(resistor, 0, 1023, 0, 255); 
  time = millis();
  if(digitalRead(BUTTON) == HIGH)
  {
    delay(300);
    modeLed++; 
    Serial.print(modeLed);
    if(modeLed > 3)
    {
      modeLed = 0;
    } 
  }else{
      
  }
  // Wait a few seconds between measurements.  
  if(time - nowDHt >= timeDelayDHTsensor)
  {
    nowDHt = millis();
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    } 
    else 
    {
      Serial.println(t);
      lcd.setCursor(10,0);
      lcd.print(round(t));
      lcd.print(" ");
      lcd.setCursor(12,0);
      lcd.write(0);
      lcd.print("C");
      lcd.setCursor(10,1);
      lcd.print(round(h));
      lcd.print(" %");    
    }    
  } 
  if(time - nowLED >= timeDelayLED)
  {
    nowLED = millis();
    if(giatribiendoi < 255)
    {
      analogWrite(BLUELED, giatribiendoi);
    }
    if(giatribiendoi >= 127 && giatribiendoi < 382)
    {
      analogWrite(GREENLED, giatribiendoi);
    }
    if(giatribiendoi < 510 && giatribiendoi >= 382)
    {
      analogWrite(REDLED, giatribiendoi);
    }
    if(modeLed == 1)
    {
      analogWrite(REDLED, LOW);
      analogWrite(BLUELED, LOW);
      if(giatribiendoi > 10)
      {
        analogWrite(GREENLED, giatribiendoi);      
      }else{
        analogWrite(GREENLED, LOW);
      }      
    }
    if(modeLed == 2)
    {
      analogWrite(GREENLED, LOW);
      analogWrite(BLUELED, LOW);
      if(giatribiendoi > 10)
      {
        analogWrite(REDLED, giatribiendoi);      
      }else{
        analogWrite(REDLED, LOW);
      }      
    }    
    if(modeLed == 3)
    {
      analogWrite(REDLED, LOW);
      analogWrite(GREENLED, LOW);
      if(giatribiendoi > 10)
      {
        analogWrite(BLUELED, giatribiendoi);      
      }else{
        analogWrite(BLUELED, LOW);
      }      
    } 
    if(modeLed == 0)
    {
      analogWrite(REDLED, 0);
      analogWrite(GREENLED, 0); 
      analogWrite(BLUELED, 0);     
    }
  }
}
