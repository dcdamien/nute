#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"
#include "cc1101.h"
#include "uart.h"

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
    //Uart.PrintString("\rCC1101\r");

    uint32_t LEDTmr;
    while (1) {
        if (Delay.Elapsed(&LEDTmr, 50)) {
        //Delay.ms(200);
            LED_TOGGLE();
//            Uart.Print('a');
        }
        //Task_CC();
    }
}

void GeneralInit(void) {
    LEDInit();
    Delay.Init();
    //CC.Init();
    //Uart.Init();
}

// ============================ Events =========================================
void EVENT_NewPacket(void) {


}