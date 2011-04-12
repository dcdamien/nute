/*
 * File:   main.c
 * Author: Kreyl
 *
 * Created on April 11, 2011, 7:29 PM
 */

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "main.h"
#include "common.h"
#include "delay_util.h"

// =================================== Types ===================================
struct {
    uint8_t PWM, PWMDesired;
    uint16_t Timer;
    bool IsOn;
} ELED;
struct {
    uint16_t Timer;
    bool IsPressed;
} EKey;

// =============================== Implementation ==============================
int main(void) {
    GeneralInit();

    while(1) {
        wdt_reset();
        PWM_Task();
        Key_Task();
        Sleep_Task();
    }
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);    // Enable WatchDog at 2 s
    ACSR |= (1<<ACD);       // Shutdown comparator
    DelayInit();
    // Init PWM
    DDRB  |= (1<<PWM_P);
    PORTB &= ~(1<<PWM_P);
    ELED.PWMDesired = 0;
    ELED.PWM = 0;
    DelayReset(&ELED.Timer);
    ELED.IsOn = false;
    // Key
    DDRB  &= ~(1<<KEY_P);   // Make it input
    PORTB |=  (1<<KEY_P);   // Switch on pull-up
    DelayReset(&EKey.Timer);
    EKey.IsPressed = false;
    sei();
}

// ================================== Tasks ====================================
FORCE_INLINE void Key_Task(void) {
    if (!DelayElapsed(&EKey.Timer, KEY_POLL_TIMEOUT)) return;
    if ((!EKey.IsPressed) && KEY_IS_DOWN()) {
        EKey.IsPressed = true;
        EVENT_KeyPressed();
    }
    else if (EKey.IsPressed && (!KEY_IS_DOWN())) {
        EKey.IsPressed = false;
    }
}
FORCE_INLINE void PWM_Task(void) {
    if (ELED.PWM == ELED.PWMDesired) return;    // Nothing to do if ok
    if (ELED.PWMDesired < ELED.PWM) {           // Lower PWM
        if (MayChangePWM()) {
            ELED.PWM--;
            PWM_SET(ELED.PWM);
        }
        // Workaround hardware PWM bug: LED does not switches off totally
        if (ELED.PWM == 0) PWMDisable();
    }
    else {
        if (ELED.PWM == 0) PWMEnable();
        if (MayChangePWM()) {
            ELED.PWM++;
            PWM_SET(ELED.PWM);
        } // if may change
    } // Fade or brighten
}
FORCE_INLINE void Sleep_Task(void) {
    if (ELED.IsOn) return;  // Get out if on
    // Check if fade completed and key depressed
    if ((ELED.PWM == 0) && (!EKey.IsPressed)) { // Time to sleep!
        // No need to stop timer as in power-down mode it is stopped
        MCUCR = (1<<SE)|(1<<SM1)|(0<<SM0);  // Enable sleep in power-down mode
        GIMSK = (1<<PCIE);                  // }
        PCMSK = (1<<KEY_PCINT);             // } Enable Key IRQ
        wdt_disable();                      // Disable Watchdog
        sleep_cpu();                        // Fall asleep
        // Awake occured
        wdt_enable(WDTO_2S);                // Enable WatchDog at 2 s
        GIMSK = (0<<PCIE);                  // Disable Key IRQ
        MCUCR = (0<<SE)|(0<<SM1)|(0<<SM0);  // Disable sleep

        EKey.IsPressed = true;
        EVENT_KeyPressed();
    } // if PWM==0
}

// ================================= Events ====================================
FORCE_INLINE void EVENT_KeyPressed(void) {
    if (ELED.IsOn) {
        ELED.IsOn = false;
        ELED.PWMDesired = 0;
    }
    else {
        ELED.IsOn = true;
        // Left existing PWM if key pressed during fade-out
        if (ELED.PWM > PWMStartValue) ELED.PWMDesired = ELED.PWM;
        else ELED.PWMDesired = PWMStartValue;
    }
}

// =================================== PWM =====================================
FORCE_INLINE void PWMEnable(void){
    // Setup timer1
    TCNT1 = 0x00;
    OCR1C = 0xFF;
    OCR1A = 0x00;
    OCR1B = 0x00;
    // Disable Timer1 interrupts
    TIMSK &= ~((1<<OCIE1A)|(1<<OCIE1B)|(1<<TOIE1));
    // Init clock
/*
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        PLLCSR |= (1<<LSM);     // Set low-speed mode (32MHz), need for low-voltage operation
        PLLCSR |= (1<<PLLE);    // Enable PLL
        _delay_us(100);         // Wait for PLL to stabilize
        loop_until_bit_is_set (PLLCSR, PLOCK); // wait until PLOCK become 1
        PLLCSR |= (1<<PCKE);    // Enable PCK
    }
*/
    // Single Channel VCC-based PWM
    TCCR1 = (1<<PWM1A)|(1<<COM1A1)|(0<<COM1A0)|(0<<CS13)|(0<<CS12)|(0<<CS11)|(1<<CS10);
}
FORCE_INLINE void PWMDisable(void){
    TCCR1  = 0x00; // Stop Timer1
    PLLCSR = 0x00; // Stop clock
}
bool MayChangePWM(void) {
    if (ELED.PWM <= PWMStepOver1)                                   return DelayElapsed(&ELED.Timer, PWMDelayLong);        // Low speed
    else if (ELED.PWM > PWMStepOver1 && ELED.PWM <= PWMStepOver2)   return DelayElapsed(&ELED.Timer, PWMDelayMid);         // Mid-speed
    else if (ELED.PWM > PWMStepOver2)                               return DelayElapsed(&ELED.Timer, PWMDelayFast);        // High-speed
    return false;
}

// ******************** Interrupts **************************
// Key interrupt
EMPTY_INTERRUPT (PCINT0_vect);

