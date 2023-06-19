#include "tm4c.h"

// new hal
HAL::HAL() {}

// init spi
void HAL::initSPI() const {}

// transfer via spi, tx data will be overwritten with rx data
void HAL::transferSPI(uint8_t *data, uint8_t count) const {}
