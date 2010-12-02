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
#include "menu.h"

int main(void) {
    GeneralInit();
    
    //LCD_PrintString_P(0, 2, PSTR("Ага"), false);
    //Beep(2);

    sei();

    SetState(StIdle);
    
    while(1) {
        Task_Sensors();
        Task_Beep();
        Task_Time();
        Task_Menu();
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

// ============================= Events ========================================
// Time events
void EVENT_NewMinute(void) {
    if(EState == StIdle) {
        LCD_PrintTime(PRINT_TIME_X, PRINT_TIME_Y);
        if(!Time.IsSetCorrectly) LCD_PrintString_P(0, PRINT_TIME_Y+2, PSTR("Установите время"), false);
    }
}