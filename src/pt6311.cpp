#include "pt6311.h"

// display ram size in bytes
#define RAM_SIZE 48

// key data size in bytes
#define KEY_DATA_SIZE 6

// initialize device
void PT6311::init() const {
    // init hal
    mHAL.init();

    // 200ms delay
    mHAL.delay(200);
}

// set display mode
void PT6311::setDisplayMode(uint8_t mode) const {
    uint8_t command = 0x00 | (mode & 0x0F);
    mHAL.transferSPI(&command, 1);
}

// set display control
void PT6311::setDisplayControl(bool enabled, uint8_t brightness) const {
    uint8_t command = 0x80 | (enabled ? 0x08 : 0x00) | (brightness & 0x07);
    mHAL.transferSPI(&command, 1);
}

// set test mode
void PT6311::setTestMode(bool enabled) const {
    uint8_t command = 0x40 | (enabled ? 0x08 : 0x00);
    mHAL.transferSPI(&command, 1);
}

// write data to display memory (block write)
void PT6311::writeDisplayData(const uint8_t *data, uint8_t count, uint8_t offset) const {
    // repack data
    uint8_t packet[1 + RAM_SIZE]; // command + max 48 data bytes
    if (count > RAM_SIZE) count = RAM_SIZE; // limit to ram size
    for (uint8_t i = 0; i < count; i++) {
        packet[i + 1] = data[i];
    }

    // set data write mode (increment address)
    uint8_t command = 0x40;
    mHAL.transferSPI(&command, 1);

    // set address and data
    packet[0] = 0xC0 | (offset & 0x3F); // command
    mHAL.transferSPI(packet, 1 + count);
}

// write data to display memory (specific address)
void PT6311::writeDisplayData(uint8_t data, uint8_t address) const {
    // set data write mode (fixed address)
    uint8_t command = 0x44;
    mHAL.transferSPI(&command, 1);

    // set address and data
    command = 0xC0 | (address & 0x3F);
    uint8_t packet[2] = { command, data };
    mHAL.transferSPI(packet, 2);
}

// write data to led port
void PT6311::writeLedData(uint8_t data) const {}

// read key data
void PT6311::readKeyData(uint8_t *data, uint8_t count) const {
    uint8_t packet[1 + KEY_DATA_SIZE]; // command + max 6 data bytes
    if (count > KEY_DATA_SIZE) count = KEY_DATA_SIZE; // limit to key data size
    
    // set key read mode and read data
    packet[0] = 0x42; // command
    mHAL.transferSPI(packet, 1 + count);

    // repack data
    for (uint8_t i = 0; i < count; i++) {
        data[i] = packet[i + 1];
    }
}

// read switch data
void PT6311::readSwitchData(uint8_t *data) const {}
