Seven Segment Display Library
=============================

Simple Arduino library for interfacing with seven segment displays. Written for
use with [5641AH](http://www.xlitx.com/datasheet/5641AH.pdf), but it might work
with other displays even without modification.

How To Use
----------
```cpp
/** @file sketch.ino */
#include "7seg.h"

int segment_pins[] = {1, 2, 3, 4, 5, 6, 7, 8};

SegmentDisplay display{
    CATHODE,
    segment_pins,
    10, 11, 12, 13
};

void setup() {
    display.write_num(1729);
}

void loop() {
    display.refresh();
}
```
For more information, see `7seg.h`

License
-------
This software is licensed under the MIT License (MIT). For full license text,
see the [`LICENSE.txt`](LICENSE.txt) file.
