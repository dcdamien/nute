/* 
 * File:   leds.h
 * Author: Kreyl Laurelindo
 *
 * Created on 12 Март 2011 г., 15:07
 */

#ifndef LEDS_H
#define	LEDS_H

#include "stm32f10x.h"
#include <inttypes.h>

// Defines
#define PWM1_PIN    GPIO_Pin_6

#define RED_PIN     GPIO_Pin_7
#define GREEN_PIN   GPIO_Pin_8

#define PWM_START   40  // Start value for when music starts
#define PWM_END     250

// Types
class Leds_t {
private:
    void PWMSet(uint16_t APWM) { TIM4->CCR1 = APWM; }
    uint16_t PWMGet(void) { return (uint16_t)(TIM4->CCR1); }
public:
    void Init(void);
    // Indicators
    void RedOn(void)    { GPIOB->BSRR = RED_PIN; }
    void RedOff(void)   { GPIOB->BRR  = RED_PIN; }
    void GreenOn(void)  { GPIOB->BSRR = GREEN_PIN; }
    void GreenOff(void) { GPIOB->BRR  = GREEN_PIN; }
    // Field
    void PWMIncrease(void);
    void PWMReset(void) { PWMSet(PWM_START); }
    void FieldOn(void);
    void FieldOff(void);
};

extern Leds_t Leds;

// Declare Timer IRQ. Use externC to make it visible from asm file.
extern "C" {
extern void TIM3_IRQHandler(void);
}


#endif	/* LEDS_H */

