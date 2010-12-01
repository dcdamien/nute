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
#include "delay_util.h"
#include "beep.h"
#include "time.h"

int main(void) {
    GeneralInit();
    
    LCD_PrintString_P(0, 2, PSTR("Deluvio"), false); 
    //Beep(2);

    sei();
    
    while(1) {
        Task_Sensors();
        Task_Beep();
    } // while(1)
}

FORCE_INLINE void GeneralInit(void) {
    QTouchInit();
    DelayInit();
    BeepInit();
    LCD_Init();
    TimeInit();
    // Pumps
    PUMP_DDR |= (1<<PUMP1P)|(1<<PUMP2P)|(1<<PUMP3P)|(1<<PUMP4P);
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

// Time
void PrintTime(uint8_t x, uint8_t y) {
    LCD_GotoXYstr(x, y);
    
}

// ============================= Events ========================================
// Key events
void EVENT_KeyDown(void) {
    Beep(1);
    LCD_GotoXY(0,0);
    LCD_DrawChar('D', false);
}
void EVENT_KeyUp(void) {
    Beep(1);
    LCD_GotoXY(0,0);
    LCD_DrawChar('U', false);
}
void EVENT_KeyMenu(void) {
    Beep(1);
    LCD_GotoXY(0,0);
    LCD_DrawChar('M', false);
}
void EVENT_KeyAqua(void) {
    Beep(1);
    LCD_GotoXY(0,0);
    LCD_DrawChar('A', false);
}

// Time events
void EVENT_NewHour(void) {

}
void EVENT_NewMinute(void) {
    
}