#include "FastLED.h"


#define WIDTH 15
#define HEIGHT 10

#define NUM_LEDS 450

CRGB leds[NUM_LEDS];

void setup() {
  while(!Serial1 || !Serial);
  Serial.begin(230400); // 230400
  Serial1.begin(9600);
  FastLED.addLeds<NEOPIXEL, 17>(leds, NUM_LEDS);
}

void loop() {
  /**while (Serial.available() <= 4) {
    delay(100);
    if(Serial.available() >= 4) break;
    else if(Serial.available() > 0) Serial.read();
  }*/
  //Serial1.println(Serial.available());
  if(Serial.available() < 4) return;
  uint32_t input = Serial.read() | Serial.read() << 8 | Serial.read() << 16;
  uint8_t pos = Serial.read();

  uint8_t x = pos & 0x0F;
  uint8_t y = (pos >> 4) & 0x0F;

  /**Serial1.print(x);
  Serial1.print(", ");
  Serial1.print(y);
  Serial1.print(":");
  Serial1.println(input);*/

  if (x == 0xF && y == 0xF)
  {
    //Special treatment
    switch (input)
    {
      case 0xFFFFFF: // reset (NYI)
        break;
      case 0x00DEAD:
        memset(leds, 0, NUM_LEDS * sizeof(CRGB));
        break;
      default:
        break;
    }
  } else if(x == 0xE && y == 0xF) {
     // input is position
     pos = (input & 0xFF);
     x = pos & 0x0F;
     y = (pos >> 4) & 0x0F;
     leds[2 * (y * WIDTH + (y % 2 == 1 ? WIDTH - x - 1 : x))] = 0xFF000000;
     leds[2 * (y * WIDTH + (y % 2 == 1 ? WIDTH - x - 1 : x)) + 1] = 0xFF000000;
    Serial1.print(x);
    Serial1.print(", ");
    Serial1.print(y);
    Serial1.print(" = ");
    Serial1.println(input);     
  } else {
    leds[2 * (y * WIDTH + (y % 2 == 1 ? WIDTH - x - 1 : x))] = 0xFF000000 | input;
    leds[2 * (y * WIDTH + (y % 2 == 1 ? WIDTH - x - 1 : x)) + 1] = 0xFF000000 | input;

  }
  FastLED.show(); // Update display...
}
