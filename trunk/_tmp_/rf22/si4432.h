/* 
 * File:   si4432.h
 * Author: Kreyl Laurelindo
 *
 * Created on 25 Декабрь 2010 г., 21:48
 */

#ifndef SI4432_H
#define	SI4432_H

#include "stm32f10x.h"

// ================================= Pins ======================================
#define SI_GPIO     GPIOA
#define SI_SDN      GPIO_Pin_0  // Shutdown pin
#define SI_NIRQ     GPIO_Pin_1
#define SI_SCK      GPIO_Pin_5  // SCK
#define SI_DO       GPIO_Pin_6  // MISO
#define SI_DI       GPIO_Pin_7  // MOSI
#define SI_NSEL     GPIO_Pin_8  // SS
// Clocks
#define SI_GPIO_CLK RCC_APB2Periph_GPIOA
#define SI_SPI_CLK  RCC_APB2Periph_SPI1

// ============================= Prototypes ====================================
void SI_Init (void);


#endif	/* SI4432_H */

