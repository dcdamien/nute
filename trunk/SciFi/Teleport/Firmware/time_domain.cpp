#include "time_domain.h"

Trigger_t Trigger;

void Trigger_t::Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,  ENABLE);
    //TIM_PrescalerConfig(TIM2, 1, TIM_PSCReloadMode_Update); // 8 MHz / (1+1) = 4 MHz;  4000 kHz / 250 = 16 kHz
    //TIM_SetAutoreload(TIM2, 250);                           // is used earlier
    TIM_PrescalerConfig(TIM6, 1, TIM_PSCReloadMode_Update); // 8 MHz / (1+1) = 4 MHz;  4000 kHz / 363 = 11.025 kHz
    TIM_SetAutoreload(TIM6, 363);                           // is used earlier
    TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);   // Timer TRGO selection
    // Set timer as master
    //TIM_SelectMasterSlaveMode(TIM6, TIM_MasterSlaveMode_Enable);
    Off();
}

