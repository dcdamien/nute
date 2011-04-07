#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"
#include "dac.h"
#include "leds.h"
#include "time_domain.h"
#include "mdl_inputs.h"

#include "uart.h"

// ========================== Prototypes =======================================
void GeneralInit(void);

void FieldOn(void);
void FieldOff(void);
// ========================== Implementation ===================================

int main(void) {
    GeneralInit();
    Uart.PrintString("\rTeleport\r");

    Leds.GreenOn();
    
    FieldOn();
    while (1) {
        Inputs.Check();
    }
}

void GeneralInit(void) {
    // Configure two bits for preemption priority
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay.Init();
    Uart.Init();

    Ticker.Init();
    Dac.Init();
    Leds.Init();
    Inputs.Init();
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

