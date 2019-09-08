#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F);

char c ;
unsigned int previousMillis = 0;        // will store last time LED was updated
uint8_t interval = 250;           // interval at which to blink (milliseconds)
void setup()
{
  setupMyLcd();
}

void loop()
{
  lcd.blink();
  unsigned int currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
    lcd.noBlink();
  }

  while (Serial.available())
  {
    char c = Serial.read();
    String str;
    if (c == '\n')
    {
      lcd.clear();
      lcd.home();
      char responce[80];
      str.toCharArray(responce, 80);
      uint8_t i = 0;
      while (responce[i] != '\0')
      {
        lcd.print(responce[i]);
        lcd.blink();
        delay(100);
        lcd.noBlink();
        i++;
      }

      str = "";     // empty the string
    }
    else
    {
      str += c;
    }
  }
}

void setupMyLcd()
{
  uint8_t error;
  uint8_t width = 20, height = 4;
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("Checking for LCD"));

  Wire.begin();
  Wire.beginTransmission(0x3F);
  error = Wire.endTransmission();
  Serial.print(F("Error: "));
  Serial.print(error);

  if (error == 0) {
    Serial.println(F(" : LCD found."));
  }
  else {
    Serial.println(F(" : LCD not found."));
  }
  lcd.begin(width, height);
  lcd.setBacklight(255);
  lcd.clear();
  lcd.home();
}

