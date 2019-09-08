#include <Keypad.h>                     //6950,750b
#include <Wire.h>                       //5756,630b - 5744,590b - 5638,590b
#include <LiquidCrystal_PCF8574.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_PCF8574 lcd(0x3F);

byte arrowDown[8] = {B00000, B01110, B01110, B01110, B11111, B01110, B00100}; // Custom characters for LCD
byte cursorLCD[8] = {B00000, B00000, B00110, B01111, B01111, B00110, B00000};
byte white[8]     = {B00000, B00000, B00000, B00000, B00000, B00000, B00000};
byte water[8]     = {B00000, B00100, B01110, B01110, B11111, B11111, B11111, B01110};
byte temp[8] = {
  0b00100,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b10001,
  0b01110
};

byte wind[8] = {
  0b01010,
  0b10101,
  0b00000,
  0b01010,
  0b10101,
  0b00000,
  0b01010,
  0b10101
};

uint8_t showMenu;

void setup()
{
  Serial.begin(9600);
  setupMyLcd();
  showMenu = 1;
  Serial.print("started ");
}

void loop()
{
  char resultButton = 'n';
  if (showMenu == 1)
  {
    displayMainScreen();
    getButtonPush( resultButton, 0, 200);
    if (resultButton == 'd') 
      LCDMenu();
  }
  Serial.print("loop repeated");
}

void LCDMenu()
{
  char resultButton;
  int posCursor = 1, opcMenu = -2;
  display1stMenuScreen();

  do
  {
    resultButton == 'n';
    lcd.setCursor(0, posCursor);     lcd.write(byte(0));
    getButtonPush( resultButton, 0, 200);

    // Moves the cursor up or down:
    if (resultButton == 'u')
      LCDMoveCursor(&posCursor, 3, 'r');                  // Subtract a position to cursor
    else if (resultButton == 'd')         // It adds a position to cursor
      LCDMoveCursor(&posCursor, 3, 's');
    else if (resultButton == 'r')
      opcMenu = posCursor;
    else if (resultButton == 'l')
    {
      lcd.clear();
      opcMenu = -1;
    }

    switch ( opcMenu )
    {
      case 0:
        opcMenu = -2;
        break;
      case 1:
        LCDmenu1Temp();
        opcMenu = -2;
        break;
      case 2:
        LCDMenu2Humidity();
        opcMenu = -2;
        break;
      case 3:
        LCDMenu3Wind();
        opcMenu = -2;
        break;
    };
  } while (opcMenu != -1);

}

