#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"
#include "dac.h"
#include "leds.h"
#include "time_domain.h"

#include "uart.h"

// ========================== Prototypes =======================================
void GeneralInit(void);

void PlayLoop(void);
void StopLoop(void);

void FieldOn(void);
// ========================== Implementation ===================================
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
    Uart.PrintString("\rTeleport\r");

    //Dac.PlayLoop();

    FieldOn();
    uint32_t LEDTmr;
    //Delay.Reset(&LEDTmr);
    while (1) {
        if (Delay.Elapsed(&LEDTmr, 400)) {
            LED_TOGGLE();
            //Dac.StopLoop();
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

    //Trigger.Init();
    Dac.Init();
    //Leds.Init();
}

void PlayLoop(void) {
    // Enable timer and amplifier
    Dac.AmplifierOn();  // It would be desirable to put some delay after amplifier switching on to allow capacitors to charge.
    Dac.MayPlay = true;
    //Trigger.On();
}
void StopLoop(void) {
    Dac.MayPlay = false;
}


void FieldOn(void) {
    PlayLoop();

}

// ============================ Events =========================================

// ============================= IRQs ==========================================

