// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
}

void loop()
{
  Wire.beginTransmission(0x6D);
  Wire.write(0x01);              // sends one byte
  Wire.endTransmission(); 
  delay(500);
  Wire.beginTransmission(0x6D);
  Wire.write(0x02);              // sends one byte
  Wire.endTransmission(); 
  delay(500);
  Wire.beginTransmission(0x6D);
  Wire.write(0x03);              // sends one byte
  Wire.endTransmission(); 
  delay(500);
  Wire.beginTransmission(0x6D);
  Wire.write(0x04);              // sends one byte
  Wire.endTransmission(); 
  delay(500);
}
