#ifndef DVF3060_H
#define DVF3060_H

#include "ctrl.h"
#include "disp.h"

// dvf3060 vacuum fluorescent display
template <typename CTRL_Impl>
class Display_DVF3060 : public Display<Display_DVF3060<CTRL_Impl>> {
public:
    // new vfd using controller
    Display_DVF3060(CTRL_Impl &&controller);

    // initialize device
    void init_() const;

private:
    // controller instance
    Controller<CTRL_Impl> mController;
};

#endif // DVF3060_H
