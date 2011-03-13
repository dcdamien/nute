#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"
#include "dac.h"

#include "uart.h"

#include "stm32f10x_tim.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_dma.h"


// Initialization
void GeneralInit(void);

void LEDInit(void) {
  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = LED_PIN;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}

int main(void) {
    GeneralInit();
    Uart.PrintString("\rDAC\r");

    Dac.PlayLoop();

    uint32_t LEDTmr;
    Delay.Reset(&LEDTmr);
    while (1) {
        if (Delay.Elapsed(&LEDTmr, 6000)) {
            LED_TOGGLE();
            Dac.StopLoop();
//            Uart.PrintAsHex(b);
//            Uart.NewLine();
            //Uart.Print('a');
        }
    }
}

void GeneralInit(void) {
    LEDInit();
    // Configure two bits for preemption priority
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay.Init();
    Uart.Init();
    Dac.Init();
}

// ============================ Events =========================================

// ============================= IRQs ==========================================

