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

    uint8_t bit = 0;
    bool pressed = false;
    char output[64] = {};

    setIcon(DVF3060_ICON::RESUME);
    setIcon(DVF3060_ICON::INTRO);

    clearIcon(DVF3060_ICON::RESUME);
    return;

    while (1) {
        if (isKeyPressed(DVF3060_KEY_FF) && !pressed) {
            bit++;
            pressed = true;
        } else if (isKeyPressed(DVF3060_KEY_REW) && !pressed) {
            bit--;
            pressed = true;
        } else {
            pressed = false;
        }

        // mController.writeDisplayData(buffer, 48, 0);
        mController.writeDisplayData(1 << (bit % 8), bit / 8);

        sprintf(output, "address: %02X, bit: %d\n", bit / 8, bit % 8);
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
    uint8_t i = static_cast<uint8_t>(icon);
    uint8_t address = DVF3060_ICON_FONT[i][0];
    uint8_t data = DVF3060_ICON_FONT[i][1];

    mBuffer[address] |= data;
    mController.writeDisplayData(mBuffer[address], address);
}

// clear icon
void DVF3060::clearIcon(DVF3060_ICON icon) {
    uint8_t i = static_cast<uint8_t>(icon);
    uint8_t address = DVF3060_ICON_FONT[i][0];
    uint8_t data = DVF3060_ICON_FONT[i][1];

    mBuffer[address] &= ~data;
    mController.writeDisplayData(mBuffer[address], address);
}

// is key pressed
bool DVF3060::isKeyPressed(uint8_t key) const {
    uint8_t keyData[2] = {};
    mController.readKeyData(keyData, 2);
    uint8_t aggregated = keyData[0] | (keyData[1] >> 7); // merge stop key into first byte
    return (aggregated & key) != 0;
}
