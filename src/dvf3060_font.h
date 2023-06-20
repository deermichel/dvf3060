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

// icon font (address, bits)
const uint8_t DVF3060_ICON_FONT[][2] = {
    { 0x00, 0x01 }, // RESUME
    { 0x00, 0x02 }, // REW2
    { 0x00, 0x04 }, // REW1
    { 0x00, 0x08 }, // FF1
    { 0x00, 0x10 }, // FF2
    { 0x00, 0x20 }, // INTRO
};

// character font (bits)
const uint8_t DVF3060_CHAR_FONT[][2] = {
                        //   7654 3210 FEDC BA98
                        //   ---- ---- ---- ----
    { 0xC2, 0x61 },     // E 1100 0010 0110 0001
    { 0xE0, 0x31 },     // H 1110 0000 0011 0001
    { 0x40, 0x60 },     // L 0100 0000 0110 0000
    { 0x62, 0x70 },     // O 0110 0010 0111 0000
};

// segment bits
//   ---1---
//  |\  |  /|
//  6 2 3 4 5
//  |  \|/  |
//   -8- -7-
//  |  /|\  |
//  D B A 9 C
//  |/  |  \|
//   ---E---

#endif // DVF3060_FONT_H
