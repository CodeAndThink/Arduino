#include <DHT.h>  // Including library for dht
#include <ESP8266WiFi.h>
String apiKey = "GB31GW8YPC84YOMX";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "VNU-IS THMT 02";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Vnu.edu.vn";
//const char *ssid =  "Tang 3";     // replace with your wifi ssid and wpa2 key
//const char *pass =  "88888888";
const char* server = "api.thingspeak.com";
#define DHTPIN 0
bool start = false;
DHT dht(DHTPIN, DHT11);
WiFiClient client;
String sms;

void setup() {
  ///////////////////////
  Serial.begin(9600);
  delay(2000);
  dht.begin();
  delay(100);
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
  /////////////////////////////////////////////////////
}

void loop() {
  // put your main code here, to run repeatedly:
  sms = "";
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  sms.concat(t);
  sms += " ";
  sms.concat(h);
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
  }
  if(t>=20.0)
  {
    Serial.print("AT");  //Start Configuring GSM Module
    delay(1000);         //One second delay
    Serial.println();
    Serial.println("AT+CMGF=1");  // Set GSM in text mode
    delay(1000);                  // One second delay
    Serial.println();
    Serial.print("AT+CMGS=");     // Enter the receiver number
    Serial.print("\"+84385965957\"");
    Serial.println();
    delay(1000);
    Serial.print(sms); // SMS body - Sms Text
    delay(1000);
    Serial.println();
    Serial.write(26);                //CTRL+Z Command to send text and end session
  }
  client.stop(); 
  Serial.println("Waiting..."); 
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
