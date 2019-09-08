#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F);
int screenWidth = 20;
int screenHeight = 4;

String line1 = "This is a line scrolling tutorial by Rishav KUMAR";
String line2 = "by Rishav KUMAR";

int stringStart, stringStop = 0;
int scrollCursor = screenWidth;

void setup() {
  lcd.begin(screenWidth, screenHeight);
}

void loop()
{
  lcd.setBacklight(255);
  lcd.setCursor(scrollCursor, 0);
  lcd.print(line1.substring(stringStart, stringStop));
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(500);
  lcd.clear();
  if (stringStart == 0 && scrollCursor > 0)
  {
    scrollCursor--;
    stringStop++;
  }
  else if (stringStart == stringStop)
  {
    stringStart = stringStop = 0;
    scrollCursor = screenWidth;
  }
  else if (stringStop == line1.length() && scrollCursor == 0)
  {
    stringStart++;
  }
  else
  {
    stringStart++;
    stringStop++;
  }
}
