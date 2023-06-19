#include "dvf3060.h"

// new vfd using controller
VFD::VFD(Controller &&controller)
    : mController(controller) {}
