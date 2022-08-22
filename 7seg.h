#pragma once

#define CATHODE true
#define ANODE   false

/**
 * @anchor segment_layout
 * @par Segment Layout
 * @verbatim
+---7---+
|       |
2       6
|       |
+---1---+
|       |
3       5
|       |
+---4---+  0
   @endverbatim
 */
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

  /**
   * @brief Construct a new object representing a 7-segment display
   *
   * @param cathode  true if display is common cathode. Also possible to use
   *                 CATHODE or ANODE macros
   * @param segments Array of pin numbers used to address individual display
   *                 segments, in descending order according to the
   *                 @ref segment_layout "Segment Layout"
   * @param digit0, digit1, digit2, digit3
   *        pin number used to address Nth digit from the left,
   *        i.e. digit0 is the least significant digit
   */
  SegmentDisplay(bool cathode, const int segments[8],
                 int digit0, int digit1, int digit2, int digit3);
  SegmentDisplay(bool cathode, const int segments[8], int digit0, int digit1, int digit2);
  SegmentDisplay(bool cathode, const int segments[8], int digit0, int digit1);
  SegmentDisplay(bool cathode, const int segments[8], int digit0);

  /**
   * @brief Low-level write
   *
   * @param digit which digit to write to
   * @param bits  which segments to light up. The
   *              @ref segment_layout "Segment Layout" section maps between bits
   *              and segments. 0 is the least-significant bit.
   * @return true on success
   */
  bool raw_write(int digit, unsigned char bits);

  /**
   * @brief Set the desired refresh frequency
   *
   * @note Note that this is in fact the theoretical maximum frequency the
   *       display will operate at. The real frequency is dependent on how
   *       often the @ref refresh method is called.
   *
   * @param frequency in Hz
   * @return true on success
   */
  bool set_freq(int frequency);

  /**
   * @brief Refresh the display
   *
   * This method should be called repeatedly in a loop as fast as possible, else
   * the display will freeze, showing only one digit lit up.
   */
  void refresh();

  /**
   * @brief Write a number to the display.
   *
   * @param n The number to be written
   * @return true on success.
   */
  bool write_num(int n);
};
