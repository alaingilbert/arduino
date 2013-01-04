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

#ifndef _H_bv4513_I_h
#define _H_bv4513_I_h

//#include "Wire.h"
#include "I2c_bv.h"
#include "Arduino.h"

#define MAX_DIGITS 3
#define MIN_DIGITS 0


class BV4513_I : public I2c_bv
{
    public:
        BV4513_I(char i2adr);
        void bright(char brightness);
        void cls();
        void sendbyte(char digit, char value);
        void number(char digit, char value);
        void dp(char disgit, char dpon);
    private:    
        int i2_16bit();
        char _i2adr;
};

#endif
