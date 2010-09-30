#include "lcd110x.h"
#include "common.h"
#include "lcd_font.h"
#include <util/delay.h>

void LCD_Init(void) {
    LCD_DDR |= (1<<LCD_SCLK)|(1<<LCD_XCS)|(1<<LCD_XRES)|(1<<LCD_SDA);
    LCD_SCLK_LO();
    LCD_XCS_HI();
    // Reset display
    LCD_XRES_LO();
    _delay_ms(7);
    LCD_XRES_HI();
    // Initial commands
    LCD_Write(LCD_CMD, 0xA4);   // Set normal display mode
    LCD_Write(LCD_CMD, 0x2F);   // Charge pump on
    LCD_Write(LCD_CMD, 0x40);   // Set start row address = 0
    //LCD_Write(LCD_CMD, 0xC8); // mirror Y axis
    //LCD_Write(LCD_CMD, 0xA1); // Mirror X axis
    LCD_Write(LCD_CMD, 0xAF);   // display ON
    LCD_Clear(); // clear LCD
}

void LCD_Clear(void) {
    LCD_Write(LCD_CMD, 0x40); // Y = 0
    LCD_Write(LCD_CMD, 0xB0);
    LCD_Write(LCD_CMD, 0x10); // X = 0
    LCD_Write(LCD_CMD, 0x00);
    //Lcd_Write(CMD, 0xAE); // display OFF
    for(uint16_t i=0;i<864;i++) LCD_Write(LCD_DATA,0x00);
    //Lcd_Write(CMD,0xAF);  // display ON
}

void LCD_PrintString (const uint8_t x, const uint8_t y, const char *S, bool AInvert) {
    LCD_GotoXY(x, y);
    while (*S != '\0')
        LCD_DrawChar(*S++, AInvert);
}

void LCD_DrawImage(const uint8_t x, const uint8_t y, prog_uint8_t *I, bool AInvert) {
    uint8_t Width = pgm_read_byte(I++), Height = pgm_read_byte(I++);
    uint8_t b;
    for(uint8_t fy=y; fy<y+Height; fy++) {
        LCD_GotoXY(x, fy);
        for(uint8_t fx=x; fx<x+Width; fx++) {
            b = pgm_read_byte(I++);
            if(AInvert) b = ~b;
            LCD_Write(LCD_DATA, b);
        } // fx
    } // fy

}

// ============================ Inner use ======================================
void LCD_GotoXY(uint8_t x, uint8_t y) {
    LCD_Write(LCD_CMD,(0xB0|(y&0x0F)));         // Y axis initialisation: 0100 yyyy
    LCD_Write(LCD_CMD,(0x00|(x&0x0F)));         // X axis initialisation: 0000 xxxx ( x3 x2 x1 x0)
    LCD_Write(LCD_CMD,(0x10|((x>>4)&0x07))); // X axis initialisation: 0010 0xxx  ( x6 x5 x4)
}

void LCD_DrawChar(uint8_t AChar, bool AInvert) {
    uint16_t indx = (AChar<<2) + (AChar<<1);
    uint8_t b;
    prog_uint8_t *PointerFont = &Font_6x8_Data[indx];
    for(uint8_t i=0; i<6; i++) {
        b = pgm_read_byte(PointerFont);
        if(AInvert) b = ~b;
        LCD_Write(LCD_DATA, b);
        PointerFont++;
    }
 }

void LCD_Write(uint8_t AType, uint8_t AByte) {
    LCD_SCLK_LO();
    LCD_XCS_LO();   // Select chip
    // Send bit of data type
    if(AType == LCD_CMD) LCD_SDA_LO();
    else LCD_SDA_HI();
    nop();
    nop();
    LCD_SCLK_HI();
    nop();
    nop();
    LCD_SCLK_LO();
    // Send byte
    for(uint8_t i=0; i<8; i++) {
        if(AByte & 0x80) LCD_SDA_HI();
        else LCD_SDA_LO();
        nop();
        nop();
        LCD_SCLK_HI();
        nop();
        nop();
        LCD_SCLK_LO();
        AByte <<= 1;
    }
    LCD_XCS_HI();
}