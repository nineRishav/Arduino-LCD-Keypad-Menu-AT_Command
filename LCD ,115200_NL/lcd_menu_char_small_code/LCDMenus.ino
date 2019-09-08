void displayMainScreen()
{
  lcd.setCursor(0, 1); lcd.print(F("Weather Station Menu"));
  lcd.setCursor(1, 3); lcd.print(F("PRESS ")); lcd.write(byte(1)); lcd.print(F(" to Continue"));
}

void display1stMenuScreen()
{
  lcd.clear();
  lcd.setCursor(3, 0); lcd.print(F("Weather Station "));
  lcd.setCursor(1, 1); lcd.print(F("1. Temperature"));
  lcd.setCursor(1, 2); lcd.print(F("2. Humidity"));
  lcd.setCursor(1, 3); lcd.print(F("3. Wind"));
}

//void display2ndMenuScreen()
//{
//  lcd.clear();
//  lcd.setCursor(1, 0); lcd.print("5. Others#1");
//  lcd.setCursor(1, 1); lcd.print("6. Others#2");
//}
//



