#ifndef DVF3060_H
#define DVF3060_H

#include "dvf3060_font.h"
#include "pt6311.h"

// display buffer size in bytes, addresses 0x00-0x22
#define DVF3060_BUF_SIZE 35

// display max characters
#define DVF3060_MAX_CHARS 10

// keys
#define DVF3060_KEY_STOP 0x01
#define DVF3060_KEY_PLAY 0x04
#define DVF3060_KEY_EJECT 0x08
#define DVF3060_KEY_NEXT 0x10
#define DVF3060_KEY_PREV 0x20
#define DVF3060_KEY_FF 0x40
#define DVF3060_KEY_REW 0x80

// dvf3060 front panel
class DVF3060 {
public:
    // initialize device
    void init();

    // clear display
    void clearDisplay();

    // set icon
    void setIcon(DVF3060_ICON icon);

    // clear icon
    void clearIcon(DVF3060_ICON icon);

    // set character
    void setChar(char c, uint8_t position);

    // clear character
    void clearChar(uint8_t position);

    // return key state
    uint8_t getKeyState() const;

private:
    // controller instance
    PT6311 mController;

    // display buffer
    uint8_t mBuffer[DVF3060_BUF_SIZE] = {};
};

#endif // DVF3060_H
