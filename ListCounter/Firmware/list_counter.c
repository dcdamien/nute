/* 
 * File:   list_counter.c
 * Author: Laurelindo
 *
 * Created on 30.07.2010, 11:09
 */
#include <avr/io.h>
#include <avr/wdt.h>
#include "list_counter.h"
#include "time_utils.h"
#include "common.h"
#include "matrix_lcd.h"

// ============================= Types =========================================

// ============================== General ======================================
int main(void) {
    DDRC |= 1<<PC4;
    PORTC |= 1<<PC4;
    GeneralInit();

    //LCD_SetCursor(0, 0);
    //LCD_WriteChar('f');

    sei(); 
    while (1) {
        wdt_reset();    // Reset watchdog
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    LCD_Init();
}

// ============================== Tasks ========================================


// ============================== Events =======================================

