#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F);
void setup()
{
  setupMyLcd();
}

void loop()
{
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("lCD Started");
  delay(2000);
}

void setupMyLcd()
{
  uint8_t error;
  uint8_t width=20,height=4;
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
}

