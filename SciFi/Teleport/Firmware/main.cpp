#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"
#include "dac.h"
#include "leds.h"
#include "time_domain.h"

#include "uart.h"

// ========================== Prototypes =======================================
void GeneralInit(void);

void FieldOn(void);
void FieldOff(void);
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

    FieldOn();
    uint32_t LEDTmr;
    while (1) {
        if (Delay.Elapsed(&LEDTmr, 100)) {
            LEDTmr++; // dummy
            //LED_TOGGLE();
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

    Ticker.Init();
    Dac.Init();
    Leds.Init();
}

void FieldOn(void) {
    // Enable timer and amplifier
    Dac.AmplifierOn();  // It would be desirable to put some delay after amplifier switching on to allow capacitors to charge.
    Dac.MayPlay = true;
    Leds.FieldOn();
    Ticker.On();
}
void FieldOff(void) {
    Dac.MayPlay = false;    // All the next will be performed automatically
}




// ============================ Events =========================================

// ============================= IRQs ==========================================

