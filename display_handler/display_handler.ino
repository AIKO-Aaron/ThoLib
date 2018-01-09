#include "FastLED.h"


#define WIDTH 10
#define HEIGHT 15

#define NUM_LEDS 450

CRGB leds[NUM_LEDS];
uint32_t setup_input = 0;

#define WRITE_COLOR(x, y, color) leds[y * WIDTH + (y % 2 == 1 ? WIDTH - x - 1 : x)] = color

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, 17>(leds, NUM_LEDS);
}

void loop() {
  if (setup_input == 0x30313233) {
    uint32_t input = Serial.read() | Serial.read() << 8 | Serial.read() << 16;
    uint8_t pos = Serial.read();
    
    uint8_t x = pos & 0x0F;
    uint8_t y = pos >> 4;

    if(x == 0xF && y == 0xF)
    {
      //Special treatment
      switch(input)
      {
        case 0xFFFFFF: // reset (NYI)
          break;
        case 0x00DEAD:
          memset(leds, 0, NUM_LEDS * 4);
        default:
          break;
      }
    }
    else WRITE_COLOR(x, y, input);

    Serial.print("Received: ");
    Serial.println(input, HEX);
    
    // FastLED.show(); // Update display...
  } else {
    setup_input = (setup_input >> 8) | ((uint32_t) Serial.read() << 24); // append last byte, only changed here
    if (setup_input == 0x30313233) {
      Serial.print('A'); // Acknowledge existence of raspi
    } else Serial.println(setup_input);
  }
}
