#ifndef TM4C_H
#define TM4C_H

#include <stdint.h>

// tm4c hardware abstraction layer
class TM4C {
public:
    // initialize device
    void init() const;

    // transfer via spi, tx data will be overwritten with rx data
    void transferSPI(uint8_t *data, uint8_t count) const;

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

#endif // TM4C_H
