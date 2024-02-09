#define OnBtn 2
#define OffBtn 3
#define LED 7
int state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(OnBtn, INPUT);
  pinMode(OffBtn, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(OnBtn) == 0)
  {
    state = 1;   
  }
  if(digitalRead(OffBtn) == 0)
  {
    state = 0;  
  }
  if(state == 1)
  {
    digitalWrite(LED, HIGH);
  }
  if(state == 0) 
  {
    digitalWrite(LED, LOW);
  }
}
