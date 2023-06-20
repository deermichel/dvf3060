#ifndef DVF3060_FONT_H
#define DVF3060_FONT_H

#include <stdint.h>

// icons (index in ICON_FONT)
enum class DVF3060_ICON : uint8_t {
    RESUME,
    REW2,
    REW1,
    FF1,
    FF2,
    INTRO,
};

// icon font (address, bit)
const uint8_t DVF3060_ICON_FONT[][2] = {
    { 0x00, 0x01 }, // RESUME
    { 0x00, 0x02 }, // REW2
    { 0x00, 0x04 }, // REW1
    { 0x00, 0x08 }, // FF1
    { 0x00, 0x10 }, // FF2
    { 0x00, 0x20 }, // INTRO
};

#endif // DVF3060_FONT_H
