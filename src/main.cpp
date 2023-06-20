#include <memory>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "dvf3060.h"

#define LED_RED GPIO_PIN_1
#define LED_BLUE GPIO_PIN_2
#define LED_GREEN GPIO_PIN_3

extern "C" {
    void setup();
    void loop();
}

uint8_t rbit(uint8_t data) {
    uint32_t temp = data;
    asm("rbit %0, %1" : "=r" (temp) : "r" (temp)); // reverse order of 32 bits
    return (uint8_t)(temp >> 24); // return reversed 8 bits
}

void setup() {
    DVF3060 dvf3060;
    dvf3060.init();

    // display data write
    SSIDataPut(SSI0_BASE, rbit(0x40)); // 0x40
    while (SSIBusy(SSI0_BASE)); // wait for tx done

    // display data
    SSIDataPut(SSI0_BASE, rbit(0xC0)); // 0xC0
    for (int i = 0; i < 48; i++) {
        SSIDataPut(SSI0_BASE, rbit(0xFF)); // 0xFF
    }
    while (SSIBusy(SSI0_BASE)); // wait for tx done

    // display on
    SSIDataPut(SSI0_BASE, rbit(0x8B)); // 0x8B
    while (SSIBusy(SSI0_BASE)); // wait for tx done

    // led data write
    SSIDataPut(SSI0_BASE, rbit(0x41)); // 0x41
    SSIDataPut(SSI0_BASE, rbit(0x00));
    while (SSIBusy(SSI0_BASE)); // wait for tx done
}

void loop() {
    HAL hal;

    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, LED_BLUE);
    hal.delay(1000);

    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, LED_GREEN);
    hal.delay(1000);
}
