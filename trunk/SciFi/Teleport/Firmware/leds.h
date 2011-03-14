/* 
 * File:   leds.h
 * Author: Kreyl Laurelindo
 *
 * Created on 12 Март 2011 г., 15:07
 */

#ifndef LEDS_H
#define	LEDS_H

#include "stm32f10x.h"

// Defines
#define PWM1_PIN    GPIO_Pin_6

#define RED_PIN     GPIO_Pin_7
#define GREEN_PIN   GPIO_Pin_8

#define PWM_START   40  // Start value for when music starts
#define PWM_END     250

// Types
class Leds_t {
public:
    void Init(void);
    // Indicators
    void RedOn(void)    { GPIOB->BSRR = RED_PIN; }
    void RedOff(void)   { GPIOB->BRR  = RED_PIN; }
    void GreenOn(void)  { GPIOB->BSRR = GREEN_PIN; }
    void GreenOff(void) { GPIOB->BRR  = GREEN_PIN; }
};

extern Leds_t Leds;


#endif	/* LEDS_H */

