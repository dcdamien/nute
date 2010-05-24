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
#include <avr/eeprom.h>

#include "main.h"
#include "../cc_common/cc1101.h"
#include "time_utils.h"

uint16_t CC_Timer;

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
    } // while 1
}

FORCE_INLINE void GeneralInit(void){
    wdt_enable(WDTO_2S);
    LED_DDR |= (1<<LED_P);

    TimerInit();

    TimerResetDelay(&CC_Timer);
    CC.Address = eeprom_read_byte(EE_ADDRESS); //Never changes in CC itself
    CC_Init();
    CC_SetChannel(CC_CHANNEL_START);    // DEBUG
    //CC_SetChannel(CC_CHANNEL_START + CC.Address);    // DEBUG
}

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
            PORTA &= ~(1<<PA1); // DEBUG
            // DEBUG: do it not continuously
            //if (!TimerDelayElapsed(&CC_Timer, 200)) return;

            // Transmit at once if IDLE
            // Prepare CALL packet
            CC.TX_Pkt->Address = 0;     // Broadcast
            CC.TX_Pkt->PacketID = 0;    // Current packet ID, to avoid repeative treatment
            CC.TX_Pkt->CommandID = 0xCA;// }
            CC.TX_Pkt->Data[0] = 0x11;  // } CALL packet

            CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
            CC_ENTER_TX();


            PORTA |= (1<<PA1); // DEBUG
            break;
        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}

// ============================== Interrupts ===================================
