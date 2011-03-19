#include "time_domain.h"

Ticker_t Ticker;

void Ticker_t::Init(void) {
    // Timer clock enable
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;   // Up-counter needed, nothing special
    TIM_TimeBaseStructure.TIM_ClockDivision     = 0;                    // Dead-time divisor, not needed here
    TIM_TimeBaseStructure.TIM_Period            = 363;                  // Auto-reload value
    TIM_TimeBaseStructure.TIM_Prescaler         = 1;                    // Input clock divisor: 8 MHz / (1+1) = 4 MHz;  4000 kHz / 363 = 11.025 kHz
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);   // Timer TRGO selection
    // Set timer as master
    //TIM_SelectMasterSlaveMode(TIM6, TIM_MasterSlaveMode_Enable);
    Off();
}

