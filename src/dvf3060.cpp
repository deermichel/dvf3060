#include "dvf3060.h"

// new vfd using controller
VFD::VFD(Controller &&controller)
    : mController(controller) {}

// initialize device
void VFD::init() const {
    // init controller
    mController.init();

    // set display mode
    mController.setDisplayMode(PT6311_MODE_G12_S16);
}
