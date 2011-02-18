#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"

// Initialization
void GeneralInit(void);

void LEDInit(void) {
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = LED_PIN;

  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}

int main(void) {
    GeneralInit();
    while (1) {
        LED_TOGGLE();
        Delay.ms(100);
    }
}

void GeneralInit(void) {
    LEDInit();
    Delay.Init();
}
