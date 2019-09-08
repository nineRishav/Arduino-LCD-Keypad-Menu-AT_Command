#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
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

void setup()
{
  Serial.begin(9600);
  setupMyLcd();
}

void loop()
{
  char key = keypad.getKey();

  if (key)
  {
    Serial.print(key);
    lcd.print(key);
  }
}

void setupMyLcd()
{
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

  if (error == 0) {
    Serial.println(F(" : LCD found."));
  }
  else {
    Serial.println(F(" : LCD not found."));
  }
  lcd.begin(width, height);
  lcd.setBacklight(255);
  lcd.clear();
  lcd.home();
}

