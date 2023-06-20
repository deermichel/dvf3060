#include "hal_tm4c.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

// debug leds
#define LED_RED GPIO_PIN_1
#define LED_BLUE GPIO_PIN_2
#define LED_GREEN GPIO_PIN_3
#define DEBUG_LEDS (LED_RED | LED_BLUE | LED_GREEN)

// new hal
HAL_TM4C::HAL_TM4C() {}

// initialize device
void HAL_TM4C::init_() const {
    initClock();
    initLEDs();
    initSPI();
}

// transfer via spi, tx data will be overwritten with rx data
void HAL_TM4C::transferSPI_(uint8_t *data, uint8_t count) const {}

// --- private ---

// init clock
void HAL_TM4C::initClock() const {
    // 200mhz / 5 = 40mhz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
}

// init debug leds
void HAL_TM4C::initLEDs() const {
    // onboard led on port f
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, DEBUG_LEDS);
    GPIOPinWrite(GPIO_PORTF_BASE, DEBUG_LEDS, LED_RED);
}

// init spi
void HAL_TM4C::initSPI() const {
    // ssi0 on port a
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    // pa2 = sck, pa3 = cs, pa4 = miso, pa5 = mosi
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
    
    // cpol = 1, cpha = 1, 100khz, 8 bit
    SSIClockSourceSet(SSI0_BASE, SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_MASTER, 100000, 8);
    SSIEnable(SSI0_BASE);

    // drain rx fifo
    uint32_t data;
    while (SSIDataGetNonBlocking(SSI0_BASE, &data));
}

// reverse bits (msb <-> lsb)
uint8_t HAL_TM4C::rbit(uint8_t data) const {
    uint32_t temp = data;
    asm("rbit %0, %1" : "=r" (temp) : "r" (temp)); // reverse order of 32 bits
    return (uint8_t)(temp >> 24); // return reversed 8 bits
}
