#ifndef DVF3060_FONT_H
#define DVF3060_FONT_H

#include <stdint.h>

// icons (address = i/8, bit = i%8)
enum class DVF3060_ICON : uint16_t {
    RESUME = 0,
    REW2 = 1,
    REW1 = 2,
    FF1 = 3,
    FF2 = 4,
    INTRO = 5,
    PROG = 6,
    PBC = 7,
    AUDIO = 8,
    DVD = 9,
    VCD = 10,
    VIDEO = 11,
    CD = 12,
    MP3 = 13,
    SEC = 24,
    MIN = 72,
    COLON_MIN = 87,
    HOUR = 120,
    COLON_HOUR = 135,
    TRACK = 144,
    DOT_TRACK = 159,
    CHAP = 168,
    TITLE = 216,
    DOT_TITLE = 231,
    GROUP = 240,
    PLAY = 264,
    PAUSE = 265,
    LOCK = 266,
    RANDOM = 267,
    REPEAT = 268,
    ONE = 269,
    ALL = 270,
    A_TO = 271,
    B = 272,
};

// character font (bitmap)
const uint8_t DVF3060_CHAR_FONT[][2] = {
                        //   7654 3210 FEDC BA98 | ascii
                        //   ---- ---- ---- ---- |
    { 0xE2, 0x31 },     // A 1110 0010 0011 0001 | A
    { 0xAA, 0x54 },     // B 1010 1010 0101 0100 | B
    { 0x42, 0x60 },     // C 0100 0010 0110 0000 | C
    { 0x2A, 0x54 },     // D 0010 1010 0101 0100 | D
    { 0xC2, 0x61 },     // E 1100 0010 0110 0001 | E
    { 0xC2, 0x21 },     // F 1100 0010 0010 0001 | F
    { 0xC2, 0x70 },     // G 1100 0010 0111 0000 | G
    { 0xE0, 0x31 },     // H 1110 0000 0011 0001 | H
    { 0x0A, 0x44 },     // I 0000 1010 0100 0100 | I
    { 0x20, 0x70 },     // J 0010 0000 0111 0000 | J
    { 0x50, 0x23 },     // K 0101 0000 0010 0011 | K
    { 0x40, 0x60 },     // L 0100 0000 0110 0000 | L
    { 0x74, 0x30 },     // M 0111 0100 0011 0000 | M
    { 0x64, 0x32 },     // N 0110 0100 0011 0010 | N
    { 0x62, 0x70 },     // O 0110 0010 0111 0000 | O
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
