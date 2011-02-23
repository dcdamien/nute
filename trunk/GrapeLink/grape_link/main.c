/* 
 * File:   main.c
 * Author: Kreyl Laurelindo
 *
 * Created on 21 Февраль 2011 г., 22:23
 */

#include <avr/io.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "main.h"
#include "delay_util.h"
#include "battery.h"
#include "common.h"
#include "cc1101.h"
#include "leds.h"

// ============================= Types =========================================
enum Mood_t {Nobody, Neutral, Bad, VeryBad};
struct {
    uint8_t CycleCounter;
    bool CC_IsSleeping;
    enum Mood_t SelfMood, FarMood;

} Grape;

// ============================== General ======================================
int main(void) {
    GeneralInit();
    DDRB |= 1<< PB0;
    DDRC |= 1<<PC6;

    //Grape.FarMood = VeryBad;
    sei();
    while (1) {
        wdt_reset();    // Reset watchdog
        //CC_Task();
//        Battery_Task();
        LEDs_Task();
        _delay_ms(1);
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    //wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator

    CC_Init();
    LedsInit();
    DelayInit();

    // Setup Timer1: cycle timings
/*
    TCNT1 = 0;
    TCCR1A = 0;
    OCR1A = ((uint16_t)Corma.Addr) * PKT_DURATION;  // TX start
    ICR1 = SUBCYCLE_DURATION;                       // TX + RX/Sleep duration
    TIMSK |= (1<<OCIE1A)|(1<<TICIE1);
    CYC_TIMER_START();
*/

    // Battery
    //BatteryInit();
}

// ============================== Tasks ========================================
void CC_Task (void) {
    // Handle packet if received
    if (CC.NewPacketReceived) {
        CC.NewPacketReceived = false;
        EVENT_NewPacket();
    }

    // Check if sleeping

    // Do with CC what needed
    CC_GET_STATE();
    switch (CC.State){
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;

        case CC_STB_RX:
            break;

        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}

// Handle rise & fade
void LEDs_Task(void) {
    if (!DelayElapsed(&ELeds.Timer, LED_STEP_DELAY)) return;
    //if (!DelayElapsed(&ELeds.Timer, 100)) return;
    if      (ELeds.CurrentPWM < ELeds.DesiredPWM) ELeds.CurrentPWM++;
    else if (ELeds.CurrentPWM > ELeds.DesiredPWM) ELeds.CurrentPWM--;
    else {  // Current = desired
        if (ELeds.DesiredPWM == 0) {    // Bottom of fade out, switch to next LED
            PWMStop();
            LedSwitch(Off);             // Turn off current LED
            ChooseNextLED();
            ELeds.DesiredPWM = PWM_MAX; 
            PWMStart();
        } // if bottom
        else ELeds.DesiredPWM = 0;
    } // if current == desired
    PWMSet(ELeds.CurrentPWM);
}

void ChooseNextLED(void) {
    switch (Grape.FarMood) {
        case Neutral:   // Greens only
            if (ELeds.LedColor != Green) ELeds.LedColor = Green;
            ELeds.LedGreenNumber++;
            if (ELeds.LedGreenNumber >= GREEN_COUNT) ELeds.LedGreenNumber = 0;
            break;

        case Bad:   // Greens and Reds
            if (ELeds.LedColor == Red) {    // Set to green
                ELeds.LedColor = Green;
                ELeds.LedGreenNumber++;
                if (ELeds.LedGreenNumber >= GREEN_COUNT) ELeds.LedGreenNumber = 0;
            }
            else {  // Set to red
                ELeds.LedColor = Red;
                ELeds.LedRedNumber++;
                if (ELeds.LedRedNumber >= RED_COUNT) ELeds.LedRedNumber = 0;
            }
            break;

        case VeryBad:   // Reds only
            if (ELeds.LedColor != Red) ELeds.LedColor = Red;
            ELeds.LedRedNumber++;
            if (ELeds.LedRedNumber >= RED_COUNT) ELeds.LedRedNumber = 0;
            break;

        default:
            break;
    } // Switch
}

// ============================== Events =======================================
FORCE_INLINE void EVENT_NewPacket(void) {
    if (CC.RX_Pkt.CmdID == PKT_ID_CALL) {
    } // if PKT_ID_Call
}
void EVENT_ADCMeasureCompleted(void) {
    // Choose mode of LED
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (Battery.ADCValue <= BAT_U_DISCHARGED) {
        }
    }
}

// ============================ Interrupts =====================================
// Transmit interrupt
ISR(TIMER1_COMPA_vect) {
    PORTA &= ~(1<<PA4);
    PORTA |= (1<<PA3); // DEBUG
    CYC_TIMER_STOP();
    // Prepare packet & transmit it
    CC.TX_Pkt.CmdID = PKT_ID_CALL;
    CC_WriteTX (&CC.TX_PktArray[0], PKT_LNG); // Write bytes to FIFO
    CC_ENTER_TX();
    // Wait for packet to transmit completely
    while (!CC_GDO0_IS_HI());   // After this, SYNC word is transmitted
    while (CC_GDO0_IS_HI());    // After this, packet is transmitted
//    if (Corma.CycleCounter == 0) CC_EnterRX();  // Enter RX after TX
    CYC_TIMER_START();
    PORTA &= ~(1<<PA3); // DEBUG
}

// SubCycle end interrupt
ISR(TIMER1_CAPT_vect) { // Means overflow IRQ
    _delay_us(500);
    // Handle cycle counter
/*
    if (++Corma.CycleCounter >= CYCLE_COUNT) {  // Zero cycle begins
        Corma.CycleCounter = 0;
        // Flinch!
        MotorSetCount (Corma.OthersCounter);
        Corma.OthersCounter = 0;
        // Enter RX-before-TX
        CC_EnterRX();
    }
    else CC_ENTER_IDLE();   // Non-zero cycle
*/
    PORTA &= ~(1<<PA1);// DEBUG
}


