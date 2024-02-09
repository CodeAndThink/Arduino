#include "SIM900.h"
#include "sms.h"

#include <DHT.h>  // Including library for dht
#include <ESP8266WiFi.h>
#define DHTPIN 0          //pin where the dht11 is connected

SMSGSM sms;
String apiKey = "GB31GW8YPC84YOMX";     //  Enter your Write API key from ThingSpeak
 
//const char *ssid =  "VNU-IS THMT 02";     // replace with your wifi ssid and wpa2 key
//const char *pass =  "Vnu.edu.vn";
const char *ssid =  "VNU-IS THMT 02";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Vnu.edu.vn";
const char* server = "api.thingspeak.com";

bool start = false;
DHT dht(DHTPIN, DHT11);
 
WiFiClient client;

void setup()
{
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println("GSM SIM900A BEGIN");
  delay(100);
  if (gsm.begin(2400))
  {     
      Serial.println("\nstatus=READY");     
      started=true;     
  }else 
  Serial.println("\nstatus=IDLE");    
  if(started)
  {     
      sms.SendSMS("+84123456789", "Online");   //đổi lại số của bạn nhé :D
  }  
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
}

void loop()
{  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
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
    //if(t >= 30.0)
    //{
      Serial.print("AT");
      Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      Serial.println("AT+CMGS=\"+84979046630\"\r"); // Replace x with mobile number
      delay(1000);
      Serial.println("Warning");// The SMS text you want to send
      delay(100);
      Serial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
    //}
  }
  client.stop(); 
  Serial.println("Waiting..."); 
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}


