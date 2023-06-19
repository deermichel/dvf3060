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
    VFD vfd;

    // clock: 40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    // debug led
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN);
    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, LED_RED);

    // init ssi
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2);
    SSIClockSourceSet(SSI0_BASE, SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_MASTER, 100000, 8);
    SSIEnable(SSI0_BASE);

    // drain rx fifo
    uint32_t data;
    while (SSIDataGetNonBlocking(SSI0_BASE, &data));

    // 200ms delay
    SysCtlDelay(SysCtlClockGet() / (3 * 5));

    // display mode set
    SSIDataPut(SSI0_BASE, rbit(0x0B)); // 0x0B
    while (SSIBusy(SSI0_BASE)); // wait for tx done

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
    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, LED_BLUE);
    SysCtlDelay(SysCtlClockGet() / 3);

    SSIDataPut(SSI0_BASE, rbit(0x41)); // 0x41
    SSIDataPut(SSI0_BASE, rbit(0x00));
    while (SSIBusy(SSI0_BASE)); // wait for tx done

    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, LED_GREEN);
    SysCtlDelay(SysCtlClockGet() / 3);

    SSIDataPut(SSI0_BASE, rbit(0x41)); // 0x41
    SSIDataPut(SSI0_BASE, rbit(0xFF));
    while (SSIBusy(SSI0_BASE)); // wait for tx done

}
