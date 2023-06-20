#include "pt6311.h"

// initialize device
void PT6311::init() const {
    // init hal
    mHAL.init();

    // 200ms delay
    // TODO
}

// set display mode
void PT6311::setDisplayMode(uint8_t mode) const {}

// set display control
void PT6311::setDisplayControl(bool enabled, uint8_t brightness) const {}

// set test mode
void PT6311::setTestMode(bool enabled) const {}

// write data to display memory (block write)
void PT6311::writeDisplayData(const uint8_t *data, uint8_t count, uint8_t offset) const {}

// write data to display memory (specific address)
void PT6311::writeDisplayData(uint8_t data, uint8_t address) const {}

// write data to led port
void PT6311::writeLedData(uint8_t data) const {}

// read key data
void PT6311::readKeyData(uint8_t *data, uint8_t count) const {}

// read switch data
void PT6311::readSwitchData(uint8_t *data) const {}
