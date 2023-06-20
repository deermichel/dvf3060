#ifndef DISP_H
#define DISP_H

template <typename Impl>
class Display {
public:
    // initialize device
    void init() const {
        static_cast<const Impl*>(this)->init_();
    }
};

#endif // DISP_H
