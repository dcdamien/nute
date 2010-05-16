/*
 * File:   main.c of CallingStone of Tirusse project
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
#include "cc1101.h"
#include "time_utils.h"

int main(void) {
    GeneralInit();

    uint16_t Timer;
    TimerResetDelay(&Timer);
    sei();

    DDRA = 0xFF;    //DEBUG

    // ******** Main cycle *********
    while (1){
        wdt_reset();    // Reset watchdog
        if(TimerDelayElapsed(&Timer, 100)){
            PORTC ^= (1<<PC6);
        }
        CC_Task();
        Packet_TASK(); 
    } // while 1
}

FORCE_INLINE void GeneralInit(void){
    wdt_enable(WDTO_2S);

    LED_DDR |= (1<<LED_P);

    CC.Address = 4; //Never changes in CC itself

    TimerInit();
    CC_Init();
    //CC_SET_CHANNEL(1);
}

void Packet_TASK(void){
    if (!CC.NewPacketReceived) return;  // Nothing to do here

    if (CC.RX_Pkt->CommandID == PKT_ID_CALL){

    }
    CC.NewPacketReceived = false;
}

// ============================== Interrupts ===================================
