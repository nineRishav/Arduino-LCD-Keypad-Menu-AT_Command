void LCDmenu1Temp()
{
  char resultButton;
  uint8_t posCursor = 1, opcMenu = -2;
  uint8_t tempValue = 25;
  //Menu

  lcd.clear();
  lcd.print(F(" Adjust Temperature"));
  lcd.setCursor(5, 1);
  lcd.print(F("Press UP/DOWN"));

  do {
    resultButton = 'n';
    getButtonPush( resultButton, 0, 200);

    // Selection cursor indicating the option :
    lcd.setCursor(0, posCursor); lcd.write(byte(0));

    if (resultButton == 'u' || resultButton == 'd')
      opcMenu = posCursor;
      
    if (resultButton == 'u')
    {
      tempValue++;
      lcd.setCursor(10, 2);    lcd.print(tempValue);
      //Serial.println(tempValue);
    }
    if (resultButton == 'd')
    {
      tempValue--;
      lcd.setCursor(10, 2);    lcd.print(tempValue);
      //Serial.println(tempValue);
    }
    else if (resultButton == 'l')
    {
      // operate on temp value before leaving
      lcd.setCursor(5, 3);
      lcd.print("New ");  lcd.write(byte(3)); lcd.print(tempValue);
      //Serial.print(tempValue);
      opcMenu = -1;
    }

  } while (opcMenu != -1);

  display1stMenuScreen();
}

void LCDMenu2Humidity()
{
  lcd.setCursor(19, 3);
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
  lcd.setCursor(19, 2);
  lcd.write(byte(2));
  lcd.setCursor(19, 3);
  lcd.write(byte(5));

}


