#include "7seg.h"

const int segment_pins[8] = {6, 4, A0, 12, 11, 5, A1, 13};
const int digit_pins[4]   = {10, 7, 8, 9};
const int display_freq    = 300;

SegmentDisplay display{CATHODE, segment_pins, digit_pins[0],
                       digit_pins[1], digit_pins[2], digit_pins[3]};

void setup() {
  display.set_freq(display_freq);
  for (unsigned i = 0; i < 4; ++i) {
    display.raw_write(i, 0b11111111u);
    unsigned start = millis();
    while (millis() - start < 1000) {
      display.refresh();
    }
    display.raw_write(i, 0b0u);
  }
  for (unsigned char i = 0b10000000; i != 0x00; i >>= 1) {
    display.raw_write(0, i);
    display.raw_write(1, i);
    display.raw_write(2, i);
    display.raw_write(3, i);
    unsigned start = millis();
    while (millis() - start < 1000) {
      display.refresh();
    }
  }
}

void loop() {
  unsigned now = millis();
  display.write_num( (now / 10) % 10000 );
  display.refresh();
}
