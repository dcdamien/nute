#include "random.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define ADC_START( )	(ADCSRA |= (1<<ADSC))

struct Random_t ERandom;

void RandomStart(void){
    ERandom.IsReady = false;
    ERandom.Random = 0;
    ERandom.counter = 0;
    DDRA &= ~((1<<PA0)|(1<<PA1));
    PORTA &= ~((1<<PA0)|(1<<PA1));
    //PORTA |= (1<<PA0);
    // Setup ADC
    // Ref = AVcc, not left-adjusted, Channel GND
    ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX4)|(1<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0);
    // ADC on, trigger start disabled, irq enabled, division 8
    ADCSRA = (1<<ADEN)|(0<<ADATE)|(1<<ADIE)|(0<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    // Start first conversion
    ADC_START();
}

// Interrupt
ISR (ADC_vect){
    ERandom.Random <<= 1;
    if (bit_is_set (ADCL, 0)) ERandom.Random++;
    ERandom.counter++;
    if (ERandom.counter == RANDOM_LENGTH) ERandom.IsReady = true;
    else ADC_START();
}