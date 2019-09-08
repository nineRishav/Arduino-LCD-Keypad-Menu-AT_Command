#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F);

byte water[8] = {
  0b00000,
  0b00100,
  0b01110,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110
};

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

void setup()
{
  int error;
  Serial.begin(115200);
  Serial.println("LCD...");
  while (! Serial);
  Wire.begin();
  Wire.beginTransmission(0x3F);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");

  } else {
    Serial.println(": LCD not found.");
  }

  lcd.begin(20, 4); // initialize the lcd
  lcd.createChar(3, temp);
  lcd.createChar(1, wind);
  lcd.createChar(2, water);
  lcd.clear();
  lcd.home();
  lcd.setBacklight(255);
  lcd.print("Custom Character");
  lcd.setCursor(1, 1);  lcd.print("Temperature ");  lcd.setCursor(15, 1);  lcd.write(3);  
  lcd.setCursor(1, 2);  lcd.print("Humidity ");     lcd.setCursor(15, 2);  lcd.write(2);
  lcd.setCursor(1, 3);  lcd.print("Wind ");         lcd.setCursor(15, 3);  lcd.write(1);
}

void loop()
{
  
}
