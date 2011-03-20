#include "leds.h"
#include "stm32f10x_tim.h"
#include "sound_data.h"

#include "main.h"

Leds_t Leds;

void Leds_t::Init(void) {
    // ==== GPIO ====
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // Blue LEDs, PWM powered
    GPIO_InitStructure.GPIO_Pin = PWM1_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // Red, just on/off
    GPIO_InitStructure.GPIO_Pin = RED_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // Green, just on/off
    GPIO_InitStructure.GPIO_Pin = GREEN_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // ==== Timer4 as PWM ====
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 250;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    // ==== PWM ====
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 100;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM4, ENABLE);

    // ==== Timer3 as divider of play interval ====
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    // Slave Mode selection: TIM3 is clocked by TIM2
    TIM_SelectInputTrigger(TIM3, TIM_TS_ITR1);  // ITR1 for TIM3 means output of TIM2 (see table @ page 311)
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_External1);
    // Setup prescaler
    TIM_TimeBaseStructure.TIM_Period = SND1_LEN / (PWM_END - PWM_START) - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    // Interrupt config
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // Clear Timer update pending flag
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    // Interrupts config
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    
}

void Leds_t::FieldOn(void) {
    PWMReset();
    TIM_Cmd(TIM3, ENABLE);  // Enable sampling frequency divider
    TIM_Cmd(TIM4, ENABLE);  // Enable PWM
}
void Leds_t::FieldOff(void) {
    PWMSet(0);               // Shutdown output
    TIM_Cmd(TIM3, DISABLE);  // Disable sampling frequency divider
    TIM_Cmd(TIM4, DISABLE);  // Disable PWM
}

void Leds_t::PWMIncrease(void) {
    uint16_t CurPWM = PWMGet();
    if (CurPWM < PWM_END) {
        CurPWM++;
        PWMSet (CurPWM);
    }
}

// ================================ Interrupts =================================
// Delay counter
void TIM3_IRQHandler (void) {
    // Clear TIimer update interrupt
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    //LED_TOGGLE();
    Leds.PWMIncrease();
}
