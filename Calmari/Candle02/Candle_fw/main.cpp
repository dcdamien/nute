/*
 * main.cpp
 *
 *  Created on: 18.07.2011
 *      Author: Kreyl
 */

#include "main.h"
#include "avr/power.h"
#include "avr/pgmspace.h"

#include "uart_soft.h"
#include "sensors.h"

Light_t ELight;

// ========================= Implementation ====================================
int main(void) {
    GeneralInit();
    UARTSendString("Candle\r");

    while(1) {
        wdt_reset();
        EKeys.Task();
        ELight.Task();
    }
    return 0;
}

void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    clock_prescale_set(clock_div_8);    // 1 MHz

    Delay.Init();
    UARTInit();
    EKeys.Init();
    ELight.Init();

    sei();
}

// ============================= Events ========================================
void EVENT_KeyDown(void) {
    UARTSendString("Down\r");
    if (ELight.Indx == 0) return;
    ELight.Indx--;
    ELight.SetTableColor();
}
void EVENT_KeyUp(void) {
    UARTSendString("Up\r");
    if (ELight.Indx == (COLOR_COUNT-1)) return;
    ELight.Indx++;
    ELight.SetTableColor();
}
void EVENT_KeyOnOff(void) {
    UARTSendString("OnOff\r");


}
void EVENT_KeyLit(void) {
    UARTSendString("Lit\r");
    if (ELight.BlinkState == BlinkDisabled) {
        ELight.BlinkState = BlinkOn;
        Delay.Bypass(&ELight.BlinkTimer, LED_BLINK_ON_T);
    }
    else {
        ELight.BlinkState = BlinkDisabled;
    }
}

// ============================= Light =========================================
void Light_t::Init() {
    LED_DDR  |=   (1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P);
    LED_PORT &= ~((1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P));
    TCCR0A = (1<<WGM01)|(1<<WGM00);
    TCCR0B = (0<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00);
    TCCR2A = (1<<WGM21)|(1<<WGM20);
    TCCR2B = (0<<WGM22)|(0<<CS22)|(1<<CS21)|(0<<CS20);
    Delay.Reset(&Timer);
    R.TCCRxA = &TCCR0A;
    G.TCCRxA = &TCCR0A;
    B.TCCRxA = &TCCR2A;
    R.OCRx   = &OCR0A;
    G.OCRx   = &OCR0B;
    B.OCRx   = &OCR2B;
    R.TccrOnValue  = ((1<<COM0A1)|(0<<COM0A0));
    G.TccrOnValue  = ((1<<COM0B1)|(0<<COM0B0));
    B.TccrOnValue  = ((1<<COM2B1)|(0<<COM2B0));
    R.TccrOffValue = (uint8_t)(~((1<<COM0A1)|(1<<COM0A0)));
    G.TccrOffValue = (uint8_t)(~((1<<COM0B1)|(1<<COM0B0)));
    B.TccrOffValue = (uint8_t)(~((1<<COM2B1)|(1<<COM2B0)));

    Indx = 0;
    SetTableColor();
    //IsOn = false;
}

void Light_t::SetTableColor(void) {
    R.Desired = GetColor(Indx, 0);
    G.Desired = GetColor(Indx, 1);
    B.Desired = GetColor(Indx, 2);
    UARTSendUint(Indx);
    UARTSend(':');
    UARTSendAsHex(R.Desired);
    UARTSend(' ');
    UARTSendAsHex(G.Desired);
    UARTSend(' ');
    UARTSendAsHex(B.Desired);
    UARTNewLine();
}

void Light_t::Task() {
    if (BlinkState == BlinkOff) {
        if (Delay.Elapsed(&BlinkTimer, LED_BLINK_OFF_T)) {
            BlinkState = BlinkOn;
            AllOn();
        }
    }
    else {
        if (BlinkState == BlinkOn) {
            if (Delay.Elapsed(&BlinkTimer, LED_BLINK_ON_T)) {
                BlinkState = BlinkOff;
                AllOff();
                return;
            }
        }
        // Adjust colors
        if (Delay.Elapsed(&Timer, LED_STEP_T)) AllAdjust();
    }
}

void Channel_t::Adjust() {
    if (Desired < Current) {
        Current--;
        if (Current == 0) ATOMIC_BLOCK(ATOMIC_FORCEON) { *TCCRxA &= TccrOffValue; }
    }
    else if (Desired > Current) {
        if (Current == 0) ATOMIC_BLOCK(ATOMIC_FORCEON) { *TCCRxA |= TccrOnValue; }
        Current++;
    }
    ATOMIC_BLOCK(ATOMIC_FORCEON) { *OCRx = Current; }
}
