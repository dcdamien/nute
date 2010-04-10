#include "random.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define ADC_START( )	(ADCSRA |= (1<<ADSC))

struct Random_t ERandom;

void RandomStart(void){
    ERandom.IsReady = false;
    ERandom.Random = 0;
    ERandom.counter = 0;
}

void RandomAdd(uint8_t AData){
    if (ERandom.IsReady) return;
    ERandom.Random <<= 1;
    if (AData & 0x01) ERandom.Random++;
    ERandom.counter++;
    if (ERandom.counter == RANDOM_LENGTH) ERandom.IsReady = true;
}

