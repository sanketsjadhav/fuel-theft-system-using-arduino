#include<SoftwareSerial.h>
SoftwareSerial gsm(16,17);

#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,6,7,8);

char com ;
String caller = "9730609245";

int fuel = 0;

int i = 0;

void setup() {
  Serial.begin(9600);
  gsm.begin(9600);

  lcd.begin(16,2);

  pinMode(9, OUTPUT);
  pinMode(19, INPUT);
}

void loop() {
  fuel = digitalRead(19);

  if(fuel == LOW)
  {
      i++;
      delay(1000);
    }
    else
    {
      i=0;
      digitalWrite(9,LOW);
      lcd.clear();
      lcd.print("----------------");
      delay(100);
      }

    if(i == 1)
    {
      digitalWrite(9,HIGH);

      lcd.clear();
      lcd.print("Fuel Theft !!!!");
      delay(100);

      
      sendAndWait("AT+CMGF=1\r\n");
  delay(1000);
   sendAndWait("AT+CMGS=\"" + caller + "\"\r\n");
   delay(1000);
    sendAndWait("someone tries to theft fuel\r\n");
    delay(500);
    gsm.println(char(26));
      }
}

String sendAndWait(String cmd) {
  const char* com = cmd.c_str();
  Serial.println("[IN]:" + cmd);
  while (gsm.available() > 0) {
    gsm.read();
  }
  gsm.write(com);
  gsm.readStringUntil('\n');
  String res = gsm.readStringUntil('\n');

  while (gsm.available() > 0) {
    gsm.read();
  }
  delay(150);
  Serial.println("[OU]" + res);
  delay(500);
  return res;
}
