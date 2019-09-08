#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F);
#include <Wire.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int access = 0;
int rxPin = 0;                    // RX PIN
int byteGPS = -1;
char linea[300] = "";
char comandoGPR[7] = "$GPRMC";
int cont = 0;
int good = 0;
int conta = 0;
int indices[13];
//RFID
char tag[] = "02005D35C5AF";
char input[12];        // A variable to store the Tag ID being presented
int count = 0;        // A counter variable to navigate through the input[] character array
boolean flag = 0;     // A variable to store the Tag match status
//CUSTOM CHARACTERS
byte arrowDown[8] = {B00000, B01110, B01110, B01110, B11111, B01110, B00100}; // Custom characters for LCD
byte cursorLCD[8] = {B00000, B00000, B00110, B01111, B01111, B00110, B00000};
byte ledOn[8]   = {B00000, B01110, B10001, B10001, B01010, B01110, B01110};
byte white[8]   = {B11111, B11111, B11111, B11111, B11111, B11111, B11111};
//LED
boolean ledB_E = false;
int ledB_I = 0;

int show;

void setup()
{
  int error;

  Serial.begin(9600);
  Serial.println("LCD...");
  while (! Serial);
  Serial.println("Dose: check for LCD");
  Wire.begin();
  Wire.beginTransmission(0x3F);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");

  } else {
    Serial.println(": LCD not found.");
  } // if

  lcd.begin(20, 4);
  show = 0;

  lcd.createChar(0, cursorLCD);
  lcd.createChar(1, arrowDown);
  lcd.createChar(2, ledOn);
  lcd.createChar(3, white);
  Serial.println("start");
}


void loop()
{
  if (show == 0)
  {
    lcd.setBacklight(255);
    // Save the read result of a push by keyboard:
    char resultButton[7] = "null";
    // Home screen printing :
    lcd.setCursor(7, 1); lcd.print("WELCOME");
    lcd.setCursor(7, 3); lcd.print("PRESS "); lcd.write(byte(1));

    // Check if you pressed a button :
    getButtonPush( resultButton, 0, 200);

    // If the key is pressed down , you enter the menu:
    if ( !strcmp(resultButton, "bottom"))
      LCDmenu();
  }
}

void LCDmenu()
{
  char resultButton[7];
  int posCursor = 0, opcMenu = -2;
  // Menu
  lcd.clear();
  lcd.setCursor(1, 0); lcd.print("1.LED");
  lcd.setCursor(1, 1); lcd.print("2.COLLISSION");
  lcd.setCursor(1, 2); lcd.print("3.RFID");
  lcd.setCursor(1, 3); lcd.print("4.GPS");


  // While not tap out , will not come to your home screen :
  do {
    strcpy(resultButton, "null");
    getButtonPush( resultButton, 0, 200);

    // Cursor indicating the selected option:
    lcd.setCursor(0, posCursor); lcd.write(byte(0));

    // Moves the cursor up or down:
    if (!strcmp(resultButton, "up"))
      LCDMueveCursor(&posCursor, 4, 'r'); // Subtract a position to cursor

    else if (!strcmp(resultButton, "bottom")) // It adds a position to cursor
      LCDMueveCursor(&posCursor, 4, 's');

    if (posCursor == 4) 
    {
      lcd.clear();
      lcd.setCursor(1, 0); lcd.print("5.SPEEDOMETER");
      lcd.setCursor(1, 1); lcd.print("6.VOLTMETER");
    }
    else if (!strcmp(resultButton, "right"))
      opcMenu = posCursor;
    // Pressing on the right (to access that option ) the selected menu option is updated as where the cursor now .
    //Exit Button
    if (!strcmp(resultButton, "left"))
    {
      lcd.clear();
      opcMenu = -1;
    }
    // Depending on the selected menu option, you call another menu or closes the current menu :
    switch ( opcMenu )
    {
      case 0:       // You access the menu on and off the LEDs.
        LCDmenu0();
        opcMenu = -2;
        break;
      case 1:       // Access to the setting menu brightness LEDs.
        LCDmenu1();
        opcMenu = -2;
        break;
      case 2:
        LCDmenu2();
        opcMenu = -2;
        break;
      case 3:
        LCDmenu3();
        opcMenu = -2;
        break;
      case 4:       // Exit to the main screen .
        lcd.clear();
        opcMenu = -2;
        lcd.setCursor(1, 0); lcd.print("5.SPEEDOMETER");
        lcd.setCursor(1, 1); lcd.print("6.VOLTMETER");
        break;
    };
  }
  while (opcMenu != -1);
}

// MENU FOR ON AND OFF THE LEDs
void LCDmenu0()
{
  char resultButton[7];
  int posCursor = 0, opcMenu = -2;

  // Menu
  lcd.clear();
  lcd.setCursor(2, 0); lcd.print("LED");
  lcd.setCursor(2, 1); lcd.print("BACK");

  // Upgrade indicators (drawn bulbs) LCD :
  LCDBombillasLed( ledB_E, 0);

  // While not tap out , will not come to the menu:
  do {
    strcpy(resultButton, "null");
    getButtonPush( resultButton, 0, 200);

    // Selection cursor indicating the option :
    lcd.setCursor(0, posCursor); lcd.write(byte(0));

    // Moves the cursor up or down,:
    if (!strcmp(resultButton, "up"))
      LCDMueveCursor(&posCursor, 1, 'r'); // Subtract a position to cursor

    else if (!strcmp(resultButton, "bottom")) // It adds a position to cursor
      LCDMueveCursor(&posCursor, 1, 's');

    else if (!strcmp(resultButton, "right") || !strcmp(resultButton, "left"))
      opcMenu = posCursor;

    // Depending on the selected menu item , you change the status to an LED or other closes the current menu:
    switch ( opcMenu )
    {
      // LED Blue
      case 0:
        if (!strcmp(resultButton, "right"))
        {
          //digitalWrite(pinLedB, HIGH);
          ledB_E = true;
        }
        else if ( !strcmp(resultButton, "left") )
        {
          //digitalWrite(pinLedB, LOW);
          ledB_E = false;
        }

        opcMenu = -2;
        LCDBombillasLed( ledB_E, 0);
        break;

      // Get Out
      case 1:
        if (!strcmp(resultButton, "right"))
          opcMenu = -1;
        break;
    };
  }
  while (opcMenu != -1);

  // Leaving the Menu 1 the previous menu is printed:
  lcd.clear();
  lcd.setCursor(1, 0); lcd.print("1.LED");
  lcd.setCursor(1, 1); lcd.print("2.COLLISSION");
  lcd.setCursor(1, 2); lcd.print("3.RFID");
  lcd.setCursor(1, 3); lcd.print("4.GPS");
}



// MENU CONTROL COLLISSION SENSOR
void LCDmenu1()
{

}

// MENU CONTROL RFID
void LCDmenu2()
{

  char resultButton[7];
  int posCursor = 0, opcMenu = -2, i, temp1, temp2;


  // Menu
  lcd.clear();

  // While not tap out , will not come to the menu:
  do {
    strcpy(resultButton, "null");
    getButtonPush( resultButton, 0, 200);
    //Exit button
    if (!strcmp(resultButton, "left"))
      opcMenu = -1;
    rfaccess();
  }

  while (opcMenu != -1);
  lcd.clear();
  lcd.setCursor(1, 0); lcd.print("1.LED");
  lcd.setCursor(1, 1); lcd.print("2.COLLISSION");
  lcd.setCursor(1, 2); lcd.print("3.RFID");
  lcd.setCursor(1, 3); lcd.print("4.GPS");
  // The previous menu is printed:

}

// MENU CONTROL GPS
void LCDmenu3()
{

}

// Upgrade indicators (drawn bulbs) LCD :
void LCDBombillasLed( boolean led_E, int fila)
{
  if (led_E)
  {
    lcd.setCursor(18, fila); lcd.write(byte(2));
  }
  else
  {
    lcd.setCursor(18, fila); lcd.print(" ");
  }
}
// Moves the cursor one position in the indicated direction
void LCDMueveCursor(int *pos, int max, char ope)
{
  // Precondition: The ope parameter should be the character ' s ' or 'r' to add or subtract a position.
  //          The max parameter indicates the number of options to choose from.
  // Postcondition : the new cursor value is returned by reference.

  if (ope == 's')
    if (*pos < max)  *pos += 1;
    else      *pos = 0;
  else if (*pos > 0)  *pos -= 1;
  else      *pos = max;

  // Cursors are deleted :
  lcd.setCursor(0, 0); lcd.print(" ");
  lcd.setCursor(0, 1); lcd.print(" ");
  lcd.setCursor(0, 2); lcd.print(" ");
  lcd.setCursor(0, 3); lcd.print(" ");
}

void tone1()
{

}

void tone2()
{

}


void rfaccess()
{

}

// CHECKING PROCEDURE IF YOU HAVE BEEN NEW PRESSES WITH BUTTONS :
void getButtonPush(char *resultButton, int pin, int pause)
{
  // Precondition : The pin parameter must be an analog pin of Arduino .
  // Postcondition : The resultButton parameter is a string returned by reference to the button pressed .
  // The pause parameter must be an integer equal to or greater than 0 .
  // Info : The keyboard used is this : http://giltesa.com/?p=11458 , depending on the type of resistance must be changed to suit the conditional read from Analog pin value.
  char customKey = customKeypad.getKey();

  if (customKey)
  {
    if (customKey == '2')
      strcpy(resultButton, "up");
    else if (customKey == '4')
      strcpy(resultButton, "left");
    else if (customKey == '8')
      strcpy(resultButton, "bottom");
    else if (customKey == '6')
      strcpy(resultButton, "right");

    delay(pause);
  }
}
