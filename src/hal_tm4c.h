#ifndef HAL_TM4C_H
#define HAL_TM4C_H

#include "hal.h"

// tm4c hardware abstraction layer
class HAL_TM4C : public HAL<HAL_TM4C> {
public:
    // new hal
    HAL_TM4C();

    // initialize device
    void init_() const;

    // transfer via spi, tx data will be overwritten with rx data
    void transferSPI_(uint8_t *data, uint8_t count) const;

private:
    // init clock
    void initClock() const;

    // init debug leds
    void initLEDs() const;

    // init spi
    void initSPI() const;

    // reverse bits (msb <-> lsb)
    uint8_t rbit(uint8_t data) const;
};

#endif // HAL_TM4C_H
