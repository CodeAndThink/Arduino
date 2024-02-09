#include<SPI.h>
#include<MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>  
#include <ThreeWire.h>  
#include <RtcDS1302.h>

#define SS_PIN 10
#define RST_PIN 9
#define change_mode_pin A0
#define servo_pin 3

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
MFRC522 mfrc522(SS_PIN,RST_PIN); // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo; 
RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
RtcDateTime now = Rtc.GetDateTime();

const int mode = 0;

void mode_state_0()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mode 0");
  lcd.setCursor(0, 1);
  lcd.print("access!");
  Serial.println("Mode 0 access");
  Serial.println();
  myservo.write(0);
  delay(200);
  lcd.clear(); 
}
void mode_state_1()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mode 1");
  lcd.setCursor(0, 1);
  lcd.print("access!");
  Serial.println("Mode 1 access");
  Serial.println();
  myservo.write(89);
  delay(200);
  lcd.clear();
}
void mode_state_2()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mode 2");
  lcd.setCursor(0, 1);
  lcd.print("access!");
  Serial.println("Mode 2 access");
  Serial.println();
  myservo.write(179);
  delay(200);
  lcd.clear();
}
void modes(){
  while(1){
    int mode = map(analogRead(change_mode_pin),0,1018,0,3);
    if(mode == 0){
      mode_state_0();
    }else if(mode == 1){
      mode_state_1();
    }else if(mode == 2){
      mode_state_2();
    }else{
      mode_state_time();
    }
  }  
}
void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(datestring);

}
void mode_state_time()
{
  Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }

    printDateTime(now);
    Serial.println();

    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }
  delay(1);
}
void setup()
{
  Serial.begin(9600); // Initiate a serial communication
  SPI.begin();     // Initiate  SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Online");
  myservo.attach(servo_pin);
}
void loop()
{
  // Look for new cards
  if(!mfrc522.PICC_IsNewCardPresent())
  {
   return;
  }
  // Select one of the cards
  if(!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content="";
  byte letter;
  for(byte i=0;i<mfrc522.uid.size;i++)
  {
    Serial.print(mfrc522.uid.uidByte[i]<0x10?" 0":" ");
    Serial.print(mfrc522.uid.uidByte[i],HEX);
    content.concat(String(mfrc522.uid.uidByte[i]<0x10?" 0":" "));
    content.concat(String(mfrc522.uid.uidByte[i],HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if(content.substring(1)=="82 B7 86 4E")//change here the UID of the card/cards that you want to give access
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Authorized");
    lcd.setCursor(0, 1);
    lcd.print("access!");
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
    lcd.clear();
    modes();
  }
  else {
    Serial.println(" Access denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access");
    lcd.setCursor(0, 1);
    lcd.print("denied!");
    Serial.println();
    delay(3000);
    lcd.clear();
  }
}