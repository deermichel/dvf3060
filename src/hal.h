#ifndef HAL_H
#define HAL_H

#include <stdint.h>

template <typename Impl>
class HAL {
public:
    // initialize device
    void init() const {
        static_cast<const Impl*>(this)->init_();
    }

    // transfer via spi, tx data will be overwritten with rx data
    void transferSPI(uint8_t *data, uint8_t count) const {
        static_cast<const Impl*>(this)->transferSPI_(data, count);
    }
};

#endif // HAL_H
