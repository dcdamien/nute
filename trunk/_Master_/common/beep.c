#include "beep.h"
#include "common.h"
#include "delay_util.h"
#include <avr/io.h>
#include <stdbool.h>

struct {
    uint16_t Timer;
    uint8_t Count;
    bool IsYelling;
} EBeep;

void BeepOn(void);
void BeepOff(void);

// ============================ Implementation =================================
void Task_Beep(void) {
    if(EBeep.Count == 0) return;
    if(EBeep.IsYelling) {
        // Check if time to silence
        if(DelayElapsed(&EBeep.Timer, BEEP_ON_TIME)) {
            BeepOff();
            EBeep.IsYelling = false;
            EBeep.Count--;
        }
    } // if yelling
    else {
        // Check if time to yell
        if(DelayElapsed(&EBeep.Timer, BEEP_OFF_TIME)) {
            BeepOn();
            EBeep.IsYelling = true;
        }
    }
}

void Beep(uint8_t ACount) {
    EBeep.Count = ACount;
    EBeep.IsYelling = true;
    DelayReset(&EBeep.Timer);
    BeepOn();
}

void BeepInit(void) {
    // Setup variables
    EBeep.Count = 0;
    EBeep.IsYelling = false;
    // Setup output - OC1A, PD5
    DDRD  |= 1<<PD5;
    PORTD |= 1<<PD5;
}

FORCE_INLINE void BeepOn(void) {
    // Setup Timer1
    ICR1L = BEEP_TOP_VALUE;
    OCR1AL = BEEP_TOP_VALUE/2;
    TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(0<<WGM10);
    TCCR1B = (1<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10);
}
FORCE_INLINE void BeepOff(void) {
    TCCR1A = 0;
    TCCR1B = 0;
}
