#include "7seg.h"

const int segment_pins[8] = {6, 4, A0, 12, 11, 5, A1, 13};
const int digit_pins[4]   = {10, 7, 8, 9};
const int display_freq    = 300;

SegmentDisplay display{CATHODE, segment_pins, digit_pins[0],
                       digit_pins[1], digit_pins[2], digit_pins[3]};

void setup() {
  display.set_freq(display_freq);
}

void loop() {
  unsigned now = millis();
  display.write_num(now % 10000);
  display.refresh();
}
