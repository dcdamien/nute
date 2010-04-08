// ************************** LEDs & keys handling *******************************
#include <stdbool.h>
#include <avr/io.h>
#include "ledskeys.h"

void LEDKeyInit (void) {
    // Ports init
    LED_DDR  |=   (1<<LED_RED)|(1<<LED_GREEN); // LEDs are outputs
    //BTN_DDR  &= ~((1<<BTN1)|(1<<BTN2));
    //BTN_PORT |=   (1<<BTN1)|(1<<BTN2);
}