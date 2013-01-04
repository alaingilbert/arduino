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

#ifndef _H_I2c_bv_h
#define _H_I2c_bv_h

#include "Wire.h"
#include "Arduino.h"

#define I2CMD_TEST 0x55
#define I2CMD_EEREAD 0x90
#define I2CMD_EEWRITE 0x91
#define I2CMD_EEEND 0x93
#define I2CMD_SLEEP 0x94
#define I2CMD_RESET 0x95
#define I2CMD_CHANGEADRT 0x98 // temporary
#define I2CMD_CHANGEADRP 0x99
#define I2CMD_VERSION 0xA0
#define I2CMD_DEVICEID 0xA1



class I2c_bv : public TwoWire
{
    public:
        I2c_bv(char i2c_addr);
        char test();
        void resetaddress(char newaddr);
        void eeread(char eeAdr, char *buf, char bytes);
        void eewrite(char eeAdr, char value);
        void sleep();
        void reset();
        void setaddress(char newAddress);
        int deviceid();
        int version();
        int i2_16bit();
    private:    
        char _i2adr;
};

#endif
