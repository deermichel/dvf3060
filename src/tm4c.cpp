#include "tm4c.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"

// debug leds
#define LED_RED GPIO_PIN_1
#define LED_BLUE GPIO_PIN_2
#define LED_GREEN GPIO_PIN_3
#define DEBUG_LEDS (LED_RED | LED_BLUE | LED_GREEN)

// initialize device
void TM4C::init() const {
    initClock();
    initLEDs();
    initUART();
    initSPI();
}

// delay for given number of milliseconds
void TM4C::delay(uint32_t ms) const {
    SysCtlDelay(ms * (SysCtlClockGet() / 3000));
}

// print string to uart
void TM4C::printUART(const char *str) const {
    while (*str) {
        UARTCharPut(UART0_BASE, *str++);
    }
}

// transfer via spi, tx data will be overwritten with rx data
void TM4C::transferSPI(uint8_t *data, uint8_t count) const {
    // send bytes (msb -> lsb)
    for (uint8_t i = 0; i < count; i++) {
        SSIDataPut(SSI0_BASE, rbit(data[i]));
    }

    // wait for tx done
    while (SSIBusy(SSI0_BASE));

    // receive bytes (lsb -> msb)
    uint32_t temp;
    for (uint8_t i = 0; i < count; i++) {
        SSIDataGetNonBlocking(SSI0_BASE, &temp); // fifo might be smaller than count
        data[i] = rbit((uint8_t)temp);
    }
}

// --- private ---

// init clock
void TM4C::initClock() const {
    // 200mhz / 5 = 40mhz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
}

// init debug leds
void TM4C::initLEDs() const {
    // onboard led on port f
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, DEBUG_LEDS);
    GPIOPinWrite(GPIO_PORTF_BASE, DEBUG_LEDS, LED_RED);
}

// init uart
void TM4C::initUART() const {
    // uart0 on port a
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // pa0 = rx, pa1 = tx
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // 115200 baud, 8 bit, 1 stop bit, no parity
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTEnable(UART0_BASE);
}

// init spi
void TM4C::initSPI() const {
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
    uint32_t temp;
    while (SSIDataGetNonBlocking(SSI0_BASE, &temp));
}

// reverse bits (msb <-> lsb)
uint8_t TM4C::rbit(uint8_t data) const {
    uint32_t temp = data;
    asm("rbit %0, %1" : "=r" (temp) : "r" (temp)); // reverse order of 32 bits
    return (uint8_t)(temp >> 24); // return reversed 8 bits
}
