void setup()
{
  Serial.begin(9600);
  Serial.println("Serial Monitor started...");
}

char rx_byte = 0;
String rx_str = "";
boolean not_number = false;
uint8_t result;

void loop()
{
  rxSerialData();
}

void rxSerialData()
{
  if (Serial.available() > 0)
  {
    rx_byte = Serial.read();
    if ((rx_byte >= '0') && (rx_byte <= '9'))
      rx_str += rx_byte;

    else if (rx_byte == '\n')
    {
      // end of string
      if (not_number)
        Serial.println("Not a number");
      else
      {
        result = rx_str.toInt();
        Serial.print("Your DATA : ");
        Serial.print(rx_str);
        Serial.println("");
      }
      not_number = false;
      rx_str = "";
    }
    else
    {
      not_number = true;    // flag
    }
  }

}
