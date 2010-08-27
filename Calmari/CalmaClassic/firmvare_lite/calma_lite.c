#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include "calma_lite.h"
#include "delay_util.h"
#include "common.h"

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

    sei();

    //PORTB &= ~(1<<PB1);
    while(1) {
        wdt_reset();
        LED_Task();
        Key_Task();
        Sleep_Task();
    }
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);    // Enable WatchDog at 2 s
    ACSR |= (1<<ACD);       // Shutdown comparator
    // Setup IO
    DDRB  = (0<<KeyPin)|(1<<LedPin);
    PORTB = (0<<KeyPin)|(1<<LedPin); // VCC-based LED, GND-pulled key

    DelayInit();

    // Init LED
    ELED.PWMDesired = 0;    // Stay still at power-on
    ELED.PWM = 1;           // To force PWM shutdown
    DelayReset(&ELED.Timer);
    ELED.IsOn = false;

    // Key
    DelayReset(&EKey.Timer);
    EKey.IsPressed = false;
}

// ================================== Tasks ====================================
FORCE_INLINE void Key_Task(void) {
    if (DelayElapsed(&EKey.Timer, KEY_POLL_TIMEOUT)) {
        if ((!EKey.IsPressed) && KEY_IS_DOWN()) {
            EKey.IsPressed = true;
            EVENT_KeyPressed();
        }
        else if (EKey.IsPressed && (!KEY_IS_DOWN())) {
            EKey.IsPressed = false;
        }
    }
}
FORCE_INLINE void LED_Task(void) {
    if (ELED.PWM != ELED.PWMDesired) {
        if (ELED.PWMDesired < ELED.PWM) {   // Lower PWM
            if (MayChangePWM()) {
                ELED.PWM--;
                OCR1A = ELED.PWM;
            }
            // Workaround hardware PWM bug: LED does not switches off totally
            if (ELED.PWM == 0) PWMDisable();
        }
        else {
            if (ELED.PWM == 0) PWMEnable();
            if (MayChangePWM()) {
                ELED.PWM++;
                OCR1A = ELED.PWM;
            } // if may change
        } // Fade or brighten
    } // if not desired
}
FORCE_INLINE void Sleep_Task(void) {
    // Check if is off
    if (!ELED.IsOn) {
        // Check if fade completed and key depressed
        if ((ELED.PWM == 0) && (!EKey.IsPressed)) { // Time to sleep!
            // No need to stop timer as in power-down mode it is stopped
            MCUCR = (1<<SE)|(1<<SM1)|(0<<SM0);  // Enable sleep in power-down mode
            GIMSK = (1<<PCIE);                  // }
            PCMSK = (1<<PCINT2);                // } Enable Key IRQ
            wdt_disable();                      // Disable Watchdog
            sleep_cpu();                        // Fall asleep
            // Awake occured
            wdt_enable(WDTO_2S);                // Enable WatchDog at 2 s
            GIMSK = (0<<PCIE);                  // Disable Key IRQ
            MCUCR = (0<<SE)|(0<<SM1)|(0<<SM0);  // Disable sleep

            EKey.IsPressed = true;
            EVENT_KeyPressed();
        } // if PWM==0
    } // if !is on
}

// ================================= Events ====================================
FORCE_INLINE void EVENT_KeyPressed(void) {
    if (ELED.IsOn) {
        ELED.IsOn = false;
        ELED.PWMDesired = 0;
    }
    else {
        ELED.IsOn = true;
        ELED.PWMDesired = PWM_MAX;
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
    PLLCSR |= (1<<LSM); // Set low-speed mode (32MHz), need for low-voltage operation
    PLLCSR |= (1<<PLLE); // Set PLL enable
    loop_until_bit_is_set (PLLCSR, PLOCK); // wait until PLOCK become 1
    PLLCSR |= (1<<PCKE); // Enable PCK
    // Set PWM mode; PCK is freq source. UnComment desired rows
    // ********* SingleChannelVCC **********
    TCCR1 = (1<<PWM1A)|(1<<COM1A1)|(1<<COM1A0)|(0<<CS13)|(0<<CS12)|(0<<CS11)|(1<<CS10);
}
FORCE_INLINE void PWMDisable(void){
    TCCR1  = 0x00; // Stop Timer1
    PLLCSR = 0x00; // Stop clock
}
bool MayChangePWM(void) {
    if (ELED.PWM <= PWMStepOver1) {
        return DelayElapsed(&ELED.Timer, PWMDelayLong);        // Low speed
    }
    else if (ELED.PWM > PWMStepOver1 && ELED.PWM <= PWMStepOver2) {
        return DelayElapsed(&ELED.Timer, PWMDelayMid);         // Mid-speed
    }
    else if (ELED.PWM > PWMStepOver2) {
        return DelayElapsed(&ELED.Timer, PWMDelayFast);        // High-speed
    }
    return false;
}

// ******************** Interrupts **************************
// Key interrupt
EMPTY_INTERRUPT (PCINT0_vect);

