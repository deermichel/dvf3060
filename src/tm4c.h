#ifndef TM4C_H
#define TM4C_H

#include <stdint.h>

// tm4c hardware abstraction layer
class HAL {
public:
    // new hal
    HAL();

    // init spi
    void initSPI() const;

    // transfer via spi, tx data will be overwritten with rx data
    void transferSPI(uint8_t *data, uint8_t count) const;
};

#endif // TM4C_H
