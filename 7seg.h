#pragma once

#define CATHODE true
#define ANODE   false

class SegmentDisplay
{
  int seg_pins[8];
  int digi_num;
  int digi_cur = 0;
  int digits[4];
  bool common_cathode;
  unsigned char segs[4] = {0, 0, 0, 0};
  int freq = 60;
  unsigned long last_refresh = 0;

  SegmentDisplay(bool cathode, const int segments[8],
                 int digit0, int digit1, int digit2, int digit3, int used);

public:
  unsigned char digit_lookup[10] = {
    0b11111100u,
    0b01100000u,
    0b11011010u,
    0b11110010u,
    0b01100110u,
    0b10110110u,
    0b10111110u,
    0b11100000u,
    0b11111110u,
    0b11110110u
  };

  SegmentDisplay(bool cathode, const int segments[8],
                 int digit0, int digit1, int digit2, int digit3);
  SegmentDisplay(bool cathode, const int segments[8], int digit0, int digit1, int digit2);
  SegmentDisplay(bool cathode, const int segments[8], int digit0, int digit1);
  SegmentDisplay(bool cathode, const int segments[8], int digit0);

  bool raw_write(int digit, unsigned char bits);

  bool set_freq(int frequency);

  void refresh();

  bool write_num(int n);
};
