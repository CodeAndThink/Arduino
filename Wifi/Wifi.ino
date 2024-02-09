#include <DHT.h>  // Including library for dht
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

String apiKey = "GB31GW8YPC84YOMX";     //  Enter your Write API key from ThingSpeak
 
//const char *ssid =  "VNU-IS THMT 01";     // replace with your wifi ssid and wpa2 key
//const char *pass =  "Vnu.edu.vn";
const char *ssid =  "Tang 3";     // replace with your wifi ssid and wpa2 key
const char *pass =  "88888888";
const char* server = "api.thingspeak.com";
bool state = true;

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

#define DHTPIN 0          //pin where the dht11 is connected
#define RED 16
#define GREEN 2
#define BLUE 13
#define Buzz 14
#define Button 15

DHT dht(DHTPIN, DHT11);
 
WiFiClient client;
 
void setup() 
{
  Serial.begin(9600);
  //////////////////////////////
  lcd.init();  
  lcd.backlight();
  lcd.clearWriteError();
  lcd.print("Nhiet do: ");
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  lcd.createChar(0, customChar);
  ///////////////////////////////
  delay(10);
  dht.begin();
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(Buzz, OUTPUT);
  pinMode(Button, INPUT);
}
 
void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if(digitalRead(Button) == 1)
  {
    if(state == true) state = false;
    else state = true;
    delay(300);
  }
  Serial.println(state);
  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }else{
    //LCD display///////////////////////////////
    lcd.setCursor(10,0);
    lcd.print((int)t);
    lcd.print(" ");
    lcd.setCursor(12,0);
    lcd.write(0);
    lcd.print("C");
    lcd.setCursor(10,1);
    lcd.print((int)h);
    lcd.print(" %");
    ///////////////////////////////
  }
  if(t < 20.0)
    {
      digitalWrite(BLUE, HIGH);
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(Buzz,LOW);
    }
    if(t >= 20.0 && t < 30.0)
    {
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, LOW);
      digitalWrite(Buzz,LOW);
    }
    if(t >= 30.0)
    {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      if(state == true)
      {
        digitalWrite(Buzz,HIGH);
      }else{
        digitalWrite(Buzz,LOW);
      }          
    }
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {      
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(t);
    postStr +="&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";
 
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celcius, Humidity: ");
    Serial.print(h);
    Serial.println("%. Send to Thingspeak.");
  }
  client.stop(); 
  Serial.println("Waiting..."); 
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}

