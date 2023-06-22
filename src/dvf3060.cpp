#include "dvf3060.h"
#include <stdio.h>

// initialize device
void DVF3060::init() {
    // init controller
    mController.init();

    // set display mode, clear, turn on
    mController.setDisplayMode(PT6311_MODE_G12_S16);
    clearDisplay();
    mController.setDisplayControl(true, 7);

    HAL hal;
    hal.printUART("DVF3060 initialized\n");

    uint16_t bit = 0;
    bool pressed = false;
    char output[64] = {};

    // char test
    for (int i = 0; i < 10; i++) {
        setChar(i+26, i);
    }
    return;

    while (1) {
        if (isKeyPressed(DVF3060_KEY_FF) && !pressed) {
            bit++;
            pressed = true;
        } else if (isKeyPressed(DVF3060_KEY_REW) && !pressed) {
            bit--;
            pressed = true;
        } else if (isKeyPressed(DVF3060_KEY_NEXT) && !pressed) {
            bit+=8;
            pressed = true;
        } else if (isKeyPressed(DVF3060_KEY_PREV) && !pressed) {
            bit-=8;
            pressed = true;
        } else {
            pressed = false;
        }

        clearDisplay();
        mController.writeDisplayData(1 << (bit % 8), bit / 8);

        sprintf(output, "address: %02X, bit: %d\n", bit / 8, bit);
        hal.printUART(output);

        hal.delay(100);
    }
}

// clear display
void DVF3060::clearDisplay() {
    for (uint8_t i = 0; i < BUF_SIZE; i++) {
        mBuffer[i] = 0;
    }
    mController.writeDisplayData(mBuffer, BUF_SIZE, 0);
}

// set icon
void DVF3060::setIcon(DVF3060_ICON icon) {
    uint16_t offset = static_cast<uint16_t>(icon);
    uint8_t address = offset / 8;
    uint8_t bitmask = 1 << (offset % 8);

    mBuffer[address] |= bitmask;
    mController.writeDisplayData(mBuffer[address], address);
}

// clear icon
void DVF3060::clearIcon(DVF3060_ICON icon) {
    uint16_t offset = static_cast<uint16_t>(icon);
    uint8_t address = offset / 8;
    uint8_t bitmask = 1 << (offset % 8);

    mBuffer[address] &= ~bitmask;
    mController.writeDisplayData(mBuffer[address], address);
}

// set character
void DVF3060::setChar(char c, uint8_t position) {
    uint8_t offset = 3 * (10 - position);
    uint8_t data0 = DVF3060_CHAR_FONT[c][0];
    uint8_t data1 = DVF3060_CHAR_FONT[c][1];

    mBuffer[offset + 0] |= data0;
    mBuffer[offset + 1] |= data1;
    mController.writeDisplayData(&mBuffer[offset], 2, offset);
}

// is key pressed
bool DVF3060::isKeyPressed(uint8_t key) const {
    uint8_t keyData[2] = {};
    mController.readKeyData(keyData, 2);
    uint8_t aggregated = keyData[0] | (keyData[1] >> 7); // merge stop key into first byte
    return (aggregated & key) != 0;
}
