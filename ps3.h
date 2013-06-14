/*
  Hobbytronics USB Host - PS3 Data Structure and Functions
  
  Data received from PS3 Controller is stored in a struct
  for easy access to individual bytes
  
*/
#include "Arduino.h"
#define  PS3_DATA_SIZE 35

typedef struct ps3_data {
  unsigned char joy_left_x;
  unsigned char joy_left_y;
  unsigned char joy_right_x;
  unsigned char joy_right_y;
  unsigned char accel_x;
  unsigned char accel_y;  
  unsigned char press_up;
  unsigned char press_right;
  unsigned char press_down;
  unsigned char press_left;
  unsigned char press_lb;
  unsigned char press_rb;
  unsigned char press_lt;
  unsigned char press_rt;
  unsigned char press_triangle;
  unsigned char press_circle;
  unsigned char press_x;
  unsigned char press_square;
  unsigned char btn_left;
  unsigned char btn_down;
  unsigned char btn_right;
  unsigned char btn_up;
  unsigned char btn_start;
  unsigned char btn_joy_right;
  unsigned char btn_joy_left;
  unsigned char btn_select;
  unsigned char btn_square;
  unsigned char btn_x;
  unsigned char btn_circle;
  unsigned char btn_triangle;  
  unsigned char btn_rt;  
  unsigned char btn_lt;  
  unsigned char btn_rb;  
  unsigned char btn_lb;  
  unsigned char btn_ps3;    
} ;

ps3_data ps3;

void get_ps3()
{
  // Get data from PS3 DualShock Controller
  // We only want single byte values (0 to 255)
  // We use a pointer to the ps3 struct we defined so we can populate the data in sequence

  uint8_t *ps3Ptr = (uint8_t *)&ps3;    // Create pointer to ps3 struct
  
  unsigned char data_values_rcvd=0;     // keep track of how many characters received    
  Wire.beginTransmission(I2C_ADDRESS);  // transmit to device
  Wire.write(0);                        // Start receiving data from register 0
  Wire.endTransmission();               // end transmission
  
  // To retrieve all data we need 35 bytes, but restriction in Arduino means
  // we can only get 32 bytes at one go, so we split it into 2 reads
  
  Wire.requestFrom(I2C_ADDRESS, 28);    // request 28 bytes from PS3 
  data_values_rcvd=0; 
  while(Wire.available())
  { 
    *ps3Ptr++ = Wire.read();            // receive a byte and increment pointer address
    data_values_rcvd++;
  }
  Wire.beginTransmission(I2C_ADDRESS);  // transmit to device
  Wire.write(28);                       // Start receiving data from register 28
  Wire.endTransmission();               // end transmission  
  Wire.requestFrom(I2C_ADDRESS, PS3_DATA_SIZE-28);    // request outstanding bytes from PS3 
  while(Wire.available())
  { 
    *ps3Ptr++ = Wire.read();            // receive a byte and increment pointer address
    data_values_rcvd++;
  }  
  
}

void print_ps3(void)
{
  // Print out the complete ps3 data structure.
  // We can access the data structure individually as shown by printing
  // the first two data bytes out .
  // Or we can loop through the structure with a pointer which we have
  // done for the remaining bytes
  
  unsigned char i;
  uint8_t *ps3Ptr = (uint8_t *)&ps3;         // Create pointer to ps3 struct
  
  // Print (or access) specific data items
  Serial.print(ps3.joy_left_x, DEC);         // print the character
  Serial.print(",");                         // print comma
  Serial.print(ps3.joy_left_y, DEC);         // print the character
  Serial.print(",");                         // print comma

  // Print remaining data items using pointer
  ps3Ptr++;                                  // Increment pointer address as we have already
  ps3Ptr++;                                  // printed the first 2 values
  for(i=2;i<PS3_DATA_SIZE;i++)
  {
    Serial.print(*ps3Ptr++, DEC);            // print the data and increment pointer address
    Serial.print(",");                       // print comma
  }
  Serial.println("");                        // print carriage return    
}
  
void ps3_led(unsigned char led)
{
  // Send led data to PS3 controller
  Wire.beginTransmission(I2C_ADDRESS);  // transmit to device
  Wire.write(51);                       // LED data register 51
  Wire.write(led);                      // LED Data
  Wire.endTransmission();               // end transmission
}

void ps3_rumble(unsigned char rumble)
{
  // Send Rumble data to PS3 controller
  Wire.beginTransmission(I2C_ADDRESS);  // transmit to device
  Wire.write(50);                       // rumble data register 50
  Wire.write(rumble);                   // Rumble 
  Wire.endTransmission();               // end transmission
}  
  
