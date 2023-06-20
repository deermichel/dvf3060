#ifndef CTRL_H
#define CTRL_H

#include <stdint.h>

template <typename Impl>
class Controller {
public:
    // initialize device
    void init() const {
        static_cast<const Impl*>(this)->init_();
    }

    // write data to display memory (block write)
    void writeDisplayData(const uint8_t *data, uint8_t count, uint8_t offset) const {
        static_cast<const Impl*>(this)->writeDisplayData_(data, count, offset);
    }
};

#endif // CTRL_H
