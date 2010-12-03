/* 
 * File:   main.c
 * Author: Kreyl Laurelindo
 *
 * Created on 29-11-2010 у., 19:48
 */

#include "main.h"
#include <avr/interrupt.h>
#include "lcd110x.h"
#include "sensors.h"
#include "delay_util.h"
#include "beep.h"
#include "time.h"
#include "menu.h"

struct pump_t Pumps[PUMP_COUNT];

int main(void) {
    GeneralInit();
    
    //LCD_PrintString_P(0, 2, PSTR("Рур"), false);
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
    Pumps[0].Enabled = true;
}

// Pumps
void PumpOn(uint8_t APump) {
    switch (APump) {
        case 1: PUMP_PORT |= (1<<PUMP1P); break;
        case 2: PUMP_PORT |= (1<<PUMP2P); break;
        case 3: PUMP_PORT |= (1<<PUMP3P); break;
        case 4: PUMP_PORT |= (1<<PUMP4P); break;
        default: break;
    }
}

// ============================= Events ========================================
// Time events
void EVENT_NewMinute(void) {
    if(EState == StIdle) LCD_PrintTime(PRINT_TIME_X, PRINT_TIME_Y, false, false, false);
}