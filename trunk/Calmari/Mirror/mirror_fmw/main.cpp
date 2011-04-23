/*
 * File:   main.cpp
 * Author: Kreyl
 *
 * Created on April 23, 2011, 8:17 PM
 */

#include <avr/io.h>
#include <inttypes.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "main.h"
#include "common.h"
#include "delay_util.h"
#include "color_table.h"

#include <util/delay.h>
// ============================= Types =========================================
struct Sens_t {
    bool UpIsOn, DownIsOn, HandleIsOn;
    uint16_t Timer, HoldTimer;
    uint16_t PollTime;
} ESens;

struct Color_t {
    uint8_t Red, Green, Blue;
};
struct Light_t {
    uint16_t Timer;
    struct Color_t DesiredColor, CurrentColor, SavedColor;
    uint8_t Indx;
} ELight;

bool MustSleep; // toggles in Handle Touch events

// ============================== General ======================================
int main(void) {
    GeneralInit();

    while (1) {
        wdt_reset();    // Reset watchdog
        SENS_Task ();
        Light_Task ();
        Sleep_Task ();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    // Shutdown all unneeded
    PRR = (1<<PRTWI)|(1<<PRSPI)|(1<<PRADC);

    MustSleep = true;
    DelayInit();

    // Light
    LED_DDR  |= (1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P);
    LED_PORT &= ~((1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P));

    TCCR0A = (1<<WGM01)|(1<<WGM00);
    TCCR0B = (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);
    TCCR2A = (1<<WGM21)|(1<<WGM20);
    TCCR2B = (0<<WGM22)|(0<<CS22)|(0<<CS21)|(1<<CS20);
    DelayReset(&ELight.Timer);
    ELight.Indx = 0;
    SetTableColor();
    ELight.SavedColor = ELight.DesiredColor;
    SetDesiredColor(0, 0, 0);   // Initial fade

    // Sensors
    SENS_DDR  &= ~((1<<SENS_DOWN)|(1<<SENS_UP)|(1<<SENS_HANDLE));
    SENS_PORT &= ~(1<<SENS_HANDLE);             // No pull-up
    SENS_PORT |=  (1<<SENS_DOWN)|(1<<SENS_UP);  // Pull-up on keys
    ESens.DownIsOn   = false;
    ESens.UpIsOn     = false;
    ESens.HandleIsOn = false;
    ESens.PollTime   = SENS_POLL_TIME;
    DelayReset (&ESens.Timer);

    sei();
}

FORCE_INLINE void SetDesiredColor (uint8_t ARed, uint8_t AGreen, uint8_t ABlue) {
    ELight.DesiredColor.Red   = ARed;
    ELight.DesiredColor.Green = AGreen;
    ELight.DesiredColor.Blue  = ABlue;
}
void SetTableColor(void) {
    ELight.DesiredColor.Red   = pgm_read_byte(&ColorTable[ELight.Indx][0]);
    ELight.DesiredColor.Green = pgm_read_byte(&ColorTable[ELight.Indx][1]);
    ELight.DesiredColor.Blue  = pgm_read_byte(&ColorTable[ELight.Indx][2]);
}


// ============================== Tasks ========================================
void SENS_Task (void) {
    if (!DelayElapsed (&ESens.Timer, ESens.PollTime)) return;
    // Reset to default wait time
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ESens.PollTime = SENS_POLL_TIME;
    }

    // ******** Up sensor *******
    if (!ESens.UpIsOn && SENS_UP_IS_ON()) {     // Touch occured
        ESens.UpIsOn = true;
        DelayReset(&ESens.HoldTimer);  // Reset hold timer
    }
    else if (ESens.UpIsOn && !SENS_UP_IS_ON()) {// Detouch occured
        ESens.UpIsOn   = false;
    }

    // ******* Down sensor *******
    if (!ESens.DownIsOn && SENS_DOWN_IS_ON()) { // Touch occured
        ESens.DownIsOn = true;
        DelayReset(&ESens.HoldTimer);  // Reset hold timer
    }
    else if (ESens.DownIsOn && !SENS_DOWN_IS_ON()) {    // Detouch occured
        ESens.DownIsOn = false;
    }

    // ******* Handle sensor *******
    if (!ESens.HandleIsOn && SENS_HANDLE_IS_ON()) { // Mainly, handle touch event is recalled immediately after sleep.
        ESens.HandleIsOn = true;                    // But it may occur if retouch performed during fade of LED
        EVENT_HandleTouched();
    }
    else if (ESens.HandleIsOn && !SENS_HANDLE_IS_ON()) {
        ESens.HandleIsOn = false;
        EVENT_HandleDetouched();
    }

    // ******* Holding handlers *******
    if (ESens.DownIsOn)
        if (DelayElapsed(&ESens.HoldTimer, SENS_HOLD_TICK_TIMEOUT)) EVENT_DownHoldTick();
    if (ESens.UpIsOn)
        if (DelayElapsed(&ESens.HoldTimer, SENS_HOLD_TICK_TIMEOUT)) EVENT_UpHoldTick();
}

void Light_Task(void) {
    if (!DelayElapsed(&ELight.Timer, LED_STEP_DELAY)) return;
    // Red channel
    if (ELight.CurrentColor.Red != ELight.DesiredColor.Red) {
        if (ELight.DesiredColor.Red < ELight.CurrentColor.Red) {
            ELight.CurrentColor.Red--;
            if (ELight.CurrentColor.Red == 0) LED_RED_DISABLE();
        }
        else {
            if (ELight.CurrentColor.Red == 0) LED_RED_ENABLE();
            ELight.CurrentColor.Red++;
        }
        OCR0A = ELight.CurrentColor.Red;
    }
    // Green channel
    if (ELight.CurrentColor.Green != ELight.DesiredColor.Green) {
        if (ELight.DesiredColor.Green < ELight.CurrentColor.Green) {
            ELight.CurrentColor.Green--;
            if (ELight.CurrentColor.Green == 0) LED_GREEN_DISABLE();
        }
        else {
            if (ELight.CurrentColor.Green == 0) LED_GREEN_ENABLE();
            ELight.CurrentColor.Green++;
        }
        OCR0B = ELight.CurrentColor.Green;
    }
    // Blue channel
    if (ELight.CurrentColor.Blue != ELight.DesiredColor.Blue) {
        if (ELight.DesiredColor.Blue < ELight.CurrentColor.Blue) {
            ELight.CurrentColor.Blue--;
            if (ELight.CurrentColor.Blue == 0) LED_BLUE_DISABLE();
        }
        else {
            if (ELight.CurrentColor.Blue == 0) LED_BLUE_ENABLE();
            ELight.CurrentColor.Blue++;
        }
        OCR2B = ELight.CurrentColor.Blue;
    }
}

void Sleep_Task (void) {
    if (!MustSleep) return;
    // Sleep if Current color is black => LED is faded down yet
    if (
            (ELight.CurrentColor.Red   == 0) &&
            (ELight.CurrentColor.Green == 0) &&
            (ELight.CurrentColor.Blue  == 0)
        ) {
        // Enable IRQ to wake
        cli();
        HANDLE_IRQ_SETUP_MASK();
        HANDLE_IRQ_CLEAR();
        HANDLE_IRQ_ENABLE();
        sei();
        // Enter sleep mode
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        wdt_disable();
        sleep_cpu();    // Sleep now
        // Something happened, wake now
        wdt_enable(WDTO_2S);
        sleep_disable();
        HANDLE_IRQ_DISABLE();
        ESens.HandleIsOn = true;
        // Event hanler will do the rest
        EVENT_HandleTouched();  // Execute it from here to switch on immediately
    }
}

// ============================== Events =======================================
void EVENT_HandleTouched(void) {
    ELight.DesiredColor = ELight.SavedColor;
    MustSleep = false;
}
void EVENT_HandleDetouched(void) {
    ELight.SavedColor = ELight.DesiredColor;
    SetDesiredColor(0, 0, 0);
    MustSleep = true;
}


void EVENT_UpHoldTick(void) {   // Fires every N ms when Up is holded
    if (ELight.Indx == COLOR_COUNT-1) return;
    SetTableColor();
    ELight.Indx++;
}
void EVENT_DownHoldTick(void) { // Fires every N ms when Down is holded
    if (ELight.Indx == 0) return;
    SetTableColor();
    ELight.Indx--;
}

// =========================== Interrupts ======================================
EMPTY_INTERRUPT (PCINT1_vect);