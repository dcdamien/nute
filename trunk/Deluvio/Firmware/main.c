/* 
 * File:   main.c
 * Author: Kreyl Laurelindo
 *
 * Created on 29-11-2010 ã., 19:48
 */

#include "main.h"
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "lcd110x.h"
#include "sensors.h"
#include "delay_util.h"
#include "beep.h"
#include "time.h"
#include "menu.h"

struct pump_t Pumps[PUMP_COUNT];
bool MaySleep, IsPumping;

int main(void) {
    GeneralInit();
    
    sei();

    SetState(StIdle);
    
    while(1) {
        Task_Sensors();
        Task_Beep();
        Task_Menu();
        Task_Pump();
    } // while(1)
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);

    QTouchInit();
    DelayInit();
    BeepInit();
    LCD_Init();
    TimeInit();
    // Pumps
    PUMP_DDR |= (1<<PUMP1P)|(1<<PUMP2P)|(1<<PUMP3P)|(1<<PUMP4P);
    for(uint8_t i=0; i<PUMP_COUNT; i++) {
        Pumps[i].Period = 1;
        Pumps[i].PeriodLeft = 1;
        Pumps[i].Duration = 1;
    }
    // DEBUG
    Pumps[0].Enabled = true;
    Pumps[0].Duration = 300;
    Pumps[0].Period = 1;
    Pumps[0].PeriodLeft = 1;
    Pumps[0].DelayMode = ModeHours;
}

void Task_Sleep(void) {
    
}

// Pumps
void PumpOn(uint8_t APump) {
    IsPumping = true;
    switch (APump) {
        case 1: PUMP_PORT |= (1<<PUMP1P); break;
        case 2: PUMP_PORT |= (1<<PUMP2P); break;
        case 3: PUMP_PORT |= (1<<PUMP3P); break;
        case 4: PUMP_PORT |= (1<<PUMP4P); break;
        default:
            IsPumping = false;
            break;
    }
}
void PumpOffAll(void) {
    IsPumping = false;
    PUMP_PORT &= ~((1<<PUMP1P)|(1<<PUMP2P)|(1<<PUMP3P)|(1<<PUMP4P));
}

FORCE_INLINE void Task_Pump(void) {
    for(uint8_t i=0; i<PUMP_COUNT; i++) {
        // Beep if time to pump
        if(Pumps[i].Enabled && (Pumps[i].State == PmpMustPump) && !IsPumping) {
            Pumps[i].State = PmpBeeping;
            IsPumping = true;
            Beep(BEEP_LONG);
            DelayReset(&Pumps[i].Counter);
        }
        // Switch on needed pump
        if(Pumps[i].State == PmpBeeping) {
            if(DelayElapsed(&Pumps[i].Counter, 999)) {  // Hope beep was finished now
                Pumps[i].State = PmpPumping;
                // Reset second counter
                Time.SecondPassed = false;
                Pumps[i].Counter = 0;
                PumpOn(i+1);
            }
        }
        // Check if time to shutdown
        if(Pumps[i].State == PmpPumping) {
            if(Time.SecondPassed) {
                Time.SecondPassed = false;
                Pumps[i].Counter++;
                if(Pumps[i].Counter >= Pumps[i].Duration) {
                    PumpOffAll();
                    Pumps[i].State = PmpIdle;
                }
            } // if(Time.SecondPassed)
        } // if PmpPumping
    } // for
}

// ============================= Events ========================================
// Time events
FORCE_INLINE void EVENT_NewSecond(void) {   // Check every second to work-around problem with unknown sequence of event triggering
}
FORCE_INLINE void EVENT_NewMinute(void) {
    if(EState == StIdle) LCD_PrintTime(PRINT_TIME_X, PRINT_TIME_Y, false, false, false);
}
FORCE_INLINE void EVENT_NewHour(void) {
    if((EState != StIdle) || !Time.IsSetCorrectly) return;
    for(uint8_t i=0; i<PUMP_COUNT; i++) if(Pumps[i].Enabled) {
        // Decrease PeriodLeft counter for hours mode
        if(Pumps[i].DelayMode == ModeHours) if(Pumps[i].PeriodLeft > 0) Pumps[i].PeriodLeft--;
        // Check if time to wake-up and pump
        if((Pumps[i].PeriodLeft == 0) && ((Pumps[i].DelayMode == ModeHours) || (Pumps[i].StartHour == Time.Hour))) {
            Pumps[i].State = PmpMustPump;
            Pumps[i].PeriodLeft = Pumps[i].Period;
            MaySleep = false;
        }
    }
}
FORCE_INLINE void EVENT_NewDay(void) {
    if((EState != StIdle) || !Time.IsSetCorrectly) return;
    // Decrease PeriodLeft counter for days mode
    for(uint8_t i=0; i<PUMP_COUNT; i++) if(Pumps[i].Enabled)
        if(Pumps[i].DelayMode == ModeDays) if(Pumps[i].PeriodLeft > 0) Pumps[i].PeriodLeft--;
}
