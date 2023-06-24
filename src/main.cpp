#include <stdbool.h>
#include <stdint.h>
#include "dvf3060.h"

// device instance, timer vars
DVF3060 dvf3060;
int8_t hours = 0;
int8_t minutes = 0;
int8_t seconds = 0;
bool running = true;

// process front panel keys
void processKeys() {
    uint8_t keyState = dvf3060.getKeyState();
    if (keyState & DVF3060_KEY_PLAY) {
        running = true; // resume
    } else if (keyState & DVF3060_KEY_STOP) {
        running = false; // pause
    } else if (keyState & DVF3060_KEY_EJECT) {
        hours = minutes = seconds = 0; // reset
    } else if (keyState & DVF3060_KEY_NEXT) {
        hours++; // increment hours
    } else if (keyState & DVF3060_KEY_PREV) {
        hours--; // decrement hours
    } else if (keyState & DVF3060_KEY_FF) {
        minutes++; // increment minutes
    } else if (keyState & DVF3060_KEY_REW) {
        minutes--; // decrement minutes
    }
}

// update timer vars
void updateTimer() {
    if (running) seconds++;
    while (seconds < 0) { seconds += 60; minutes--; }
    while (seconds >= 60) { seconds -= 60; minutes++; }
    while (minutes < 0) { minutes += 60; hours--; }
    while (minutes >= 60) { minutes -= 60; hours++; }
    while (hours < 0) hours += 24;
    while (hours >= 24) hours -= 24;
}

// update timer display
void updateDisplay() {
    // icons
    if (running) {
        dvf3060.setIcon(DVF3060_ICON::PLAY);
        dvf3060.clearIcon(DVF3060_ICON::PAUSE);
    } else {
        dvf3060.setIcon(DVF3060_ICON::PAUSE);
        dvf3060.clearIcon(DVF3060_ICON::PLAY);
    }
    dvf3060.setIcon(DVF3060_ICON::HOUR);
    dvf3060.setIcon(DVF3060_ICON::COLON_HOUR);
    dvf3060.setIcon(DVF3060_ICON::MIN);
    dvf3060.setIcon(DVF3060_ICON::COLON_MIN);
    dvf3060.setIcon(DVF3060_ICON::SEC);

    // time
    dvf3060.setChar('0' + hours / 10, 4);
    dvf3060.setChar('0' + hours % 10, 5);
    dvf3060.setChar('0' + minutes / 10, 6);
    dvf3060.setChar('0' + minutes % 10, 7);
    dvf3060.setChar('0' + seconds / 10, 8);
    dvf3060.setChar('0' + seconds % 10, 9);
}

// one time setup
extern "C" void setup() {
    dvf3060.init();
}

// main loop
extern "C" void loop() {
    processKeys();
    updateTimer();
    updateDisplay();
    HAL().delay(200); // just for testing!
}
