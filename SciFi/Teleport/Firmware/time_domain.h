/* 
 * File:   time_domain.h
 * Author: Kreyl Laurelindo
 *
 * Created on 14 Март 2011 г., 20:24
 */

#ifndef TIME_DOMAIN_H
#define	TIME_DOMAIN_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_dac.h"

// Timer2 is used as master timer

// DAC trigger
#define DAC_TRIGGER     DAC_Trigger_T2_TRGO

class Ticker_t {
public:
    void Init(void);
    void On(void)  { TIM_Cmd(TIM2, ENABLE);  }
    void Off(void) { TIM_Cmd(TIM2, DISABLE); }
};

extern Ticker_t Ticker;

// Declare DMA1_Channel3 IRQ. Use externC to make it visible from asm file.
extern "C" {
void DMA1_Channel3_IRQHandler(void);
}

#endif	/* TIME_DOMAIN_H */

