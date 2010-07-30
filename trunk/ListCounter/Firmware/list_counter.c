/* 
 * File:   list_counter.c
 * Author: Laurelindo
 *
 * Created on 30.07.2010, 11:09
 */
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "list_counter.h"
#include "time_utils.h"
#include "common.h"
#include "matrix_lcd.h"
#include "ee_store_uint32.h"

// ============================= Global =========================================
uint32_t ECounter;

// ============================== General ======================================
int main(void) {
    DDRC |= 1<<PC4;
    PORTC |= 1<<PC4;
    // Init LCD
    LCD_Init();
    // Display Ostranna info
    LCD_PrintString_P(4, 0, PSTR("Ostranna"));
    LCD_PrintString_P(0, 1, PSTR("ListCounter v1.0"));
    _delay_ms(2000);
    // Check if EEPROM is erased    
    EE_CheckIfErased();
    // Display initial count
    LCD_cls();
    LCD_PrintString_P(0, 0, PSTR("List count:"));
    ECounter = EE_ReadUint32();
    LCD_PrintUint32(0, 1, ECounter);

    while (1) {
        TASK_Lister();
        wdt_reset();    // Reset watchdog
    } // while
}

// ============================== Tasks ========================================
FORCE_INLINE void TASK_Lister(void) {
    _delay_ms(1000);
    EVENT_NewList();
}

// ============================== Events =======================================
void EVENT_NewList(void) {
    // Show star to blink
    LCD_SetCursor(15, 0);
    LCD_WriteChar('*');
    // Increase counter, save it and print it
    ECounter++;
    EE_WriteUint32(ECounter);
    LCD_PrintString_P(0, 1, PSTR("                "));  // Clear lower string
    LCD_PrintUint32(0, 1, ECounter);
    // Hide star
    LCD_SetCursor(15, 0);
    LCD_WriteChar(' ');
}
