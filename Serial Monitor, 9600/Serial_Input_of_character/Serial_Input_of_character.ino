void setup() {
  Serial.begin(9600);
  Serial.println("Serial Monitor Started");
}

char rx_byte = 0;
String rx_str = "";
char value[3];
uint8_t i=0;

void loop() {
  if (Serial.available() > 0)
  {
    rx_byte = Serial.read();
    if(rx_byte == ',')
    {
      rx_str.toCharArray(value[i],3);
      memset(rx_str,'\0',sizeof(rx_str));
      Serial.println(value[i]);
      i++;
    }
    else if (rx_byte != '\n')
      rx_str += rx_byte;
    else
    {
      // end of string
      Serial.print("Your DATA : ");
      Serial.println(rx_str);
      rx_str = "";
      Serial.println("");
    }
  }
}
//3088 byte used

