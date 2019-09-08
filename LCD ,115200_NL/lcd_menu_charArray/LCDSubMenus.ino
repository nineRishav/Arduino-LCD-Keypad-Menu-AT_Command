void LCDmenu1Temp()
{
  char resultButton[7];
  int posCursor = 1, opcMenu = -2;
  uint8_t tempValue = 25;
  //Menu

  lcd.clear();
  lcd.print(" Adjust Temperature");
  lcd.setCursor(5, 1);
  lcd.print("Press UP/DOWN");

  do {
    strcpy(resultButton, "null");
    getButtonPush( resultButton, 0, 200);

    // Selection cursor indicating the option :
    lcd.setCursor(0, posCursor); lcd.write(byte(0));

    if (!strcmp(resultButton, "up") || !strcmp(resultButton, "bottom"))
      opcMenu = posCursor;

    if (!strcmp(resultButton, "up"))
    {
      tempValue++;
      lcd.setCursor(10, 2);    lcd.print(tempValue);
      Serial.println(tempValue);
    }
    if (!strcmp(resultButton, "bottom"))
    {
      tempValue--;
      lcd.setCursor(10, 2);    lcd.print(tempValue);
      Serial.println(tempValue);
    }
    else if (!strcmp(resultButton, "left"))
    {
      // operate on temp value before leaving
      lcd.setCursor(5, 3);
      lcd.print("New ");  lcd.write(byte(3)); lcd.print(tempValue);
      Serial.print(tempValue);
      opcMenu = -1;
    }

  } while (opcMenu != -1);

  display1stMenuScreen();
}

void LCDMenu2Humidity()
{
  lcd.setCursor(19,3);
  lcd.print(" ");
  lcd.setCursor(19, 2);
  lcd.write(byte(4));
//  Serial.print("print water");
//  unsigned long int previous = 0;
//  unsigned long int current = millis();
//  if (current - previous > 2000)
//  {
//    lcd.setCursor(19, 2);
//    lcd.write(byte(4));
//    Serial.print("inside water");
//    previous = current;
//  }

}

void LCDMenu3Wind()
{
  lcd.setCursor(19,2);
  lcd.write(byte(2));
  lcd.setCursor(19, 3);
  lcd.write(byte(5));

}

