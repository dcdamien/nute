#include "lcd110x.h"
#include "common.h"
#include "lcd_font.h"
#include <util/delay.h>

// ============================= Types & vars ==================================

// ============================ Implementation =================================
void LCD_Init(void) {
    LCD_DDR |= (1<<LCD_SCLK)|(1<<LCD_XCS)|(1<<LCD_XRES)|(1<<LCD_SDA)|(1<<LCD_BCKLT);
    LCD_BCKLT_OFF();
    LCD_SCLK_LO();
    LCD_XCS_HI();
    // Reset display
    LCD_XRES_LO();
    _delay_ms(7);
    LCD_XRES_HI();
    // Initial commands
    LCD_WriteCmd(0xA4); // Set normal display mode
    LCD_WriteCmd(0x2F); // Charge pump on
    LCD_WriteCmd(0x40); // Set start row address = 0
#ifdef LCD_UPSIDEDOWN
    LCD_WriteCmd(0xC8); // mirror Y axis
    LCD_WriteCmd(0xA1); // Mirror X axis
#endif
    LCD_WriteCmd(0xAF); // display ON
    LCD_Clear(); // clear LCD
}

void LCD_Clear(void) {
    LCD_WriteCmd(0x40); // Y = 0
    LCD_WriteCmd(0xB0);
    LCD_WriteCmd(0x10); // X = 0
    LCD_WriteCmd(0x00);
    for(uint16_t i=0;i<864;i++) LCD_WriteData(0x00);
}


void LCD_PrintString_P (const uint8_t x, const uint8_t y, const char *S, bool AInvert) {
    LCD_GotoXYstr(x, y);
    uint8_t FChar;
    while ((FChar = pgm_read_byte(S++)) != '\0')
        LCD_DrawChar(FChar, AInvert);
}
void LCD_PrintString (const uint8_t x, const uint8_t y, const char *S, bool AInvert) {
    LCD_GotoXYstr(x, y);
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
            LCD_WriteData(b);
        } // fx
    } // fy

}

void LCD_PrintUint(const uint8_t x, const uint8_t y, uint16_t ANumber) {
    uint8_t digit = '0';
    bool ShouldPrint = false;
    const uint16_t FArr[9] = {10000, 1000, 100, 10};
    LCD_GotoXYstr(x, y);
    // Iterate until ANumber > 10
    for(uint8_t i=0; i<4; i++) {
        while (ANumber >= FArr[i]) {
            digit++;
            ANumber -= FArr[i];
        }
        if((digit != '0') || ShouldPrint) {
                LCD_DrawChar(digit, false);
                ShouldPrint = true;
        }
        digit = '0';
    }
    // Print last digit
    LCD_DrawChar('0'+ANumber, false);
}
void LCD_PrintInt(const uint8_t x, const uint8_t y, int16_t ANumber) {
    LCD_GotoXYstr(x, y);
    if(ANumber < 0) {
        LCD_DrawChar('-', false);
        LCD_PrintUint(x+1, y, -ANumber);
    }
    else LCD_PrintUint(x, y, -ANumber);
}

// ============================= Special =======================================
// Special
FORCE_INLINE void LCD_DrawGauge(void) {
    LCD_DrawImage(0, GAUGE_Y, LCD_ImgGauge, false);
}
void LCD_GaugeValue(const uint8_t AValue) {
    LCD_GotoXY(1, GAUGE_Y+1);
    for(uint8_t x=1; x<AValue; x++)  LCD_WriteData(0x7E);
    for(uint8_t x=AValue; x<95; x++) LCD_WriteData(0x00);
}

void LCD_DrawChar(uint8_t AChar, bool AInvert) {
    uint8_t b;
    for(uint8_t i=0; i<6; i++) {
        b = pgm_read_byte(&Font_6x8_Data[AChar][i]);
        if(AInvert) b = ~b;
        LCD_WriteData(b);
    }
 }

// ============================ Inner use ======================================
void LCD_GotoXY(uint8_t x, uint8_t y) {
    LCD_WriteCmd(0xB0|(y&0x0F));         // Y axis initialisation: 0100 yyyy
    LCD_WriteCmd(0x00|(x&0x0F));         // X axis initialisation: 0000 xxxx ( x3 x2 x1 x0)
    LCD_WriteCmd(0x10|((x>>4)&0x07));    // X axis initialisation: 0010 0xxx  ( x6 x5 x4)
}
void LCD_GotoXYstr(uint8_t x, uint8_t y) {
    x = (x<<2)+(x<<1);                   // x=x*6
    LCD_WriteCmd(0xB0|(y&0x0F));         // Y axis initialisation: 0100 yyyy
    LCD_WriteCmd(0x00|(x&0x0F));         // X axis initialisation: 0000 xxxx ( x3 x2 x1 x0)
    LCD_WriteCmd(0x10|((x>>4)&0x07));    // X axis initialisation: 0010 0xxx  ( x6 x5 x4)
}

FORCE_INLINE void LCD_WriteData(uint8_t AByte) {
    LCD_SCLK_LO();
    LCD_XCS_LO();   // Select chip
    // Send "Data" bit
    LCD_SDA_HI();
    LCD_SCLK_HI();
    LCD_SCLK_LO();
    // Send byte
    for(uint8_t i=0; i<8; i++) {
        if(AByte & 0x80) LCD_SDA_HI();
        else LCD_SDA_LO();
        LCD_SCLK_HI();
        LCD_SCLK_LO();
        AByte <<= 1;
    }
    LCD_XCS_HI();
}
void LCD_WriteCmd(uint8_t AByte) {
    LCD_SCLK_LO();
    LCD_XCS_LO();   // Select chip
    // Send "Cmd" bit
    LCD_SDA_LO();
    LCD_SCLK_HI();
    LCD_SCLK_LO();
    // Send byte
    for(uint8_t i=0; i<8; i++) {
        if(AByte & 0x80) LCD_SDA_HI();
        else LCD_SDA_LO();
        LCD_SCLK_HI();
        LCD_SCLK_LO();
        AByte <<= 1;
    }
    LCD_XCS_HI();
}