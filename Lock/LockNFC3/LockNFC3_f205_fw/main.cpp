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
#include "kl_sd.h"
#include "sound.h"
#include "cmd_uart.h"
#include "ff.h"
#include "MassStorage.h"
#include "evt_mask.h"
#include "main.h"
#include "led_rgb.h"
#include "Sequences.h"
#include "pn.h"
#include "keys.h"

App_t App;
Sns_t Sns = {GPIOA, 0};
SndList_t SndList;

LedRgbBlinker_t LedService = { {GPIOB, 10}, {GPIOB, 12}, {GPIOB, 11} };

// =============================== Main ========================================
int main() {
    // ==== Setup clock ====
    Clk.UpdateFreqValues();
    uint8_t ClkResult = FAILURE;
    Clk.SetupFlashLatency(12);  // Setup Flash Latency for clock in MHz
    // 12 MHz/6 = 2; 2*192 = 384; 384/8 = 48 (preAHB divider); 384/8 = 48 (USB clock)
    Clk.SetupPLLDividers(6, 192, pllSysDiv8, 8);
    // 48/4 = 12 MHz core clock. APB1 & APB2 clock derive on AHB clock
    Clk.SetupBusDividers(ahbDiv4, apbDiv1, apbDiv1);
    if((ClkResult = Clk.SwitchToPLL()) == 0) Clk.HSIDisable();
    Clk.UpdateFreqValues();

    // ==== Init OS ====
    halInit();
    chSysInit();

    // ==== Init Hard & Soft ====
    App.PThd = chThdSelf();
    Uart.Init(115200);
    Uart.Printf("\rLockNFC3 F205   AHB freq=%uMHz", Clk.AHBFreqHz/1000000);
    LedService.Init();
    LedService.StartSequence(lsqBlinkGreenX2);

    App.IDStore.Init();
    Keys.Init();

    Pn.Init();

//    SD.Init();

    // USB related
//    PinSetupIn(PWR_EXTERNAL_GPIO, PWR_EXTERNAL_PIN, pudPullDown);
//    MassStorage.Init();

//    Sound.Init();
//    Sound.SetVolume(255);
//    Sound.RegisterAppThd(chThdSelf());
//    Sound.Play("alive.wav");

    // Sensor
//    Sns.Init();

//    ReadConfig();

    // Report problem with clock if any
    if(ClkResult) Uart.Printf("Clock failure\r");

    // ==== Main cycle ====
    App.ITask();

#if 0 // ==== USB connected/disconnected ====
        if(WasExternal and !ExternalPwrOn()) {
            WasExternal = false;
            Usb.Shutdown();
            MassStorage.Reset();
            chSysLock();
            Clk.SetFreq12Mhz();
            Clk.InitSysTick();
            chSysUnlock();
            Uart.Printf("\rUsb Off");
        }
        else if(!WasExternal and ExternalPwrOn()) {
            WasExternal = true;
            chSysLock();
            Clk.SetFreq48Mhz();
            Clk.InitSysTick();
            chSysUnlock();
            Usb.Init();
            chThdSleepMilliseconds(540);
            Usb.Connect();
            Uart.Printf("\rUsb On");
        }
#endif

#if 0 // ==== Sensor ====
      if(Sns.CheckEdge() == Rising) {
          if(Sound.State == sndStopped) {
              Uart.Printf("\rDetected");
//              Sound.Play("alive.wav");
              // Generate random
              int32_t i;
              do {
                  uint32_t r = rand() % SndList.ProbSumm + 1; // [1; Probsumm]
                  //uint32_t r = Random(SndList.ProbSumm-1) + 1;
                  Uart.Printf("\rR=%u", r);
                  // Select phrase
                  for(i=0; i<SndList.Count-1; i++) { // do not check last phrase
                      if((r >= SndList.Phrases[i].ProbBottom) and (r <= SndList.Phrases[i].ProbTop)) break;
                  }
              } while(i == PreviousPhrase);
              PreviousPhrase = i;
              // Play phrase
              Sound.Play(SndList.Phrases[i].Filename);
          }
      }
#endif
}

__attribute__ ((__noreturn__))
void App_t::ITask() {
    while(true) {
        uint32_t EvtMsk = chEvtWaitAny(ALL_EVENTS);
        // ==== Card ====
        if(EvtMsk & EVTMASK_CARD_APPEARS) ProcessAppearance();

        // ==== Door ====
        if(EvtMsk & EVTMASK_DOOR_OPEN) {
            DoorState = dsOpen;
            // Set color
            // Say something
            Uart.Printf("\rDoor is open");
        }
        if(EvtMsk & EVTMASK_BAD_KEY) {
            Uart.Printf("\rBadKey");
        }

#if 1 // ==== Keys ====
        if(EvtMsk & EVTMSK_KEYS) {
            KeyEvtInfo_t EInfo;
            while(Keys.EvtBuf.Get(&EInfo) == OK) {
                if(EInfo.Type == kePress) {
                    switch(EInfo.KeyID[0]) {
                        case keyA:
                            if(State == asAddingAcc) {
                                if(IDStore.HasChanged) IDStore.Save();
                                LedService.StartSequence(lsqIdle);
                                State = asIdle;
                            }
                            else {
                                State = asAddingAcc;
                                LedService.StartSequence(lsqAddingAccIdle);
                                ResetStateTimer();
                            }
                            break;

                        case keyB:
                            if(State == asRemovingAcc) {
                                if(IDStore.HasChanged) IDStore.Save();
                                LedService.StartSequence(lsqIdle);
                                State = asIdle;
                            }
                            else {
                                State = asRemovingAcc;
                                LedService.StartSequence(lsqRemovingAccIdle);
                                ResetStateTimer();
                            }
                            break;

                        case keyC: break;
                    } // switch
                } // if keypress
                else if(EInfo.Type == keCombo and EInfo.KeyID[0] == keyA and EInfo.KeyID[1] == keyB) {
                    LedService.StartSequence(lsqEraseAll);
                    IDStore.EraseAll();
                    State = asIdle;
                }
            } // while
        } // if keys
#endif
    } // while true
}

void App_t::ProcessAppearance() {
    //LedService.StartSequence(lsqBlinkGreen);
    App.CurrentID.Print();
    switch(State) {
        case asIdle:
            if(DoorState == dsClosed) {
                IdKind_t IdKind = IDStore.Check(CurrentID);
                switch(IdKind) {
                    case ikAccess: SendEvt(EVTMASK_DOOR_OPEN); break;
                    case ikNone:   SendEvt(EVTMASK_BAD_KEY);   break;
                    case ikMaster: break;
                }
            }
            break;

        case asAddingAcc:
            LedService.StartSequence(lsqAddingAccNew);
            IDStore.AddAcc(CurrentID);
            ResetStateTimer();
            break;

        case asRemovingAcc:
            LedService.StartSequence(lsqRemovingAccNew);
            IDStore.RemoveAcc(CurrentID);
            ResetStateTimer();
            break;

        case asAddingMaster:
        case asRemovingMaster:
            break;
    } // switch
}

/*
char SndKey[45]="Sound";
uint8_t ReadConfig() {
    int32_t Probability;
    if(SD.iniReadInt32("Sound", "Count", "settings.ini", &SndList.Count) != OK) return FAILURE;
    Uart.Printf("\rCount: %d", SndList.Count);
    if (SndList.Count <= 0) return FAILURE;
    char *c;
    SndList.ProbSumm = 0;
    // Read sounds data
    for(int i=0; i<SndList.Count; i++) {
        // Build SndKey
        c = Convert::Int32ToStr(i+1, &SndKey[5]);   // first symbol after "Sound"
        strcpy(c, "Name");
//        Uart.Printf("\r%s", SndKey);
        // Read filename and probability
        char *S = nullptr;
        if(SD.iniReadString("Sound", SndKey, "settings.ini", &S) != OK) return FAILURE;
        strcpy(SndList.Phrases[i].Filename, S);
        strcpy(c, "Prob");
//        Uart.Printf("\r%s", SndKey);
        if(SD.iniReadInt32 ("Sound", SndKey, "settings.ini", &Probability) != OK) return FAILURE;
        // Calculate probability boundaries
        SndList.Phrases[i].ProbBottom = SndList.ProbSumm;
        SndList.ProbSumm += Probability;
        SndList.Phrases[i].ProbTop = SndList.ProbSumm;
    }
    for(int i=0; i<SndList.Count; i++) Uart.Printf("\r%u %S Bot=%u Top=%u", i, SndList.Phrases[i].Filename, SndList.Phrases[i].ProbBottom, SndList.Phrases[i].ProbTop);
    return OK;
}
*/
