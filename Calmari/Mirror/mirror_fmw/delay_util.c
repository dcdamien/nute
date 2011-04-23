#include <avr/io.h>

#include "delay_util.h"
#include "common.h"

volatile uint16_t TickCounter;

FORCE_INLINE void DelayInit(void) {
    // Millisecond timer initialization, with output compare interrupt enabled
    TCCR1A = 0;
    TCCR1B = (0<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10); // CTC mode, 1 MHz/8 = 125 kHz
    OCR1A  = 125;                           // 125 kHz / 125 = 1000 compares per second
    TIMSK1 |= (1<<OCIE1A);                  // Enable interrupt
}

bool DelayElapsed(uint16_t *AVar, const uint16_t ADelay) {
    bool Result = false;
    ATOMIC_BLOCK (ATOMIC_RESTORESTATE) {
        if ((TickCounter - *AVar) >= ADelay) {
            *AVar = TickCounter;   // Reset delay
            Result = true;
        }
    } // Atomic
    return Result;
}

void DelayReset(uint16_t *AVar) {
    ATOMIC_BLOCK (ATOMIC_RESTORESTATE) {
        *AVar = TickCounter;
    }
}

// ================================ Interrupts =================================
// Delay counter
ISR (TIMER1_COMPA_vect, ISR_BLOCK) {
	TickCounter++;
}