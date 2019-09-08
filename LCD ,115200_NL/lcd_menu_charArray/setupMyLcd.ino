void setupMyLcd()
{                                                   //6950,750b
  uint8_t error;
  uint8_t width = 20, height = 4;
  //Serial.begin(115200);
  while (!Serial);
  Serial.println(F("Checking for LCD"));

  Wire.begin();
  Wire.beginTransmission(0x3F);
  error = Wire.endTransmission();
  Serial.print(F("Error: "));
  Serial.print(error);

  if (error == 0) 
  {
    Serial.println(F(" : LCD found."));
  }
  else 
  {
    Serial.println(F(" : LCD not found."));
  }
  lcd.begin(width, height);
  lcd.setBacklight(255);
  lcd.createChar(0, cursorLCD);
  lcd.createChar(1, arrowDown);
  lcd.createChar(2, white);
  lcd.createChar(3, temp);
  lcd.createChar(4, water);
  lcd.createChar(5, wind);
  lcd.clear();
  lcd.home();
}





