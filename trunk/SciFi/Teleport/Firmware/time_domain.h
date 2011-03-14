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
#define DAC_TRIGGER     DAC_Trigger_T6_TRGO

class Trigger_t {
public:
    void Init(void);
    void On(void)  { TIM_Cmd(TIM6, ENABLE);  }
    void Off(void) { TIM_Cmd(TIM6, DISABLE); }
};

extern Trigger_t Trigger;



#endif	/* TIME_DOMAIN_H */

