#include "ctrl_pt6311.h"

// new controller using hal
template <typename HAL_Impl>
Controller_PT6311<HAL_Impl>::Controller_PT6311(HAL_Impl &&hal)
    : mHAL(hal) {}

// initialize device
template <typename HAL_Impl>
void Controller_PT6311<HAL_Impl>::init_() const {
    // init hal
    // mHAL.init();

    // 200ms delay
    // TODO
}

// set display mode
template <typename HAL_Impl>
void Controller_PT6311<HAL_Impl>::setDisplayMode(uint8_t mode) const {}

// set display control
template <typename HAL_Impl>
void Controller_PT6311<HAL_Impl>::setDisplayControl(bool enabled, uint8_t brightness) const {}

// set test mode
template <typename HAL_Impl>
void Controller_PT6311<HAL_Impl>::setTestMode(bool enabled) const {}

// write data to display memory (block write)
template <typename HAL_Impl>
void Controller_PT6311<HAL_Impl>::writeDisplayData_(const uint8_t *data, uint8_t count, uint8_t offset) const {}

// write data to display memory (specific address)
template <typename HAL_Impl>
void Controller_PT6311<HAL_Impl>::writeDisplayData(uint8_t data, uint8_t address) const {}

// write data to led port
template <typename HAL_Impl>
void Controller_PT6311<HAL_Impl>::writeLedData(uint8_t data) const {}

// read key data
template <typename HAL_Impl>
void Controller_PT6311<HAL_Impl>::readKeyData(uint8_t *data, uint8_t count) const {}

// read switch data
template <typename HAL_Impl>
void Controller_PT6311<HAL_Impl>::readSwitchData(uint8_t *data) const {}
