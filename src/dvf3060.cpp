#include "dvf3060.h"

// initialize device
void DVF3060::init() const {
    // init controller
    mController.init();

    // set display mode
    mController.setDisplayMode(PT6311_MODE_G12_S16);

    // display on
    mController.setDisplayControl(true, 7);

    // clear
    uint8_t buffer[48] = {0};
    mController.writeDisplayData(buffer, 48, 0);

    uint8_t keydata[4];
    while (1) {
        // read key data
        mController.readKeyData(keydata, sizeof(keydata));

        if (keydata[0] || keydata[1] || keydata[2] || keydata[3]) {
            mController.writeDisplayData(0x00, 3);
        } else {
            mController.writeDisplayData(0xFF, 3);
        }

        // HAL().delay(100);
    }
}
