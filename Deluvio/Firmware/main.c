/* 
 * File:   main.c
 * Author: Kreyl Laurelindo
 *
 * Created on 29-11-2010 ã., 19:48
 */

#include "main.h"
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "lcd110x.h"
#include "sensors.h"
#include "delay_util.h"
#include "beep.h"
#include "time.h"
#include "menu.h"

struct pump_t Pumps[PUMP_COUNT];
bool IsPumping;
struct {
    bool MustSleep;
    uint16_t Timer;
} ESleep;

int main(void) {
    GeneralInit();

//    LCD_PrintString_P(0, 2, PSTR("Ostranna BBS"), false);
//    _delay_ms(1800);

    sei();

    SetState(StIdle);
    
    while(1) {
        if(POWER_OK()) {
            Task_Sensors();
            Task_Beep();
            Task_Menu();
            Task_Pump();
            Task_Sleep();
            wdt_reset();
        }
        else {  // power failure, enter sleep mode
            LCD_Shutdown();
            PumpOffAll();
            WATER_SNS_OFF();
            // Enter sleep
            set_sleep_mode(SLEEP_MODE_PWR_SAVE);    // Left timer2 enabled
            sleep_enable();
            wdt_disable();  // To save energy
            // Circle here until power comes
            do {
                sleep_cpu();
            } while(!POWER_OK());
            // Power restored
            wdt_enable(WDTO_2S);
            LCD_Init();
            SetState(StIdle);
            WATER_SNS_ON();
            CheckWater();
        }
    } // while(1)
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    QTouchInit();
    DelayInit();
    BeepInit();
    LCD_Init();
    TimeInit();
    // Battery sensor init
    PWROK_DDR &= ~(1<<PWROK_P);
    // Water sensor
    WATER_SNS_DDR &= ~(1<<WATER_SNS_P);
    WATER_SNS_ON();
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

FORCE_INLINE void Task_Sleep(void) {
//#define LCD_SHUTDOWN
    if(IsPumping || (EState != StIdle)) return;     // Get out if in menu
    if(!DelayElapsed(&ESleep.Timer, 2000)) return;  // Do not sleep immediately
    // Prepare to sleep
    ESleep.MustSleep = true;
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);    // Left timer2 enabled
    //cli();                                  // DEBUG: will sleep forever
    //set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // DEBUG: will sleep forever
    sleep_enable();
    wdt_disable();
#ifdef LCD_SHUTDOWN
    LCD_Shutdown();
#else
    bool Blink = false;
#endif
    while(ESleep.MustSleep) {    // Will get out of cycle either in case of pumping, or in case of keypress
        sleep_cpu();
        // Check if key pressed
        current_time_ms_touch += 1000;  // As IRQ triggers every second
        if(QTouchActivityDetected()) {
            ESleep.MustSleep = false;
            DelayReset(&ESleep.Timer);
        }
#ifndef LCD_SHUTDOWN
        // Display blinking ':' to show time is passing
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            LCD_GotoXYstr(PRINT_TIME_X+2, PRINT_TIME_Y);
            if(Blink) LCD_DrawChar(' ', false);
            else LCD_DrawChar(':', false);
        }
        Blink = !Blink;
#endif
    } // While must sleep
    wdt_enable(WDTO_2S);
#ifdef LCD_SHUTDOWN
    LCD_Init();
#endif
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
// Automatically switches pumps on and off. Disabled in any menu activity.
FORCE_INLINE void Task_Pump(void) {
    if(EState != StIdle) return;
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

// Beep if no water
void CheckWater(void) {
    if(EState == StIdle)
        if(POWER_OK())
            if(WATER_EMPTY()) {
                Beep(BEEP_LONG);
                ESleep.MustSleep = false;   // Get out of sleep cycle in Sleep_Task
            }
}

// ============================= Events ========================================
// Time events: recalled from interrupt. Do it quick!
FORCE_INLINE void EVENT_NewMinute(void) {
    if(EState == StIdle)
        if(POWER_OK())
            LCD_PrintTime(PRINT_TIME_X, PRINT_TIME_Y, false, false, false);
}
FORCE_INLINE void EVENT_NewHour(void) {
    if((EState != StIdle) || !Time.IsSetCorrectly) return;
    CheckWater();
    // Iterate pumps, switch on if needed
    for(uint8_t i=0; i<PUMP_COUNT; i++) if(Pumps[i].Enabled) {
        // Decrease PeriodLeft counter for hours mode
        if(Pumps[i].DelayMode == ModeHours) if(Pumps[i].PeriodLeft > 0) Pumps[i].PeriodLeft--;
        // Check if time to wake-up and pump
        if((Pumps[i].PeriodLeft == 0) && ((Pumps[i].DelayMode == ModeHours) || (Pumps[i].StartHour == Time.Hour))) {
            Pumps[i].State = PmpMustPump;
            Pumps[i].PeriodLeft = Pumps[i].Period;
            ESleep.MustSleep = false;   // Get out of sleep cycle in Sleep_Task
        }
    }
}
FORCE_INLINE void EVENT_NewDay(void) {
    if((EState != StIdle) || !Time.IsSetCorrectly) return;
    // Decrease PeriodLeft counter for days mode
    for(uint8_t i=0; i<PUMP_COUNT; i++) if(Pumps[i].Enabled)
        if(Pumps[i].DelayMode == ModeDays) if(Pumps[i].PeriodLeft > 0) Pumps[i].PeriodLeft--;
}
