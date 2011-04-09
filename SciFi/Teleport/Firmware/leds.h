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
#include "stm32f10x_tim.h"

// Defines
#define PWM1_PIN    GPIO_Pin_6

#define RED_PIN     GPIO_Pin_7
#define GREEN_PIN   GPIO_Pin_8

// Timings & steps calculated in EXCEL
#define PWM_DIV1    198
#define PWM_DIV2    135
#define PWM_DIV3    45
#define PWM_DIV4    18

#define PWM_MIN     7
#define PWM_STEP1   36
#define PWM_STEP2   54
#define PWM_MAX     254


// Types
class Leds_t {
private:
    uint16_t FPWM;
    bool FadeOut;
    void PWMSet(uint16_t APWM) { TIM4->CCR1 = APWM; }
    void SetDivider(uint16_t ADiv) { TIM_SetAutoreload(TIM3, ADiv); }
public:
    void Init(void);
    // Indicators
    void RedOn(void)    { GPIOB->BSRR = RED_PIN; }
    void RedOff(void)   { GPIOB->BRR  = RED_PIN; }
    void GreenOn(void)  { GPIOB->BSRR = GREEN_PIN; }
    void GreenOff(void) { GPIOB->BRR  = GREEN_PIN; }
    // FieldPWMSet(PWM_MIN);
    void PWMChange(void);
    void PWMReset(void) { FPWM = PWM_MIN; FadeOut = false; }
    void FieldOn(void);
    void FieldOff(void);
};

extern Leds_t Leds;

// Declare Timer IRQ. Use externC to make it visible from asm file.
extern "C" {
extern void TIM3_IRQHandler(void);
}


#endif	/* LEDS_H */

