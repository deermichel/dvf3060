#include "pt6311.h"

// new controller using hal
Controller::Controller(HAL &&hal)
    : mHAL(hal) {}

// initialize device
void Controller::init() const {
    // init hal
    mHAL.init();

    // 200ms delay
    // TODO
}

// set display mode
void Controller::setDisplayMode(uint8_t mode) const {}

// set display control
void Controller::setDisplayControl(bool enabled, uint8_t brightness) const {}

// set test mode
void Controller::setTestMode(bool enabled) const {}

// write data to display memory (block write)
void Controller::writeDisplayData(const uint8_t *data, uint8_t count, uint8_t offset) const {}

// write data to display memory (specific address)
void Controller::writeDisplayData(uint8_t data, uint8_t address) const {}

// write data to led port
void Controller::writeLedData(uint8_t data) const {}

// read key data
void Controller::readKeyData(uint8_t *data, uint8_t count) const {}

// read switch data
void Controller::readSwitchData(uint8_t *data) const {}
