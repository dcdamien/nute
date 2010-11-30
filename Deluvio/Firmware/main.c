/* 
 * File:   main.c
 * Author: Kreyl Laurelindo
 *
 * Created on 29-11-2010 г., 19:48
 */


#include "main.h"
#include <avr/interrupt.h>
#include "lcd110x.h"
#include "sensors.h"

int main(void) {
    GeneralInit();
    
    LCD_PrintString_P(0, 2, PSTR("Deluvio"), false); 

    sei();
    
    while(1) {
        Task_Sensors();

        if(SensorIsTouched(3)) 
            LCD_BCKLT_ON();
        else 
            LCD_BCKLT_OFF();
    } // while(1)
}

FORCE_INLINE void GeneralInit(void) {
    QTouchInit();

    // Pumps
    PUMP_DDR |= (1<<PUMP1P)|(1<<PUMP2P)|(1<<PUMP3P)|(1<<PUMP4P);
    
    LCD_Init();
    
}

// Pumps
void PumpOn(enum pump_t APump) {
    switch (APump) {
        case Pump1: PUMP_PORT |= (1<<PUMP1P);
        case Pump2: PUMP_PORT |= (1<<PUMP2P);
        case Pump3: PUMP_PORT |= (1<<PUMP3P);
        case Pump4: PUMP_PORT |= (1<<PUMP4P);
    }
}
void PumpOff(enum pump_t APump) {
    switch (APump) {
        case Pump1: PUMP_PORT &= ~(1<<PUMP1P);
        case Pump2: PUMP_PORT &= ~(1<<PUMP2P);
        case Pump3: PUMP_PORT &= ~(1<<PUMP3P);
        case Pump4: PUMP_PORT &= ~(1<<PUMP4P);
    }
}



