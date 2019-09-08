void displayMainScreen()
{
  lcd.setCursor(0, 1); lcd.print("Weather Station Menu");
  lcd.setCursor(1, 3); lcd.print("PRESS "); lcd.write(byte(1)); lcd.print(" to Continue");
}

void display1stMenuScreen()
{
  lcd.clear();
  lcd.setCursor(3, 0); lcd.print("Weather Station ");
  lcd.setCursor(1, 1); lcd.print("1. Temperature");
  lcd.setCursor(1, 2); lcd.print("2. Humidity");
  lcd.setCursor(1, 3); lcd.print("3. Wind");
}

void display2ndMenuScreen()
{
  lcd.clear();
  lcd.setCursor(1, 0); lcd.print("5. Others#1");
  lcd.setCursor(1, 1); lcd.print("6. Others#2");
}



