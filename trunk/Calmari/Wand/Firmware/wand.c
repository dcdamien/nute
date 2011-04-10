/* 
 * File:   wand.c
 * Author: Laurelindo
 *
 * Created on 25 Ноябрь 2009 г., 19:48
 */

#include <wand.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include "time_utils.h"

enum LightState_t {LightUp, LightDown, SetFullOn, SetFullOff, IsFullOn, IsFullOff};
struct {
    enum LightState_t State;
    uint8_t Brightness;
    uint16_t Timer;
    uint8_t DelayValue;
} ELight;

struct {
    uint16_t Timer, DurationTimer;
    bool IsDown;
    bool IsMeasuringDelay;
} EKey;

uint16_t SleepTimer;

int main(void) {
    wdt_enable (WDTO_2S);   // Enable watchdog @ 2s
    // shutdown comparator
    ACSR = (1<<ACD);
    // setup io
    DDRB = (1<<PWM_P)|(0<<KEY_P);
    PORTB = (1<<KEY_P); // Enable pullup
    LED_OFF;            // Shutdown light for the first time
    PCMSK = (1<<KEY_P); // Enable Key PinChange IRQ

    // Setup timer 
    TimerInit();    // Time counter
    // Setup PWM
    OCR1A = 0;
    OCR1C = 255;
    TCCR1 = (1<<PWM1A)|(1<<COM1A1)|(0<<COM1A0)|(0<<CS13)|(1<<CS12)|(0<<CS11)|(1<<CS10);

    // Init light
    ELight.Brightness = 0;
    ELight.State = SetFullOff;
    ELight.DelayValue = LIGHT_LOW_T;
    TimerResetDelay (&ELight.Timer);
    
    // Init key
    EKey.IsDown = false;
    EKey.IsMeasuringDelay = false;
    TimerResetDelay (&EKey.Timer);

    // Init sleep
    TimerResetDelay (&SleepTimer);
   
    sei();

    while (1) {
        Key_Task ();
        Light_Task ();
        Sleep_Task ();
    } // while
}

void Light_Task (void) {
    switch (ELight.State) {
        case LightUp:   // ===== Rise brightness =====
            if (TimerDelayElapsed (&ELight.Timer, ELight.DelayValue)) {
                ELight.Brightness++;
                SET_PWM(ELight.Brightness);     // Set needed brightness
                LightSetDelay();                // Change delay in accordance to brightness value
                if (ELight.Brightness == 255) { // Check if completed
                    ELight.State = IsFullOn;    // After achievment of max brightness, set it fully on
                    LED_ON;                     // to prevent unknown condition in sleep mode
                }
            } // if delay
            break;

        case LightDown: // ===== Fade it down =====
            if (TimerDelayElapsed (&ELight.Timer, ELight.DelayValue)) {
                ELight.Brightness--;
                SET_PWM(ELight.Brightness);     // Set needed brightness
                LightSetDelay();                // Change delay in accordance to brightness value
                if (ELight.Brightness == 0) {   // Check if completed
                    ELight.State = IsFullOff;   // After achievment of min brightness, set it fully off
                    LED_OFF;                    // to prevent unknown condition in sleep mode
                }
            }
            break;

        case SetFullOn:
            SET_PWM(255);
            ELight.Brightness = 255;
            ELight.State = IsFullOn;
            LED_ON;
            break;

        case SetFullOff:
            SET_PWM(0);
            ELight.Brightness = 0;
            ELight.State = IsFullOff;
            LED_OFF;
            break;

        default:
            break;
    } // switch
}
void LightSetDelay (void) {
    if (ELight.Brightness < PWM_STEP_LOW) ELight.DelayValue = LIGHT_LOW_T;
    else if (ELight.Brightness >= PWM_STEP_MID) ELight.DelayValue = LIGHT_HIGH_T;
    else ELight.DelayValue = LIGHT_MID_T;
}

void Key_Task (void) {
    // ====== Check button when needed ======
    if (TimerDelayElapsed (&EKey.Timer, KEY_POLL_T)) {  
        if (!EKey.IsDown && KEY_IS_DOWN) {     // Keypress occured
            EKey.IsDown = true;
            // start keypress duration measuring
            EKey.IsMeasuringDelay = true;
            TimerResetDelay (&EKey.DurationTimer);
            // Run corresponding event
            //KeyPress_Event ();
        } // if keypress occured

        else if (EKey.IsDown && !KEY_IS_DOWN) { // Key depress occured
            EKey.IsDown = false;
            // Stop keypress duration measuring
            if (EKey.IsMeasuringDelay) {    // if still measuring
                EKey.IsMeasuringDelay = false;
                // if still measuring when depressing, then there is not a long keypress
                KeyQuickPress();
            }
            // Run corresponding event
            //KeyDepress_Event ();
        } // if depress occured
    } // if timeout

    // ====== Check press duration ======
    if (EKey.IsMeasuringDelay) {
        // Check if time has passed
        if (TimerDelayElapsed (&EKey.DurationTimer, TRESHOLD_DURATION)) {
            EKey.IsMeasuringDelay = false;  // no need to measure further as timeout has passed yet
            // Run corresponding event
            KeyLongPress();
        } // if delay
    } // if measuring
}

/*
void KeyPress_Event (void) {
}
void KeyDepress_Event (void) {
}
*/

void KeyQuickPress (void) {
    // Switch light quickly
    if      (ELight.State == LightUp   || ELight.State == IsFullOff) ELight.State = SetFullOn;
    else if (ELight.State == LightDown || ELight.State == IsFullOn)  ELight.State = SetFullOff;
}
void KeyLongPress (void) {
    // Switch light slowly
    if      (ELight.State == LightDown || ELight.State == IsFullOff) ELight.State = LightUp;
    else if (ELight.State == LightUp   || ELight.State == IsFullOn)  ELight.State = LightDown;
}

void Sleep_Task (void) {
    // Check timeout
    if (! TimerDelayElapsed (&SleepTimer, SLEEP_T)) return;
    wdt_reset();  // Reset watcdog timer
    
    if (EKey.IsDown || KEY_IS_DOWN) return;    // Don't sleep when key is pressed
    if (!(ELight.State == IsFullOff || ELight.State == IsFullOn)) return;   // May sleep at FullOff and FullOn states

    MCUCR = (1<<SE)|(1<<SM1)|(0<<SM0);  // Setup deep sleep mode
    GIFR  = (1<<PCIF);                  // Clear Key IRQ flag
    GIMSK = (1<<PCIE);                  // Enable Key IRQ
    wdt_disable ();                     // Disable watchdog
    asm volatile (
        "sei"   "\n\t"
        "sleep" "\n\t"
    ::);
    wdt_enable (WDTO_2S);   // Enable watchdog @ 2s
    MCUCR = 0;              // Disable sleep
    GIMSK = (0<<PCIE);      // Disable Key IRQ
}

// ******************** Interrupts **************************
EMPTY_INTERRUPT (PCINT0_vect);