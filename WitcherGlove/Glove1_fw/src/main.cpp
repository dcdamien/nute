/*
 * File:   main.cpp
 * Author: Kreyl
 * Project: klNfcF0
 *
 * Created on May 27, 2011, 6:37 PM
 */

#include "ch.h"
#include "hal.h"

#include "kl_lib_f2xx.h"
#include "acc.h"

#include "application.h"
#include "ManyLed.h"
#include "vibro.h"
#include "infrared.h"

#define TESTING

static inline void Init();

#ifndef TESTING
static inline bool IsUsbPowered() { return  PinIsSet(GPIOA, 9); }
static inline bool IsCharging()   { return !PinIsSet(GPIOB, 2); }
#endif

// Application entry point.
int main() {
    // ==== Setup clock ====
    uint8_t ClkResult = 1;
    Clk.SetupFlashLatency(16);  // Setup Flash Latency for clock in MHz
    // 16 MHz/8 = 2; 2*192 = 384; 384/8 = 48 (preAHB divider); 384/8 = 48 (USB clock)
    //Clk.SetupPLLDividers(8, 192, pllSysDiv8, 8);
    // 48/4 = 12 MHz core clock. APB1 & APB2 clock derive on AHB clock
    //Clk.SetupBusDividers(ahbDiv1, apbDiv1, apbDiv1);
    //if((ClkResult = Clk.SwitchToPLL()) == 0) Clk.HSIDisable();
    Clk.UpdateFreqValues();

    // ==== Init OS ====
    halInit();
    chSysInit();
    // ==== Init Hard & Soft ====
    Init();
    // Report problem with clock if any
    if(ClkResult) Uart.Printf("Clock failure\r");
#ifndef TESTING
//    bool WasUsb=false;
#endif
    while(TRUE) {
#ifndef TESTING
        chThdSleepMilliseconds(999);
        // Detect power change
//        if(!WasUsb and IsUsbPowered()) {
//            BlueLed.On(4);
//            WasUsb = true;
//            App.Enabled = false;
//            // Lower CPU freq
//            chSysLock();
//            Clk.SetupBusDividers(ahbDiv64, apbDiv1, apbDiv1);
//            Clk.UpdateFreqValues();
//            Clk.UpdateSysTimer();
//            chSysUnlock();
//        }
//        else if(WasUsb and !IsUsbPowered()) {
//            BlueLed.Off();
//            WasUsb = false;
//            // Speed-up CPU
//            chSysLock();
//            Clk.SetupBusDividers(ahbDiv4, apbDiv1, apbDiv1);
//            Clk.UpdateFreqValues();
//            Clk.UpdateSysTimer();
//            chSysUnlock();
//            App.Enabled = true;
//        }
//
//        // Indicate charging
//        if(IsUsbPowered()) {
//            if(IsCharging()) GreenLed.On(4);
//            else GreenLed.Off();
//        }
#else
        chThdSleepMilliseconds(999);
        if(!Acc[0].IsOperational) {
            Uart.Printf("Acc fail\r");
            Acc[0].Init();
        }
        else {
            Acc[0].ReadAccelerations();
            Uart.Printf("%d %d %d\r", Acc[0].a[0], Acc[0].a[1], Acc[0].a[2]);
        }
#endif
    }
}

void Init() {
    Uart.Init(57600);
#ifndef TESTING
    Uart.Printf("Glove1 AHB=%u; APB1=%u; APB2=%u; Usb=%u\r", Clk.AHBFreqHz, Clk.APB1FreqHz, Clk.APB2FreqHz, Clk.UsbSdioFreqHz);

//    LedsInit();
    // Charging and powering
//    PinSetupIn(GPIOA, 9, pudPullDown);
//    PinSetupIn(GPIOB, 2, pudPullUp);

//    AccInit();
//    VibroInit();
    //IR.Init();

    // Application init
//    App.Init();
#else
    Uart.Printf("Glove tester\r");
    PinSetupOut(GPIOA, 15, omPushPull);
    PinSet(GPIOA, 15);
    chThdSleepMilliseconds(450);
    Acc[0].SetPortAndPins(GPIOA, 1, 3, 4);
#endif
}
