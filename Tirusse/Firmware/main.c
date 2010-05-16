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

uint16_t CC_Timer;

struct {
    uint16_t Timer;
    bool IsOn;
} ELED;

int main(void) {
    GeneralInit();
    sei();

    DDRA = 0xFF;    //DEBUG

    // ******** Main cycle *********
    while (1){
        wdt_reset();    // Reset watchdog
        CC_Task();
        Packet_TASK();
        LED_Task();
    } // while 1
}

void LED_Task(void){
    if (TimerDelayElapsed(&ELED.Timer, 100)){
        if (ELED.IsOn == false) LED_OFF();
        ELED.IsOn = false;  // reset LED
    }
}

FORCE_INLINE void GeneralInit(void){
    wdt_enable(WDTO_2S);

    LED_DDR |= (1<<LED_P);

    CC.Address = 4; //Never changes in CC itself

    TimerInit();

    // LED init
    TimerResetDelay(&ELED.Timer);
    ELED.IsOn = false;

    // CC init
    TimerResetDelay(&CC_Timer);
    CC_Init();
    CC_SetChannel(1);
}

void Packet_TASK(void){
    if (!CC.NewPacketReceived) return;  // Nothing to do here

    if (CC.RX_Pkt->CommandID == PKT_ID_CALL){
        LED_ON();
        ELED.IsOn = true;
    }
    CC.NewPacketReceived = false;
}

// ================================= CC Task ===================================
void CC_Task (void){
    CC_GET_STATE();
    switch (CC.State){
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;
        case CC_STB_IDLE:
            //if ((!CC.NewPacketReceived) && TimerDelayElapsed(&CC_Timer, CC_RX_PERIOD))
            if (!CC.NewPacketReceived)
                CC_ENTER_RX();
            break;
        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}

