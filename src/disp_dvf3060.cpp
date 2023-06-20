#include "disp_dvf3060.h"

// new vfd using controller
template <typename CTRL_Impl>
Display_DVF3060<CTRL_Impl>::Display_DVF3060(CTRL_Impl &&controller)
    : mController(controller) {}

// initialize device
template <typename CTRL_Impl>
void Display_DVF3060<CTRL_Impl>::init_() const {
    // init controller
    mController.init();

    // set display mode
    // mController.setDisplayMode(PT6311_MODE_G12_S16);
}
