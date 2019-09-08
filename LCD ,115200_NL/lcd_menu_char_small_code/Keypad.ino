void getButtonPush(char *resultButton, int pin, int pause)
{
  char customKey = keypad.getKey();

  if (customKey)
  {
    if (customKey == '2')
      resultButton = 'u';
    else if (customKey == '4')
      resultButton = 'l';
    else if (customKey == '8')
      resultButton = 'd';
    else if (customKey == '6')
      resultButton = 'r';
    else
      resultButton = 'n';
    delay(pause);
    Serial.print(resultButton);
  }
}

void LCDMoveCursor(int *pos, uint8_t max, char ope)
{
  // Precondition: The ope parameter should be the character ' s ' or 'r' to add or subtract a position.
  // The max parameter indicates the number of options to choose from.
  // Postcondition : the new cursor value is returned by reference.

  if (ope == 's')
    if (*pos < max)
      *pos += 1;
    else
      *pos = 1;     // may be changed
  else if (*pos > 1)
    *pos -= 1;
  else              // for pos== 0 for cyclic
    *pos = max;

  // Cursors are deleted :
  lcd.setCursor(0, 0); lcd.print(" ");
  lcd.setCursor(0, 1); lcd.print(" ");
  lcd.setCursor(0, 2); lcd.print(" ");
  lcd.setCursor(0, 3); lcd.print(" ");
}


