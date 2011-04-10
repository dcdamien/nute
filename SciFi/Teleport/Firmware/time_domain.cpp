#include "time_domain.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_tim.h"
#include "leds.h"
#include "dac.h"

Ticker_t Ticker;

void Ticker_t::Init(void) {
    // Timer clock enable
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;   // Up-counter needed, nothing special
    TIM_TimeBaseStructure.TIM_Period            = 363;                  // Auto-reload value
    TIM_TimeBaseStructure.TIM_Prescaler         = 1;                    // Input clock divisor: 8 MHz / (1+1) = 4 MHz;  4000 kHz / 363 = 11.025 kHz
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);               // Timer TRGO selection
    Off();
}

// ============================ Interrupts =====================================
// DMA interrupt to check if music is over
void DMA1_Channel3_IRQHandler(void) {
    // Test on DMA1 Channel3 Transfer Complete interrupt
    if(DMA_GetITStatus(DMA1_IT_TC3)) {
        // Clear DMA1 Channel3 Half Transfer, Transfer Complete and Global interrupt pending bits
        DMA_ClearITPendingBit(DMA1_IT_GL3);
        if (!Dac.MayPlay) {
            Ticker.Off();
            Dac.AmplifierOff();
            Leds.FieldOff();
            // Switch LEDs off to save energy
            Leds.RedOff();
            Leds.GreenOff();
        }
        else {
            // Reset LEDs' brightness
            Leds.PWMReset();
            // Handle repeat counter
            if (Dac.RepeatCount > 0) {
                Dac.RepeatCount--;
                if (Dac.RepeatCount == 0) Dac.MayPlay = false;
            }
        }
    } // if IT_TC3
}