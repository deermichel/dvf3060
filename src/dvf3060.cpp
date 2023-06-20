#include "dvf3060.h"
#include <stdio.h>

// initialize device
void DVF3060::init() const {
    // init controller
    mController.init();

    // set display mode
    mController.setDisplayMode(PT6311_MODE_G12_S16);

    // display on
    mController.setDisplayControl(true, 7);

    // clear
    uint8_t buffer[48] = {};
    mController.writeDisplayData(buffer, 48, 0);

    HAL hal;
    
    hal.printUART("DVF3060 initialized\n");
    while (1) {
        isKeyPressed(0);

        hal.delay(100);
    }
}

// is key pressed
bool DVF3060::isKeyPressed(uint8_t key) const {
    uint8_t keyData[2] = {};
    mController.readKeyData(keyData, 2);
    uint8_t aggregated = keyData[0] | (keyData[1] >> 7); // merge stop key into first byte
    return (aggregated & key) != 0;
}
