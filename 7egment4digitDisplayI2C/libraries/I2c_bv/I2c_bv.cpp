/*
  I2C Common commands for most devices from ByVac
  Copyright (c) 2011 Jim Spence.  All right reserved.
  www.byvac.com - see terms and conditions for using hardware
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/  

#include "Arduino.h"
#include "I2c_bv.h"
 
// **************************************************************
// **************************************************************
I2c_bv::I2c_bv(char i2adr)
{
  _i2adr=i2adr;  
  Wire.begin(); // join i2c bus 
}

// ==============================================================
// I2C utilities
// ==============================================================
// ==============================================================
// **************************************************************
// gets a 16 bit value from the i2c bus
// **************************************************************
int I2c_bv::i2_16bit()
{
int rv;
  Wire.requestFrom(_i2adr, 2); // returns 2 bytes
  rv=Wire.read()*256; // high byte
  rv+=Wire.read(); // low byte
  Wire.endTransmission();
  return rv;
}

// ==============================================================
// I2C Common to most hybrid devices
// ==============================================================
// ==============================================================

// **************************************************************
// test, returns and incrementing value each time it is called
// verifies that device is okay
// returns 1 if okay
// **************************************************************
char I2c_bv::test()
{
    Wire.beginTransmission(_i2adr);
    Wire.write(I2CMD_TEST);  // send test command
    Wire.endTransmission();
    // use 16 bit 1*256+2 = 258
    if(i2_16bit()==258) return 1;
    else return 0;
}

// **************************************************************
// resets address in case of change
// **************************************************************
void I2c_bv::resetaddress(char newaddr)
{
    _i2adr=newaddr;
}

// **************************************************************
// read eeprom
// starting from eeAdr
// for number of bytes
// into provided buffer
// **************************************************************
void I2c_bv::eeread(char eeAdr, char *buf, char bytes)
{
char *bp=buf;
    Wire.beginTransmission(_i2adr);
    Wire.write(I2CMD_EEREAD);  // send command
    Wire.write(eeAdr);
    Wire.endTransmission();
    // restart and read into buffer
    Wire.requestFrom(_i2adr, bytes); // returns n bytes
    *(bp++)=Wire.read();
    Wire.endTransmission();
}    
    
// **************************************************************
// write to eeprom
// writes 1 byte to selected address
// **************************************************************
void I2c_bv::eewrite(char eeAdr, char value)
{
    Wire.beginTransmission(_i2adr);
    Wire.write(I2CMD_EEWRITE);  // send command
    Wire.write(eeAdr);
    Wire.write(value);
    Wire.endTransmission();
}

// **************************************************************
// puts device to sleep
// **************************************************************
void I2c_bv::sleep()
{
    Wire.beginTransmission(_i2adr);
    Wire.write(I2CMD_SLEEP);  // send command
    Wire.endTransmission();
}

// **************************************************************
// reset
// **************************************************************
void I2c_bv::reset()
{
    Wire.beginTransmission(_i2adr);
    Wire.write(I2CMD_RESET);  // send command
    Wire.endTransmission();
}

// **************************************************************
// sets I2C address - note will not respond to old I2C address
// after a reset
// **************************************************************
void I2c_bv::setaddress(char newAddress)
{
  Wire.beginTransmission(_i2adr);
  Wire.write(I2CMD_CHANGEADRP);  // new address comand
  Wire.write(newAddress);
  Wire.write(0x55);
  Wire.write(0xaa);
  Wire.write(_i2adr << 1); // specify 8 bit
  Wire.endTransmission();
}

// **************************************************************
// get device id, this should be 4627
// **************************************************************
int I2c_bv::deviceid()
{
  Wire.beginTransmission(_i2adr);
  Wire.write(I2CMD_DEVICEID);  // device id comand
  Wire.endTransmission();
  return i2_16bit();
}

// **************************************************************
// get device firmware version as 16 bit int
// **************************************************************
int I2c_bv::version()
{
  Wire.beginTransmission(_i2adr);
  Wire.write(I2CMD_VERSION);  // firmware comand
  Wire.endTransmission();
  return i2_16bit();
}
