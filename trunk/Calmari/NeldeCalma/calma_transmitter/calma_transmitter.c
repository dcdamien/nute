/* 
 * File:   calma3c.c
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */
#include <avr/io.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include "calma_transmitter.h"
#include "time_utils.h"
#include "../cc_common/common.h"
#include "../cc_common/cc2500.h"

//#define DEBUG_UART
#ifdef DEBUG_UART
#include "uart_soft.h"
#endif

// ============================== General ======================================
int main(void) {
    GeneralInit();

    #ifdef DEBUG_UART
    UARTInit();
    UARTSendString_P(PSTR("Calma is here\r"));
    #endif

    SetColor (10, 150, 50);

    sei(); 
    while (1) {
        wdt_reset();    // Reset watchdog
        CC_Task();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    // Setup timer
    TimerInit();    // Time counter

    // Light
    LED_DDR  |=   (1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P);
    LED_PORT &= ~((1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P));
    TCCR0A = (1<<WGM01)|(1<<WGM00);
    TCCR0B = (0<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00);  // 1 MHz/8 = 125 kHz of timer infut freq. 125 kHz/255 = 490 Hz of PWM freq.
    TCCR2A = (1<<WGM21)|(1<<WGM20);
    TCCR2B = (0<<WGM22)|(0<<CS22)|(1<<CS21)|(0<<CS20);

    LED_RED_ENABLE();
    LED_GREEN_ENABLE();
    LED_BLUE_ENABLE();

    // CC init
    CC_Init();
    CC_SetAddress(4);   //Never changes in CC itself
}

FORCE_INLINE void SetColor (uint8_t ARed, uint8_t AGreen, uint8_t ABlue) {
    OCR0A = ARed;
    OCR0B = AGreen;
    OCR2B = ABlue;
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
   
            CC.TX_Pkt.Data[1] = OCR0A;
            CC.TX_Pkt.Data[2] = OCR0B;
            CC.TX_Pkt.Data[3] = OCR2B;

            CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
            CC_ENTER_TX();
            break;

        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}
