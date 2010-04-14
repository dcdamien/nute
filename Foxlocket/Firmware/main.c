/*
 * File:   main.c of FoxLocket project
 * Author: Laurelindo
 *
 * Created on 2010.04.07
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/eeprom.h>

#include "main.h"
#include "uart_unit.h"
#include "cc1101.h"
#include "ledskeys.h"
#include "time_utils.h"

struct {
    uint8_t Arr[30];
    uint8_t Counter;
} RcvdAddreses;

int main(void) {
    LEDKeyInit();

    UARTInit();
    UARTSendString_P(PSTR("\rFoxlocket started\r"));

    // Get self address
    CC.Address = eeprom_read_byte(EE_ADDRESS);
    if (CC.Address == 0xFF) CC.Address = 0x01;
    //CC.Address = 1; //Never changes in CC itself

    TimerInit();
    CC_Init();

    // Setup Timer1
    TCNT1 = 0;
    OCR1A = ((uint16_t)CC.Address) << TIMER_MULTI;
    TCCR1A = 0;
    ICR1 = CYCLE_DURATION;
    TIMSK |= (1<<OCIE1A)|(1<<TICIE1);
    TIM1_START();

    sei();

    DDRA |= (1<<PA0)|(1<<PA1)|(1<<PA2);
    PORTA &= ~((1<<PA0)|(1<<PA1)|(1<<PA2));

    bool AlienIsCounted;

/*
    uint16_t FTimer;
    TimerResetDelay(&FTimer);
*/


    // Main cycle
    while (1){
        CC_Task();
        if (CC.NewPacketReceived){ // Handle packet
            uint8_t AlienAddr = CC.RX_Pkt->Data[1];
            switch (CC.RX_Pkt->CommandID){
                case PKT_ID_CALL:
                    // Setup our timer if alien address is lower, and do not otherwise
                    if (AlienAddr < CC.Address) {
                        ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
                            TIM1_STOP();
                            TCNT1 = (((uint16_t)AlienAddr) << TIMER_MULTI) + PKT_DURATION;
                            TIM1_START();
                        } // atomic
                    }
                    // Count this one if did not do it yet
                    AlienIsCounted = false;
                    for (uint8_t i=0; i<RcvdAddreses.Counter; i++){
                        if (RcvdAddreses.Arr[i] == AlienAddr){
                            AlienIsCounted = true;
                            //break;
                        }
                    }// for
                    if (!AlienIsCounted)
                        RcvdAddreses.Arr[RcvdAddreses.Counter++] = AlienAddr;
                    break; // ID = CALL

                default:
                    break;
            }// switch

            CC.NewPacketReceived = false;

        } // if (CC.NewPacketReceived)
    } // while 1
}


// ============================== Interrupts ===================================
ISR(TIMER1_COMPA_vect){
    PORTA |= (1<<PA0);
    // Prepare CALL packet
    CC.TX_Pkt->Address = 0;    // Recipient address
    CC.TX_Pkt->PacketID = 0;   // Current packet ID, to avoid repeative treatment
    CC.TX_Pkt->CommandID = 0xCA;
    CC.TX_Pkt->Data[0] = 0x11;
    CC.TX_Pkt->Data[1] = CC.Address;

    CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH);     // Write bytes to FIFO
    //    CC.NeededState = CC_TX;
    CC_ENTER_TX();
    PORTA &= ~(1<<PA0);
}

ISR(TIMER1_CAPT_vect){ // Means overflow IRQ
    if (RcvdAddreses.Counter > 0) LED_GREEN_ON();
    else LED_GREEN_OFF();

/*
    UARTSendUint(RcvdAddreses.Counter);
    UARTNewLine();
*/

    // Clear recieved addresses
    RcvdAddreses.Counter = 0;
}
