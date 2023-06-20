#include "dvf3060.h"

// initialize device
void DVF3060::init() const {
    // init controller
    mController.init();

    // set display mode
    mController.setDisplayMode(PT6311_MODE_G12_S16);
}
