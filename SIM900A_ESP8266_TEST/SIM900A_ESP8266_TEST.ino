 void setup()
    {
      //Begin nodemcu serial-0 channel 
      Serial.begin(9600); 
    }
  void loop()
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
    Serial.print("test"); // SMS body - Sms Text
    delay(1000);
    Serial.println();
    Serial.write(26);                //CTRL+Z Command to send text and end session
    while(1);                        //Just send the text ones and halt 
    }