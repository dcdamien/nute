/*
 * File:   main.c of Tirusse of Tirusse project
 * Author: Kreyl Laurelindo
 *
 * Created on 2010.04.07
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <util/atomic.h>

#include "main.h"
#include "../cc_common/cc1101.h"
#include "time_utils.h"
#include "battery.h"
#include "common.h"

// ================================= Types =====================================
struct {
    uint16_t Timer;
    uint8_t PWM, PWMDesired;
} ELED;
struct {
    bool Detected;
    bool IsHere;
    uint16_t Timer;
} CStone;
struct {
    uint16_t Timer;
    bool JustEnteredRX;
    bool DeepSleep;
    uint8_t Channel;
} CC_Srv;

// =============================== General =====================================
int main(void) {
    GeneralInit();
    sei();
//    DDRA = 0xFF;    //DEBUG

    // ******** Main cycle *********
    while (1){
        wdt_reset();    // Reset watchdog
        CC_Task();
        Stone_Task();
        LED_Task();
        Battery_Task();
    } // while 1
}

FORCE_INLINE void GeneralInit(void){
    wdt_enable(WDTO_2S);
    LED_DDR |= (1<<LED_P);
    ACSR = 1<<ACD;  // Disable analog comparator
    TimerInit();

    // LED init
    PWM_Setup();
    ELED.PWMDesired = 0;
    ELED.PWM = PWM_MAX; // Light-up at power-on
    TimerResetDelay(&ELED.Timer);

    // Stone init
    CStone.Detected = false;
    CStone.IsHere = false;
    TimerResetDelay(&CStone.Timer);

    // CC init
    CC_Srv.Channel = CC_CHANNEL_START;
    CC_Srv.JustEnteredRX = false;
    CC_Srv.DeepSleep = false;
    TimerResetDelay(&CC_Srv.Timer);
    CC_Init();
    CC_SetAddress(4);   //Never changes in CC itself

    // Battery
    BatteryInit();
}

// ============================= PWM functions =================================
FORCE_INLINE void PWM_Setup(void) {
    // Fast PWM, 10 bit, no prescaling, OC1A disconnected, OC1B inverted
    TCCR1A = (0<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(1<<COM1B0)|(1<<WGM11)|(1<<WGM10);
    TIMER1_ENABLE();
    DDRD  |= (1<<PD4);
    PORTD |= (1<<PD4);
}

FORCE_INLINE void PWM_Set(uint8_t APWM) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1B = APWM;
    }
}

bool MayChangePWM(void) {
    if (ELED.PWM <= PWMStepOver1) {
        return TimerDelayElapsed(&ELED.Timer, PWMDelayLong);        // Low speed
    }
    else if (ELED.PWM > PWMStepOver1 && ELED.PWM <= PWMStepOver2) {
        return TimerDelayElapsed(&ELED.Timer, PWMDelayMid);         // Mid-speed
    }
    else if (ELED.PWM > PWMStepOver2) {
        return TimerDelayElapsed(&ELED.Timer, PWMDelayFast);        // High-speed
    }
    return false;
}

// ================================ Tasks ======================================
void Stone_Task(void) {
    if (!TimerDelayElapsed(&CStone.Timer, DETECTOR_TIMEOUT)) return;
    // Here is only hide event. Detected event fires within packet handler.
    if (CStone.IsHere && !CStone.Detected) {
        CStone.IsHere = false;
        EVENT_Hide();
    }
    CStone.Detected = false;         // reset detecor
}

void LED_Task(void) {
    // Disable LED during charging
    if (BAT_IS_CHARGING()) ELED.PWMDesired = 0;

    if (ELED.PWM != ELED.PWMDesired) {
        if (ELED.PWMDesired < ELED.PWM) {   // Lower PWM
            if (MayChangePWM()) {
                ELED.PWM--;
                PWM_Set(ELED.PWM);
            }
            // Workaround hardware PWM bug: LED does not switches off totally
            if (ELED.PWM == 0) TIMER1_DISABLE();
        }
        else {
            if (ELED.PWM == 0) TIMER1_ENABLE();
            if (MayChangePWM()) {
                ELED.PWM++;
                PWM_Set(ELED.PWM);
            } // if may change
        } // Fade or brighten
    } // if not desired
}

void CC_Task (void){
    // Handle packet if received
    if (CC.NewPacketReceived) {
        CC.NewPacketReceived = false;
        EVENT_NewPacket();
    }

    if (CC_Srv.DeepSleep) {
        if (TimerDelayElapsed(&CC_Srv.Timer, CC_RX_OFF_DELAY)) CC_Srv.DeepSleep = false;
        else return;
    }
    //PORTA |= (1<<PA2); // DEBUG
    // Do with CC what needed
    CC_GET_STATE();
    switch (CC.State){
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;

        case CC_STB_IDLE:
            // Set needed channel and enter RX if time has come
            CC_SetChannel(CC_Srv.Channel);
            CC_ENTER_RX();
            CC_Srv.JustEnteredRX = true;
            // Calculate next channel
            CC_Srv.Channel++;
            if (CC_Srv.Channel > CC_CHANNEL_END) CC_Srv.Channel = CC_CHANNEL_START;
            break;
        
        case CC_STB_RX:
            // Reset timer if just entered RX
            if (CC_Srv.JustEnteredRX) {
                CC_Srv.JustEnteredRX = false;
                TimerResetDelay(&CC_Srv.Timer);
            }
            else {
                // Check if CC_RX_ON_DELAY delay elapsed
                if (TimerDelayElapsed(&CC_Srv.Timer, CC_RX_ON_DELAY)) { // Time to switch off
                    CC_ENTER_IDLE();
                    CC_POWERDOWN();
                    CC_Srv.DeepSleep = true;
                    //PORTA &= ~(1<<PA2); // DEBUG
                }// if timer
            }// if not RX
            break;
            
        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}

// =============================== Events ======================================
void EVENT_Detected(void) {
    ELED.PWMDesired = PWM_MAX;
}
void EVENT_Hide(void) {
    ELED.PWMDesired = 0;
}

void EVENT_NewPacket(void) {
    if (CC.RX_Pkt->CommandID == PKT_ID_CALL) {
        CStone.Detected = true;
        // Send event if needed
        if (!CStone.IsHere) {
            CStone.IsHere = true;
            EVENT_Detected();
        }
    } // if PKT_ID_CALL
}
