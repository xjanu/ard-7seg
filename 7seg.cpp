#include <Arduino.h>
#include "7seg.h"

#define CATHODE true
#define ANODE   false

SegmentDisplay::SegmentDisplay(
    bool cathode, const int segments[8],
    int digit0, int digit1, int digit2, int digit3, int used)
    : common_cathode(cathode), digi_num(used),
      digits({digit0, digit1, digit2, digit3})
{
    memcpy(seg_pins, segments, 8 * sizeof(int));

    // Set up pins
    for (int i = 0; i < digi_num; ++i) {
        pinMode(digits[i], OUTPUT);
        digitalWrite(digits[i], common_cathode ? HIGH : LOW);
    }
    for (int i = 0; i < 8; ++i) {
        pinMode(seg_pins[i], OUTPUT);
        digitalWrite(seg_pins[i], LOW);
    }
}

SegmentDisplay::SegmentDisplay(
    bool cathode, const int segments[8],
    int digit0, int digit1, int digit2, int digit3)
    : SegmentDisplay(cathode, segments, digit0, digit1, digit2, digit3, 4){}

SegmentDisplay::SegmentDisplay(
    bool cathode, const int segments[8], int digit0, int digit1, int digit2)
    : SegmentDisplay(cathode, segments, digit0, digit1, digit2, 0, 3){}

SegmentDisplay::SegmentDisplay(
    bool cathode, const int segments[8], int digit0, int digit1)
    : SegmentDisplay(cathode, segments, digit0, digit1, 0, 0, 2){}

SegmentDisplay::SegmentDisplay(bool cathode, const int segments[8], int digit0)
    : SegmentDisplay(cathode, segments, digit0, 0, 0, 0, 1){}

bool SegmentDisplay::raw_write(int digit, unsigned char bits)
{
    if (digit >= digi_num) {
        return false;
    }
    segs[digit] = bits;
    return true;
}

bool SegmentDisplay::set_freq(int frequency){
    if (freq <= 0) {
        return false;
    }
    freq = frequency;
    return true;
}

void SegmentDisplay::refresh()
{
    unsigned long tick = (1000000ul / freq) / digi_num;
    unsigned long now = micros();
    // micros() overflows every ~70 minutes. If `last_refresh + tick` doesn't
    // yet overflow, but `now` does, we'll just want to refresh anyway.
    if (now < last_refresh + tick && now > last_refresh) {
        return;
    }

    digitalWrite(digits[digi_cur], common_cathode ? HIGH : LOW);
    ++ digi_cur %= digi_num;
    for (int i = 0; i < 8; ++i) {
        digitalWrite(seg_pins[i], (segs[digi_cur] & (0b10000000u >> i)) ? HIGH : LOW);
    }
    digitalWrite(digits[digi_cur], common_cathode ? LOW : HIGH);

    last_refresh = now;
}

bool SegmentDisplay::write_num(int n)
{
    #ifdef NDEBUG
        constrain(n, -pow(10, digi_num - 1), pow(10, digi_num));
    #else
        if (n >= pow(10, digi_num) || n <= -pow(10, digi_num - 1)) {
            return false;
        }
    #endif

    bool minus = n < 0;
    n = abs(n);
    int digit = 0;
    while (n > 0 || digit == 0) {
        raw_write(digit, digit_lookup[n % 10]);
        n /= 10;
        ++ digit;
    }
    if (minus) {
        raw_write(digit, 0b00000010u);
        ++ digit;
    }
    while (digit < digi_num) {
        raw_write(digit, 0);
        ++ digit;
    }

    return true;
}
