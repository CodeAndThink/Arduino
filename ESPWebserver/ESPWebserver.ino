#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;
ESP8266WebServer server(80);

String webPage =
{
  "<!DOCTYPE html>"
  "<html>"
  "<head>"
  "  <meta http-equiv='Content-Type' content='text/html; charset=utf-8'>"
  "  <title>Điều khiển thiết bị</title>"
  "  <title></title>"
  "  <meta name='viewport' content='width=device-width, initial-scale=1'>"
  "  <style>"
  "    .b{width: 100px;height: 40px;font-size: 21px;color: #FFF;background-color:#4caf50;border-radius: 10px;}"
  "    .t{width: 100px;height: 40px;font-size: 21px;color: #FFF;background-color:#f44336;border-radius: 10px;}"
  "  </style>"
  "</head>"
  "<body>"
  "<div style='width: 330px;height: auto;margin: 0 auto;margin-top: 70px'>"
  "<h1 align='center'>Điều khiển thiết bị qua WIFI</h1>"
  "  <table align='center'>"
  "    <tr>"
  "    <td><a href='/left'><button class='b'>Turn Left</button></a><td>"
  "    <td><a href='/right'><button class='t'>Turn Right</button></a><td>"
  "    <tr>"
  "    <tr>"
  "    <td><a href='/forward'><button class='b'>Go Ahead</button></a><td>"
  "    <td><a href='/reverse'><button class='t'>Go Back</button></a><td>"
  "    <tr>"
  "  </table>"
  "</div>"
  "</body>"
  "</html>"
};
void TrangChu()
{
  server.send(200, "text/html", webPage);
}
void left()
{
  digitalWrite(0, HIGH); 
  Serial.println("turn left");
  //server.send(200, "text/html", webPage);
}
void right()
{
  digitalWrite(0, LOW); 
  Serial.println("turn right");
  //server.send(200, "text/html", webPage);
}
void front()
{
  digitalWrite(2, HIGH); 
  Serial.println("go ahead");
  //server.send(200, "text/html", webPage);
}
void back()
{
  digitalWrite(2, LOW); 
  Serial.println("turn back");
  //server.send(200, "text/html", webPage);
}

const char *ssid = "Tang 3";
const char *pass = "88888888";

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  if (mdns.begin("esp8266", WiFi.localIP()))
  Serial.println("MDNS responder started");
  
  server.on("/", TrangChu);
  server.on("/left", left);
  server.on("/right", right);
  server.on("/forward", front);
  server.on("/reverse", back);
  server.begin();
}
void loop()
{
  server.handleClient();
}