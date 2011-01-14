#include "main.h"
#include "delay_util.h"
#include "common.h"

int main (void) {
    GeneralInit();

    struct Chnl_t Ch1 = {START1, Up, 0, QuickDelay, &OCR1A};
    struct Chnl_t Ch2 = {START2, Up, 0, QuickDelay, &OCR1B};
    
    while (1) {
        HandleCh (&Ch1);
        HandleCh (&Ch2);
    }
}

void HandleCh(struct Chnl_t* ACh) {
    if (!DelayElapsed(&ACh->Timer, ACh->Delay)) return;
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        if (ACh->Mode == Up) {
            ACh->PWM++;
            if (ACh->PWM == 250) ACh->Mode = Down;
        }
        else {
            ACh->PWM--;
            if (ACh->PWM == 0) ACh->Mode = Up;
        }
        // Setup delay
        ACh->Delay = (ACh->PWM < StepOver) ? SlowDelay : QuickDelay;
        // Change pwm value
        *(ACh->FOCR) = ACh->PWM;
    } // Atomic
}

FORCE_INLINE void GeneralInit(void) {
    // Setup IO
    DDRB  = (1<<PB1)|(1<<PB4);
    PORTB = 0;

    // Setup timer1
    OCR1C = 0xFF;
    OCR1A = START1;
    OCR1B = START2;
    // Init clock
    PLLCSR |= (1<<LSM); // Set low-speed mode (32MHz), need for low-voltage operation
    PLLCSR |= (1<<PLLE); // Set PLL enable
    loop_until_bit_is_set (PLLCSR, PLOCK); // wait until PLOCK become 1
    PLLCSR |= (1<<PCKE); // Enable PCK
    // Enable PWM1A Set COM1A1/A0: 10 for GND-based LED
    TCCR1 = (1<<PWM1A)|(1<<COM1A1)|(0<<COM1A0)|(0<<CS13)|(0<<CS12)|(0<<CS11)|(1<<CS10);
    // Enable PWM1B
    GTCCR = (1<<PWM1B)|(1<<COM1B1)|(0<<COM1B0);

    DelayInit();
    sei();
}
