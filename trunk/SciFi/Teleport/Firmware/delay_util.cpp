#include "delay_util.h"
#include "stm32f10x_tim.h"
#include "misc.h"

Delay_t Delay;
// =============================== Implementation ==============================
void Delay_t::Init(void) {
    // Interrupt config
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // Timer clock enable
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    // Time base configuration: 1 ms == 1000 Hz = FCLK / (100 * (FCLK/100 000))
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;   // Up-counter needed, nothing special
    TIM_TimeBaseStructure.TIM_ClockDivision     = 0;                    // Dead-time divisor, not needed here
    TIM_TimeBaseStructure.TIM_Period            = 100;                  // Auto-reload value
    TIM_TimeBaseStructure.TIM_Prescaler         = (uint16_t)(SystemCoreClock / 100000) - 1; // Input clock divisor
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
    // Enable timer
    TIM_Cmd(TIM7, ENABLE);
    // Clear Timer update pending flag
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
    // Interrupts config
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
}

bool Delay_t::Elapsed(uint32_t *AVar, const uint32_t ADelay) {
    if ((TickCounter - *AVar) >= ADelay) {
        *AVar = TickCounter;   // Reset delay
        return true;
    }
    else return false;
}

// ================================ Interrupts =================================
// Delay counter
void TIM7_IRQHandler (void) {
    // Clear TIM4 update interrupt
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
    Delay.IncreaseTickCounter();
}
