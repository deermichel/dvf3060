#ifndef DVF3060_H
#define DVF3060_H

#include "pt6311.h"
#include "dvf3060_font.h"

// display buffer size in bytes, addresses 0x00-0x22
#define BUF_SIZE 35

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

    // is key pressed
    bool isKeyPressed(uint8_t key) const;

private:
    // controller instance
    PT6311 mController;

    // display buffer
    uint8_t mBuffer[BUF_SIZE] = {};
};

#endif // DVF3060_H
