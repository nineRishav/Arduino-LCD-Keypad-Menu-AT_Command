#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {8,7,6,5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9,10,11,12}; //connect to the column pinouts of the keypad
//
//byte rowPins[ROWS] = {2,3,4,5}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
   Serial.begin(9600);
}
  
void loop()
{
  char key = keypad.getKey();
  
  if (key)
  {
    Serial.println(key);
  }
}
