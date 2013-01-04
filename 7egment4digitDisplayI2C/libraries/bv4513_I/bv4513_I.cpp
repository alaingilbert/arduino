/*
  BV4513 (I2C) & Serial 7 Seg Dsiplay from ByVac
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
#include "bv4513_I.h"
 
// **************************************************************
// **************************************************************
BV4513_I::BV4513_I(char i2adr):I2c_bv(i2adr)
{
  _i2adr=i2adr;  
}

// ==============================================================
// I2C 7 Segment Display - 4 digit
// ==============================================================
// ==============================================================

// **************************************************************
// command 1
// Sets display brightness
// **************************************************************
void BV4513_I::bright(char brightness)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(brightness > 25) brightness = 25;
  if(brightness < 0) brightness = 0;
  Wire.write(1);  // command
  Wire.write(brightness);
  Wire.endTransmission();
} 

// **************************************************************
// Clears display
// **************************************************************
void BV4513_I::cls()
{ 
  // 
  Wire.beginTransmission(_i2adr);
  Wire.write(2);  // clear comand
  Wire.endTransmission();
} 

// **************************************************************
// Command 3 sends byte to digit. 
// Byte value will reflect the segment that will light up. See
// the data sheet for more details.
// digit is 0 to 3 and addressed the particular tile
// value is the byte to send 0 to 0xff
// **************************************************************
void BV4513_I::sendbyte(char digit, char value)
{
  Wire.beginTransmission(_i2adr);
  if(digit > MAX_DIGITS) digit=MAX_DIGITS;
  if(digit < MIN_DIGITS) digit = MIN_DIGITS;
  Wire.write(3);  // command
  Wire.write(digit); // address
  Wire.write(value); // pattern
  Wire.endTransmission();
}

// **************************************************************
// Command 4 places a number 0-9 on the display at a particular
// address or location. Values:
// 0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F
// 16 or 0x10 will blank the display
// **************************************************************
void BV4513_I::number(char digit, char value)
{
  Wire.beginTransmission(_i2adr);
  if(digit > MAX_DIGITS) digit=MAX_DIGITS;
  if(digit < MIN_DIGITS) digit = MIN_DIGITS;
  if(value > 16) value=16;
  if(value < 0) value=0;
  Wire.write(4);  // command
  Wire.write(digit); // address
  Wire.write(value);
  Wire.endTransmission();
}

// **************************************************************
// command 5
// turns on or off the decimal point
// **************************************************************
void BV4513_I::dp(char digit, char dpon)
{
  Wire.beginTransmission(_i2adr);
  if(digit > MAX_DIGITS) digit=MAX_DIGITS;
  if(digit < MIN_DIGITS) digit = MIN_DIGITS;
  Wire.write(5);  //  command
  Wire.write(digit); // address
  Wire.write(dpon); // if not 0 then on
  Wire.endTransmission();
}

