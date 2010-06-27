/* 
 * File:   calma3c.c
 * Author: Laurelindo
 *
 * Created on 20 2009 Рі., 0:16
 */
#include <avr/io.h>
#include <inttypes.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "transmitter.h"
#include "time_utils.h"
#include "../cc_common/common.h"
#include "../cc_common/cc2500.h"

#include <util/delay.h>

// ============================== General ======================================
int main(void) {
    GeneralInit();

    sei(); 
    while (1) {
        wdt_reset();    // Reset watchdog
        CC_Task();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    // Shutdown all unneeded
    PRR = (1<<PRTWI)|(1<<PRSPI)|(1<<PRADC);

    // Setup timer
    TimerInit();

    // Light
    LED_DDR  |= (1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P);
    LED_PORT &= ~((1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P));
    LED_PWR_DDR |= (1<<LED_PWR_P);
    LED_PWR_ON();

    TCCR0A = (1<<WGM01)|(1<<WGM00);
    TCCR0B = (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);
    TCCR2A = (1<<WGM21)|(1<<WGM20);
    TCCR2B = (0<<WGM22)|(0<<CS22)|(0<<CS21)|(1<<CS20);
    LED_GREEN_ENABLE();
    OCR0B = 180;

    // CC init
    CC_Init();
    CC_SetAddress(4);   // Never changes in CC itself
}

// ============================== Tasks ========================================
void CC_Task (void){
    // Do with CC what needed
    CC_GET_STATE();
    switch (CC.State) {
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;

        case CC_STB_IDLE:
            // Transmit at once if IDLE
            // Prepare Cale packet
            CC.TX_Pkt.Address = 0;      // Broadcast
            CC.TX_Pkt.PacketID++;       // Increase packet ID, to avoid repeative treatment
            CC.TX_Pkt.CommandID = PKT_ID0_CALE;
            CC.TX_Pkt.Data[0]   = PKT_ID1_CALE;
            // Transmit black color if "shutdown" color is set
            CC.TX_Pkt.Data[1] = 0;
            CC.TX_Pkt.Data[2] = 180;
            CC.TX_Pkt.Data[3] = 0;

            CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
            CC_ENTER_TX();
            break;

        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}

