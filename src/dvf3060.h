#ifndef DVF3060_H
#define DVF3060_H

#include "pt6311.h"

// dvf3060 vacuum fluorescent display
class VFD {
public:
    // new vfd using controller
    VFD(Controller &&controller = Controller());

private:
    // controller instance
    Controller mController;
};

#endif // DVF3060_H
