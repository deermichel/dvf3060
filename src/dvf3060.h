#ifndef DVF3060_H
#define DVF3060_H

#include "pt6311.h"

// dvf3060 front panel
class DVF3060 {
public:
    // initialize device
    void init() const;

private:
    // controller instance
    PT6311 mController;
};

#endif // DVF3060_H
