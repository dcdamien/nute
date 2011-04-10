/* 
 * File:   calma3c.c
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */
#include <avr/io.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include "portal.h"
#include "time_utils.h"
#include "common.h"

// ============================= Types =========================================
struct {
    uint16_t Timer;
    uint8_t DesiredBrightness, CurrentBrightness;
} ELight;

struct {
    bool IsOn;
    uint16_t Timer;
} SW;


// ============================== General ======================================
int main(void) {
    GeneralInit();

    sei(); 
    while (1) {
        wdt_reset();    // Reset watchdog
        Light_Task();
        Switch_Task();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    // Setup timer
    TimerInit();    // Time counter

    // Light
    LED_DDR  |=  (1<<LED_P);
    LED_PORT &= ~(1<<LED_P);
    TCCR0A = (1<<WGM01)|(1<<WGM00);
    TCCR0B = (0<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00);  // 1 MHz/8 = 125 kHz of timer infut freq. 125 kHz/255 = 490 Hz of PWM freq.
    TimerResetDelay(&ELight.Timer);

    ELight.CurrentBrightness = 0;
    ELight.DesiredBrightness = 250;

    // Switch
    SW_DDR  &= ~(1<<SW_P);
    SW_PORT |=  (1<<SW_P);
    SW.IsOn = false;
}

// ============================== Tasks ========================================
void Light_Task(void) {
    if (!TimerDelayElapsed(&ELight.Timer, LED_STEP_DELAY)) return;

    if (ELight.CurrentBrightness != ELight.DesiredBrightness) {
        if (ELight.DesiredBrightness < ELight.CurrentBrightness) {
            ELight.CurrentBrightness--;
            if (ELight.CurrentBrightness == 0) LED_DISABLE();
        }
        else {
            if (ELight.CurrentBrightness == 0) LED_ENABLE();
            ELight.CurrentBrightness++;
        }
        OCR0A = ELight.CurrentBrightness;
    }
}

void Switch_Task(void) {
    if (!TimerDelayElapsed(&SW.Timer, SW_DELAY)) return;

    if (SW.IsOn && !SW_IS_ON()) {
        SW.IsOn = false;
        EVENT_SwitchOff();
    }
    else if (!SW.IsOn && SW_IS_ON()) {
        SW.IsOn = true;
        EVENT_SwitchOn();
    }
}

// ============================== Events =======================================
void EVENT_SwitchOn(void) {
    ELight.DesiredBrightness = 250;
}
void EVENT_SwitchOff(void) {
    ELight.DesiredBrightness = 0;
}
