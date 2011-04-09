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

    //Leds.GreenOn();

    FieldOn();

//    uint32_t InpTimer;
    while (1) {
        // Check inputs
        //if (Delay.Elapsed(&InpTimer, DELAY_CHECK)) {
//        if (Delay.Elapsed(&InpTimer, 350)) {
//            Leds.PWMReset();
//        }
//        //    Inputs.ReadConnections();
//            // Debug
//            Uart.PrintUint(Inputs.Inlets[0]);
//            Uart.Print(' ');
//            Uart.PrintUint(Inputs.Inlets[1]);
//            Uart.Print(' ');
//            Uart.PrintUint(Inputs.Inlets[2]);
//            Uart.Print(' ');
//            Uart.PrintUint(Inputs.Inlets[3]);
//            Uart.Print(' ');
//            Uart.PrintUint(Inputs.Inlets[4]);
//            Uart.NewLine();
//        } // if delay
    } // while (1)
}

void GeneralInit(void) {
    // Configure two bits for preemption priority
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay.Init();
    Uart.Init();

    Ticker.Init();
    Dac.Init();
    Leds.Init();

    //Inputs.Init();
    Inputs.OnRight = &EVENT_OnInputRight;
    Inputs.OnWrong = &EVENT_OnInputWrong;
    Inputs.OnNone  = &EVENT_OnInputNone;
}

void FieldOn(void) {
    // Enable timer and amplifier
    Dac.AmplifierOn();  // It would be desirable to put some delay after amplifier switching on to allow capacitors to charge.
    Dac.MayPlay = true;
    Leds.FieldOn();
    Ticker.On();
}
void FieldOff(void) {
    if (Dac.MayPlay) Dac.MayPlay = false;    // All the next will be performed automatically if playing now
    else {
        Leds.FieldOff();
        Ticker.Off();
        Dac.AmplifierOff();
    }
}

// ============================ Events =========================================
void EVENT_OnInputRight (void) {
    Leds.GreenOn();
    FieldOn();
}
void EVENT_OnInputWrong (void) {
    Leds.GreenOff();
    Leds.RedOn();
    FieldOff();
}
void EVENT_OnInputNone (void) {
    Leds.GreenOff();
    Leds.RedOff();
    FieldOff();
}


// ============================= IRQs ==========================================

