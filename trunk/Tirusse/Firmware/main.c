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

#include "main.h"
#include "../cc_common/cc1101.h"
#include "time_utils.h"

struct {
    uint16_t Timer;
} ELED;
struct {
    bool Detected;
    bool IsHere;
    uint16_t Timer;
} CStone;
struct {
    uint16_t Timer;
    bool JustEnteredRX;
    uint8_t Channel;
} CC_Srv;

// =============================== General =====================================
int main(void) {
    GeneralInit();
    sei();

    DDRA = 0xFF;    //DEBUG

    // ******** Main cycle *********
    while (1){
        wdt_reset();    // Reset watchdog
        CC_Task();
        Stone_Task();
        LED_Task();
    } // while 1
}

FORCE_INLINE void GeneralInit(void){
    wdt_enable(WDTO_2S);
    LED_DDR |= (1<<LED_P);
    TimerInit();

    // LED init

    // Stone init
    CStone.Detected = false;
    CStone.IsHere = false;
    TimerResetDelay(&CStone.Timer);

    // CC init
    CC_Srv.Channel = CC_CHANNEL_START;
    CC_Srv.JustEnteredRX = false;
    TimerResetDelay(&CC_Srv.Timer);
    CC_Init();
    CC_SetAddress(4);   //Never changes in CC itself
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

}

void CC_Task (void){
    // Handle packet if received
    if (CC.NewPacketReceived) {
        CC.NewPacketReceived = false;
        EVENT_NewPacket();
    }

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
            if (TimerDelayElapsed(&CC_Srv.Timer, CC_RX_OFF_DELAY)) {
                CC_SetChannel(CC_Srv.Channel);
                CC_ENTER_RX();
                CC_Srv.JustEnteredRX = true;
                // Calculate next channel
                CC_Srv.Channel++;
                if (CC_Srv.Channel > CC_CHANNEL_END) CC_Srv.Channel = CC_CHANNEL_START;
            }
            break;
        
        case CC_STB_RX:
            // Reset timer if just entered RX
            if (CC_Srv.JustEnteredRX) {
                CC_Srv.JustEnteredRX = false;
                TimerResetDelay(&CC_Srv.Timer);
                PORTA |= (1<<PA2); // DEBUG
            }
            else {
                // Check if CC_RX_ON_DELAY delay elapsed
                if (TimerDelayElapsed(&CC_Srv.Timer, CC_RX_ON_DELAY)) { // Time to switch off
                    CC_ENTER_IDLE();
                    PORTA &= ~(1<<PA2); // DEBUG
                }// if timer
            }// if not RX
            break;
            
        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}


// =============================== Events ======================================
void EVENT_Detected(void) {
    LED_ON();
}
void EVENT_Hide(void) {
    LED_OFF();
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
