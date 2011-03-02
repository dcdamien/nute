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
    Uart.PrintString("\rCC1101 TX\r");

    //uint32_t LEDTmr;
    while (1) {
      //  if (Delay.Elapsed(&LEDTmr, 250)) {
        //Delay.ms(200);
            //LED_TOGGLE();
            
//            uint8_t b = CC.ReadRegister(CC_IOCFG0);
//            Uart.PrintAsHex(b);
//            Uart.NewLine();
            //Uart.Print('a');
        //}
        //Delay.ms(200);
        Task_CC();
    }
}

void GeneralInit(void) {
    LEDInit();
    // Configure two bits for preemption priority
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay.Init();
    Uart.Init();
    CC.Init();
    
}

// ============================ Events =========================================
void EVENT_NewPacket(void) {
    Uart.NewLine();
    for (uint8_t i=0; i<CC_PKT_EXTRA_LEN; i++)
        Uart.PrintAsHex(CC.RX_PktArray[i]);
    Uart.NewLine();
}

// ============================= IRQs ==========================================

