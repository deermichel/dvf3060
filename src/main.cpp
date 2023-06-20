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

// c compatibility
extern "C" {
    void setup();
    void loop();
}

void setup() {
    DVF3060 dvf3060;
    dvf3060.init();
}

void loop() {
    HAL hal;

    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, LED_BLUE);
    hal.delay(1000);

    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, LED_GREEN);
    hal.delay(1000);
}
