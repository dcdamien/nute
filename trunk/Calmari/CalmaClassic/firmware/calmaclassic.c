#include <avr/io.h>
#include <avr/wdt.h>
#include "calmaclassic.h"
#include "time_utils.h"
#include "common.h"

// =================================== Types ===================================
struct {
    uint8_t PWM, PWMDesired;
    uint16_t Timer;
    bool IsOn;
} ELED;
struct {
    uint16_t Timer;
    uint16_t Value;
    bool Measuring;
    uint8_t Counter;
} EADC;
struct {
    uint16_t Timer;
    bool IsPressed;
} EKey;

// =============================== Implementation ==============================
int main(void) {
    GeneralInit();
 
    while(1) {
        wdt_reset();
        Key_Task();
        LED_Task();
        ADC_Task();
        Sleep_Task();
    }
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);    // Enable WatchDog at 2 s
    ACSR |= (1<<ACD);       // Shutdown comparator
    // Setup IO
    DDRB  = (0<<KeyPin)|(1<<LedPin);
    PORTB = (0<<KeyPin)|(1<<LedPin); // VCC-based LED, GND-pulled key
    // Enable Key IRQ
    PCMSK = (1<<KeyPin);
    EnableKeyIRQ();

    // Init LED
    ELED.PWMDesired = PWMStartValue;    // Light-up at power-on
    ELED.PWM = 0;
    TimerResetDelay(&ELED.Timer);
    ELED.IsOn = true;

    // ADC
    TimerResetDelay(&EADC.Timer);
    EADC.Measuring = false;

    // Key
    TimerResetDelay(&EKey.Timer);
    EKey.IsPressed = false;

    TimerInit();
}

// ================================== Tasks ====================================
FORCE_INLINE void Key_Task(void) {
    if (TimerDelayElapsed(&EKey.Timer, KEY_POLL_TIMEOUT)) {
        if (!EKey.IsPressed && KEY_IS_DOWN()) {
            EKey.IsPressed = true;
            EVENT_KeyPressed();
        }
        else if (EKey.IsPressed && !KEY_IS_DOWN()) {
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
FORCE_INLINE void ADC_Task(void) {
    // Check if time to measure
    if (!EADC.Measuring) {
        if (TimerDelayElapsed(&EADC.Timer, ADC_TIMEOUT)) { // Start measure
            EADC.Counter = 0;
            EADC.Value = 0;
            EADC.Measuring = true;
            ADC_Start();
        }
    }
    else { // Is measuring
        // Check if conversion completed
        if (bit_is_clear(ADCSRA, ADSC)) {   // completed
            if (EADC.Counter != 0) {        // Discard first conversion
                ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                    EADC.Value += ADC;
                }
            } // if !=0
            EADC.Counter++;
            // Check if measure completed
            if (EADC.Counter > ADC_NUMBER_OF_MEASURES) {
                EADC.Measuring = false;
                TimerResetDelay(&EADC.Timer);
                ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                    EADC.Value >>= ADC_POWER_OF_MEASURES;
                }
                EVENT_ADC_Done();
            } // if measure completed
        } // if conversion completed
    }
}
FORCE_INLINE void Sleep_Task(void) {
    // Check if is off
    if (!ELED.IsOn) {
        // Check if fade completed and key depressed
        if ((ELED.PWM == 0) && (!EKey.IsPressed)) { // Time to sleep!
            // No need to stop timer as in power-down mode it is stopped
            // Stop ADC
            ADCSRA = (0<<ADEN)|(0<<ADSC)|(0<<ADATE)|(1<<ADIF)|(0<<ADIE)|(0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

            MCUCR = (1<<SE)|(1<<SM1)|(0<<SM0);  // Enable sleep in power-down mode
            EnableKeyIRQ();
            wdt_disable();                      // Disable Watchdog
            // Fall asleep
            asm volatile (
                    "sei"	"\n\t"
                    "sleep"	"\n\t"
                    "cli"	"\n\t"
            ::);
            wdt_enable(WDTO_2S);    // Enable WatchDog at 2 s
            DisableKeyIRQ();
            MCUCR = (0<<SE)|(0<<SM1)|(0<<SM0);  // Disable sleep
        } // if PWM==0
    } // if !is on
}

// ================================= Events ====================================
FORCE_INLINE void EVENT_ADC_Done(void) {
    if (!ELED.IsOn) return;
    // Adjust current
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (EADC.Value > ILedNominal && ELED.PWMDesired > 0)        ELED.PWMDesired--;
        if (EADC.Value < ILedNominal && ELED.PWMDesired < PWM_MAX)  ELED.PWMDesired++;
    }
}
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
        return TimerDelayElapsed(&ELED.Timer, PWMDelayLong);        // Low speed
    }
    else if (ELED.PWM > PWMStepOver1 && ELED.PWM <= PWMStepOver2) {
        return TimerDelayElapsed(&ELED.Timer, PWMDelayMid);         // Mid-speed
    }
    else if (ELED.PWM > PWMStepOver2) {
        return TimerDelayElapsed(&ELED.Timer, PWMDelayFast);        // High-speed
    }
    return false;
}

void ADC_Start(void) {
    // 1.1 V reference w/o capacitor, not left-adjusted, channel dif ADC2-ADC3 x20
    ADMUX = (0<<REFS2)|(1<<REFS1)|(0<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
    // Unipolar mode, not reversed polarity
    ADCSRB = (0<<BIN)|(0<<IPR);
    // Start first conversion
    // ADC enabled, IRQ disabled, 125 kHz
    ADCSRA = (1<<ADEN)|(1<<ADSC)|(0<<ADATE)|(1<<ADIF)|(0<<ADIE)|(0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    // leave ADC enabled
}

// ******************** Interrupts **************************
// Key interrupt
EMPTY_INTERRUPT (PCINT0_vect);

