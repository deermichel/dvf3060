#ifndef PT6311_H
#define PT6311_H

#include <stdint.h>
#include "tm4c.h"

// display modes
#define PT6311_MODE_G8_S20 0b0000
#define PT6311_MODE_G9_S19 0b1000
#define PT6311_MODE_G10_S18 0b1001
#define PT6311_MODE_G11_S17 0b1010
#define PT6311_MODE_G12_S16 0b1011
#define PT6311_MODE_G13_S15 0b1100
#define PT6311_MODE_G14_S14 0b1101
#define PT6311_MODE_G15_S13 0b1110
#define PT6311_MODE_G16_S12 0b1111

// led ports
#define PT6311_LED1 0x01
#define PT6311_LED2 0x02
#define PT6311_LED3 0x04
#define PT6311_LED4 0x08
#define PT6311_LED5 0x10

// switch ports
#define PT6311_SW1 0x01
#define PT6311_SW2 0x02
#define PT6311_SW3 0x04
#define PT6311_SW4 0x08

// pt6311 display controller
class Controller {
public:
    // new controller using hal
    Controller(HAL &&hal = HAL());

    // set display mode
    void setDisplayMode(uint8_t mode) const;

    // set display control
    void setDisplayControl(bool enabled, uint8_t brightness) const;

    // set test mode
    void setTestMode(bool enabled) const;

    // write data to display memory (block write)
    void writeDisplayData(const uint8_t *data, uint8_t count, uint8_t offset) const;

    // write data to display memory (specific address)
    void writeDisplayData(uint8_t data, uint8_t address) const;

    // write data to led port
    void writeLedData(uint8_t data) const;

    // read key data
    void readKeyData(uint8_t *data, uint8_t count) const;

    // read switch data
    void readSwitchData(uint8_t *data) const;

private:
    // hal instance
    HAL mHal;
};

#endif // PT6311_H
