#include <Keypad.h>                     //6950,750b
#include <Wire.h>
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
}

void loop()
{
  char resultButton[7] = "null";
  if (showMenu == 1)
  {
    displayMainScreen();
    getButtonPush( resultButton, 0, 200);   // to check pressed button
    if (strcmp(resultButton, "bottom") == 0)    // returns zero when matched
      LCDMenu();
  }
}

void LCDMenu()
{
  char resultButton[7];
  int posCursor = 1, opcMenu = -2;
  display1stMenuScreen();

  do
  {
    strcpy(resultButton, "null");
    lcd.setCursor(0, posCursor);     lcd.write(byte(0));
    getButtonPush( resultButton, 0, 200);

    // Moves the cursor up or down:
    if ((strcmp(resultButton, "up") == 0))
    {
      LCDMoveCursor(&posCursor, 3, 'r');                  // Subtract a position to cursor
    }
    else if ((strcmp(resultButton, "bottom") == 0))         // It adds a position to cursor
      LCDMoveCursor(&posCursor, 3, 's');
    else if ((strcmp(resultButton, "right") == 0))
      opcMenu = posCursor;
    else if (strcmp(resultButton, "left") == 0)
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
