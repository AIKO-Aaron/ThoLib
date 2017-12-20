#include "FastLED.h"


#define WIDTH 10
#define HEIGHT 15

#define NUM_LEDS 450

CRGB leds[NUM_LEDS];
uint32_t setup_input;

#define WRITE_COLOR(x, y, color) leds[y * WIDTH + (y % 2 == 1 ? WIDTH - x - 1 : x)] = color

void setup() {
  Serial.begin(19200);
  FastLED.addLeds<NEOPIXEL, 17>(leds, NUM_LEDS);
}

void loop() {
  if (setup_input == 0xDDCCBBAA) {
    uint32_t input = Serial.read() | Serial.read() << 8 | Serial.read() << 16;
    uint8_t pos = Serial.read();
    
    uint8_t x = pos & 0x0F;
    uint8_t y = pos >> 4;

    WRITE_COLOR(x, y, input);
    
    FastLED.show(); // Update display...
  } else {
    setup_input = (setup_input >> 8) | (Serial.read() << 24); // append last byte
    if (setup_input == 0xDDCCBBAA) {
      Serial.print(0x0A);
    }
  }
}
