#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F);  
# define ledpin 13

int show;
String str;
char c ;
int previousMillis = 0;        // will store last time LED was updated
int interval = 200;           // interval at which to blink (milliseconds)
void setup()
{
  int error;
  Serial.begin(115200);
  Serial.println("LCD...");
  while (! Serial);
  Serial.println("Dose: check for LCD");
  pinMode(ledpin,OUTPUT);
  Wire.begin();
  Wire.beginTransmission(0x3F);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");

  } else {
    Serial.println(": LCD not found.");
  }

  lcd.begin(20, 4); // initialize the lcd
  show = 0;
}

void loop()
{
  lcd.blink();
  unsigned int currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
    lcd.noBlink();
  }
  lcd.setBacklight(255);
  
  while(Serial.available())
    {  
      char c = Serial.read();
        
      if(c =='\n')
        {
          lcd.clear();
          lcd.home();
          char responce[60];
          str.toCharArray(responce,60);
          uint8_t i=0;
          while(responce[i] != '\0')
          {
            lcd.print(responce[i]);
            digitalWrite(ledpin,HIGH);
            lcd.blink();
            delay(50);
            digitalWrite(ledpin,LOW);
            delay(50);
            lcd.noBlink();
            i++;
            }
             
          str = "";
         }
         else
         {
          str +=c;
          }
      }
}
