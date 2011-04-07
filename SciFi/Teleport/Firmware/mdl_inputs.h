/* 
 * File:   mdl_inputs.h
 * Author: Kreyl
 *
 * Created on April 5, 2011, 1:22 AM
 */

#ifndef MDL_INPUTS_H
#define	MDL_INPUTS_H

#include "stm32f10x.h"

#define DELAY_CHECK     1000     // ms

// Ports
#define M1_GPIO GPIOB
#define M1_1    GPIO_Pin_5      // LCD_XRES, 1
#define M1_2    GPIO_Pin_2      // LCD_XCS,  2
#define M1_3    GPIO_Pin_10     // LCD_SDA,  4

#define M2_GPIO GPIOB
#define M2_1    GPIO_Pin_12     // LCD_SCLK, 5
#define M2_2    GPIO_Pin_0      // LCD_BCKLT, 8
#define M2_3    GPIO_Pin_1      // SD_POWER, 1

#define M3_GPIO GPIOB
#define M3_1    GPIO_Pin_9      // SD_DETECT, 2
#define M3_2    GPIO_Pin_11     // SD_CS, 3
#define M3_3    GPIO_Pin_13     // SD_SCK, 4

#define M4_GPIO GPIOB
#define M4_1    GPIO_Pin_14     // SD_MISO, 5
#define M4_2    GPIO_Pin_15     // SD_MOSI, 6
#define M4_3    GPIO_Pin_3      // JTDO, 4 of JTAG

#define M5_GPIO GPIOA
#define M5_1    GPIO_Pin_10     // RX1, 1
#define M5_2    GPIO_Pin_11     // USB_DM
#define M5_3    GPIO_Pin_12     // USB_DP

class Inputs_t {
private:
    uint32_t Timer;
    uint8_t Inlets[5];
public:
    void Init(void);
    void Check(void);
    bool ChangeOccured;
};

extern Inputs_t Inputs;

#endif	/* MDL_INPUTS_H */

