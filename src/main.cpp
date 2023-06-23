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

HAL hal;
DVF3060 dvf3060;

void setup() {
    dvf3060.init();
}

const char *str = "deermichelHELLO WORLD, i am a teapot 418";
int i = 0;

void print_string(const char *str) {
    dvf3060.clearDisplay();
    for (uint8_t i = 0; i < DVF3060_MAX_CHARS && str[i]; i++) {
        dvf3060.setChar(str[i], i);
    }
}

void loop() {
    print_string(&str[i]);
    // i++;
    if (!str[i]) i = 0;
    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED | LED_BLUE | LED_GREEN, i % 2 == 0 ? LED_BLUE : LED_GREEN);
    hal.delay(200);
}
