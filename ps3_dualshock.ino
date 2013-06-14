/*
** I2C Reader of Hobbytronics USB Host PS3 DualShock Controller
** Created June 2013
**
** This example code is in the public domain.
** www.hobbytronics.co.uk
*/

#define  I2C_ADDRESS 41      // I2C Address of USB Host

#include <Wire.h>
#include "ps3.h"             // PS3 Data structure and functions

unsigned long currentTime;
unsigned long ps3ReadTime;
unsigned long ps3PrintTime;

void setup()
{
  Wire.begin();              // join i2c bus (address optional for master)
  
  //Start Serial port
  Serial.begin(9600);        // start serial for output
  
  // Cycle through the LEDS on the PS3 Controller
  delay(500);
  ps3_led(0x01);      // LED 1 
  delay(500);
  ps3_led(0x02);      // LED 2  
  delay(500);
  ps3_led(0x04);      // LED 3 
  delay(500);
  ps3_led(0x08);      // LED 4 

  // Do some Rumbles
  delay(1000);
  ps3_rumble(1);      // Soft Rumble 
  delay(2000);
  ps3_rumble(2);      // Short Heavy Rumble  
  delay(2000);
  ps3_rumble(3);      // Long Heavy Rumble

  currentTime = millis();
  ps3ReadTime = currentTime;   
  ps3PrintTime = currentTime; 
}

void loop()
{
  unsigned char i;

  currentTime = millis();
    
  if(currentTime >= (ps3ReadTime + 50)){  
    // Get data from PS3 Controller every 50ms
    get_ps3(); 
    ps3ReadTime = currentTime;  // Updates ps3ReadTime
  }
  
  if(currentTime >= (ps3PrintTime + 200))
  { 
    // Print out our data to serial port every 200ms
    print_ps3();
    ps3PrintTime = currentTime;  // Updates ps3PrintTime
  }

}
