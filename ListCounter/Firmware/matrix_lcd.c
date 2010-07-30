#include "matrix_lcd.h"
#include "common.h"
#include <util/delay.h>

void LCD_Init(void) {
    // Ports setup
    LCD_CNTR_DDR  |=   (1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_E);
    LCD_CNTR_PORT &= ~((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_E));
    // Initial setup: set 8-bit mode thrice

    _delay_ms(15);
    LCD_CNTR_PORT |= (1<<LCD_DATA5)|(1<<LCD_DATA4);

    _delay_ms(5);
    _delay_ms(1);
    // Set 4-bit mode
    LCD_BusyWaitBF();
    LCD_Command(0b00100000); // Set 4-bit mode
    // Repeat 4-bit mode with needed F & N flags
    LCD_BusyWaitBF();
    PORTC &= ~(1<<PC4);
    #ifdef LCD_2_LINE
    LCD_Command(0b00101000);
    #else
    LCD_Command(0b00100000);
    #endif
    

    //LCD_cls();

}

FORCE_INLINE void LCD_cls(void) {
    LCD_BusyWaitBF();
    LCD_Command(0x01);
}

void LCD_WriteChar(uint8_t AChar) {
    LCD_BusyWaitBF();
    LCD_RS_HI();
    LCD_Command(AChar);
    LCD_RS_LO();
}

void LCD_SetCursor(uint8_t x, uint8_t y) {
    uint8_t FNumber = 0x80;
    FNumber += x;
    if (y==1) FNumber += 0x40;
    LCD_BusyWaitBF();
    LCD_Command(FNumber);
}

// ============================= Inner use =====================================
void LCD_BusyWaitBF(void) {
    uint8_t Reply;
    do {
        Reply = LCD_ReadCntr();
    } while (Reply & 0x80);
}

uint8_t LCD_ReadCntr(void) {
    // Set COMMAND mode
    LCD_RS_LO();
    return LCD_Read();
}

void LCD_Command(uint8_t ACmd) {
    // Set COMMAND mode
    LCD_RS_LO();
    LCD_Write(ACmd);
}

FORCE_INLINE void LCD_Write(uint8_t AByte) {
    uint8_t tetra;
    // Set data lines as outputs
    LCD_DATA_DDR |= (1<<LCD_DATA7)|(1<<LCD_DATA6)|(1<<LCD_DATA5)|(1<<LCD_DATA4);
    // Set WRITE mode
    LCD_RW_LO();
    // Write upper tetra
    tetra = AByte & 0xF0;
    tetra >>= 1;
    LCD_DATA_PORT &= ~((1<<LCD_DATA7)|(1<<LCD_DATA6)|(1<<LCD_DATA5)|(1<<LCD_DATA4));
    LCD_DATA_PORT |= tetra;
    LCD_E_HI();
    asm volatile (
        "nop"   "\n\t"
        "nop"   "\n\t"
        "nop"   "\n\t"
    ::);
    LCD_E_LO();
    // Write lower tetra
    asm volatile (
        "nop"   "\n\t"
        "nop"   "\n\t"
        "nop"   "\n\t"
    ::);
    tetra = AByte & 0x0F;
    tetra <<= 3;
    LCD_DATA_PORT &= ~((1<<LCD_DATA7)|(1<<LCD_DATA6)|(1<<LCD_DATA5)|(1<<LCD_DATA4));
    LCD_DATA_PORT |= tetra;
    LCD_E_HI();
    asm volatile (
        "nop"   "\n\t"
        "nop"   "\n\t"
        "nop"   "\n\t"
    ::);
    LCD_E_LO();
}
FORCE_INLINE uint8_t LCD_Read(void) {
    uint8_t tetra, result;
    // Set data lines as inputs
    LCD_DATA_DDR &= ~((1<<LCD_DATA7)|(1<<LCD_DATA6)|(1<<LCD_DATA5)|(1<<LCD_DATA4));
    // Set READ mode
    LCD_RW_HI();
    // Read hi tetra
    LCD_E_HI();
    asm volatile (
        "nop"   "\n\t"
        "nop"   "\n\t"
        "nop"   "\n\t"
    ::);
    tetra = LCD_ReadWrite();
    LCD_E_LO();
    tetra <<= 1;
    result = tetra & 0xF0;
    // Read low tetra
    asm volatile (
        "nop"   "\n\t"
        "nop"   "\n\t"
        "nop"   "\n\t"
    ::);
    LCD_E_HI();
    asm volatile (
        "nop"   "\n\t"
        "nop"   "\n\t"
        "nop"   "\n\t"
    ::);
    tetra = LCD_ReadWrite();
    LCD_E_LO();
    tetra >>= 3;
    result |= (tetra & 0x0F);
}

