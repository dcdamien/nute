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

    DDRC |= (1<<PC6);
    #define LED_ON()    PORTC

    // ******** Main cycle *********
    sei();
    while (1){
        wdt_reset();    // Reset watchdog
        if(TimerDelayElapsed(&Timer, 100)){
            PORTC ^= (1<<PC6);
        }
        //CC_Task();
        //Packet_TASK();
    } // while 1
}

FORCE_INLINE void GeneralInit(void){
    wdt_enable(WDTO_2S);

    LED_DDR |= (1<<LED_P);

    CC.Address = 4;     // Never changes as no need in it

    TimerInit();
    CC_Init();

    sei();
}

void Packet_TASK(void){
    if (!CC.NewPacketReceived) return;

    switch (CC.RX_Pkt->CommandID){
        case PKT_ID_CALL:
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
            } // Atomic
            break; // ID = CALL

        default:
            break;
    }// switch
    CC.NewPacketReceived = false;
}

// ============================== Interrupts ===================================
// Cycle end interrupt 
ISR(TIMER1_CAPT_vect){ // Means overflow IRQ
    // Do things needed at end of RX cycle
}
