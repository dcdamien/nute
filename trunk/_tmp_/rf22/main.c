#include "stm32f10x.h"
#include "delay_util.h"
#include "uart.h"
#include "si4432.h"

#define LED1_PIN                         GPIO_Pin_9
#define LED1_GPIO_PORT                   GPIOC
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOC


void LEDInit(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = LED1_PIN;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
}

void LEDOn(void)
{
  LED1_GPIO_PORT->BSRR = GPIO_Pin_9;
}

void LEDOff(void)
{
  LED1_GPIO_PORT->BRR = GPIO_Pin_9;
}

void SysTick_Handler (void) {
  static uint32_t ticks;

  if (ticks++ >= 11) {
    ticks = 0;
    LED1_GPIO_PORT->ODR ^= GPIO_Pin_9;

    //SI_WriteRegister(0x25, 0x55);
    //SI_ReadRegister(1);

    //UARTSend('a');
  }
}


int main(void) {
    LEDInit();
    UARTInit();
    SI_Init();
    
    SysTick_Config(SystemCoreClock / 100);

    while (1) {
        //UARTSend('a');
    }
}
