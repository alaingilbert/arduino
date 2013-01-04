#include <bv4513_I.h>
#include <Wire.h>
#include <I2c_bv.h>

// 7 bit adddress is used
BV4513_I seg(0x31);

void setup() {
  seg.bright(10);
  seg.cls();
}

void loop() {
  int count = 12;
  while (count >= 0) {
    seg.number(0, (count / 100) % 10);
    seg.number(1, (count / 10) % 10);
    seg.number(2, (count / 1) % 10);
    seg.dp(2, 1);
    for (int mil = 9; mil >= 0; mil--) {
      seg.number(3, (mil / 1) % 10);
      delay(100);
    }
    count--;
  }
  delay(10000);
}
