#include <bv4513_I.h>
#include <Wire.h>
#include <I2c_bv.h>

// 7 bit adddress is used
BV4513_I seg(0x31);

void setup()
{
}

void loop()
{
char count, digit;  
// counting
  seg.cls();
  for(digit=0;digit<4;digit++) {
    for(count=0;count<16;count++) {
      seg.number(digit,count);
      seg.dp(digit,1);
      delay(500);
    }
    seg.dp(digit,0);
  }
// spin
  delay(1500);
  seg.cls();
  for(digit=0;digit<4;digit++) {
    seg.sendbyte(digit,1);
    delay(200);
    seg.sendbyte(digit,2);
    delay(200);
    seg.sendbyte(digit,4);
    delay(200);
    seg.sendbyte(digit,8);
    delay(200);
    seg.sendbyte(digit,0x10);
    delay(200);
    seg.sendbyte(digit,0x20);
    delay(200);
  }
// brightness  
  delay(1500);
  seg.cls();
  for(count=0;count<26;count++) {
    seg.bright(count);
    // display number
    seg.number(0,count/10);
    seg.number(1,(count % 10));
    delay(350);
  }
  seg.bright(10); // back to default
  delay(1500);
}

