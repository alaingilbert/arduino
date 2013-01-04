#include <math.h>

#include <bv4513_I.h>
#include <Wire.h>
#include <I2c_bv.h>

// 7 bit adddress is used
BV4513_I seg(0x31);

#define ThermistorPIN 0                 // Analog Pin 0

float pad = 9850;                       // balance/pad resistor value, set this to
                                        // the measured resistance of your pad resistor
float thermr = 10000;                   // thermistor nominal resistance

float Thermistor(int RawADC) {
  long Resistance;
  float Temp;  // Dual-Purpose variable to save space.

  Resistance=((1024 * pad / RawADC) - pad);
  Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius
  // Uncomment this line for the function to return Fahrenheit instead.
  //temp = (Temp * 9.0)/ 5.0 + 32.0;         // Convert to Fahrenheit
  return Temp;                                      // Return the Temperature
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temp;
  temp = Thermistor(analogRead(ThermistorPIN));
  temp = temp - 0;
  int temp2 = round(temp);
  Serial.print(temp);
  Serial.print(", ");
  Serial.println(temp2);
  //temp = (temp * 9.0)/ 5.0 + 32.0;                  // converts to  Fahrenheit
  //Serial.print(", Fahrenheit: ");
  //Serial.print(temp,1);    // display  Fahrenheit
  seg.cls();
  if (temp2 < 0) {
    seg.sendbyte(1, 0x40);
  }
  temp2 = abs(temp2);
  int one = temp2 < 10 ? 0 : (temp2 / 10) % 10;
  int two = temp2 < 1  ? 0 : (temp2 / 1) % 10;
  seg.number(2, one);
  seg.number(3, two);
  //seg.dp(2, 1);
  //seg.number(3, 1);
  delay(500);
}
