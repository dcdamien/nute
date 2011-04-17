#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"
#include "dac.h"
#include "leds.h"
#include "time_domain.h"
#include "mdl_inputs.h"
#include "sound_data.h"

// ========================== Prototypes =======================================
void GeneralInit(void);

void FieldOn(void);
void FieldOff(void);
void AlarmOn(void);
// ========================== Implementation ===================================

int main(void) {
    GeneralInit();

    AlarmOn();
    // Blink LEDs
    for (uint8_t i=0; i<4; i++) {
        Leds.GreenOn();
        Delay.ms(100);
        Leds.GreenOff();
        Leds.RedOn();
        Delay.ms(100);
        Leds.RedOff();
    }

    uint32_t InpTimer;
    while (1) {
        // Check inputs
        if (Delay.Elapsed(&InpTimer, DELAY_CHECK)) Inputs.ReadInlets();
    } // while (1)
}

void GeneralInit(void) {
    // Configure two bits for preemption priority
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay.Init();

    Ticker.Init();
    Dac.Init();
    Leds.Init();

    Inputs.Init();
    Inputs.OnRight = &EVENT_OnInputRight;
    Inputs.OnWrong = &EVENT_OnInputWrong;
    Inputs.OnNone  = &EVENT_OnInputNone;
}

// =========================== Sound & LEDs ====================================
void FieldOn(void) {
    // Enable timer and amplifier
    Dac.WhatToPlay((uint32_t)&Snd1, SND1_LEN);
    Dac.AmplifierOn();  // It would be desirable to put some delay after amplifier switching on to allow capacitors to charge.
    Dac.MayPlay = true;
    Dac.RepeatCount = 0;    // Play infinitely
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
void AlarmOn(void) {
    Leds.FieldOff();
    Dac.WhatToPlay((uint32_t)&Snd2, SND2_LEN);
    Dac.AmplifierOn();  // It would be desirable to put some delay after amplifier switching on to allow capacitors to charge.
    Dac.MayPlay = true;
    Dac.RepeatCount = 9;
    Ticker.On();
}

// ============================ Events =========================================
void EVENT_OnInputRight (void) {
    Leds.GreenOn();
    Leds.RedOff();
    FieldOn();
}
void EVENT_OnInputWrong (void) {
    Leds.GreenOff();
    Leds.RedOn();
    FieldOff();
    AlarmOn();
}
void EVENT_OnInputNone (void) {
    Leds.GreenOff();
    Leds.RedOff();
    FieldOff();
}
