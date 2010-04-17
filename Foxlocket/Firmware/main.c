/*
 * File:   main.c of FoxLocket project
 * Author: Laurelindo
 *
 * Created on 2010.04.07
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/wdt.h>

#include <util/delay.h>
#include <avr/pgmspace.h>

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
    wdt_enable(WDTO_2S);
    LEDKeyInit();

    // Debug
    UARTInit();
    UARTSendString_P(PSTR("\rFoxlocket started\r"));
    DDRA |= (1<<PA0)|(1<<PA1)|(1<<PA2);
    PORTA &= ~((1<<PA0)|(1<<PA1)|(1<<PA2));

    CC.Address = 1; //Never changes in CC itself
    CC.CycleCounter = 0;

    TimerInit();
    CC_Init();

    // Setup Timer1: cycle timings
    TCNT1 = 0;
    OCR1A = ((uint16_t)CC.Address) << TIMER_MULTI;
    TCCR1A = 0;
    ICR1 = CYCLE_DURATION;
    TIMSK1 |= (1<<OCIE1A)|(1<<ICIE1);
    TIM1_START();

    sei();


/*
    uint16_t FTimer;
    TimerResetDelay(&FTimer);
*/


    // Main cycle
    while (1){
        wdt_reset();
        CC_Task();

/*
        if (TimerDelayElapsed(&FTimer, 1000)){
            CC_GET_STATE();
            UARTSendAsHex(CC.State, true);
            UARTNewLine();
        }
*/


        if (CC.NewPacketReceived){ // Handle packet
            uint8_t AlienAddr = CC.RX_Pkt->Data[1];
            switch (CC.RX_Pkt->CommandID){
                case PKT_ID_CALL:
                    // Modify our address if needed
                    if (AlienAddr == CC.Address) {
                        TIMER_ADJUST(AlienAddr);    // Adjust our timer as alien address is lower
                        CC.TransmitEnable = false;  // Next time just listen - if there is somebody else
                        CC.Address++;               // Increase our address
                        ATOMIC_BLOCK(ATOMIC_RESTORESTATE){  // Change our IRQ timestamp
                            OCR1A = ((uint16_t)CC.Address) << TIMER_MULTI;
                        }//atomic
                    }// if equal
                    else {
                        // Adjust our timer if alien address is lower, and do not otherwise
                        if (AlienAddr < CC.Address) TIMER_ADJUST(AlienAddr);
                        // Count this one if did not do it yet
                        bool AlienIsCounted = false;
                        for (uint8_t i=0; i<RcvdAddreses.Counter; i++)
                            if (RcvdAddreses.Arr[i] == AlienAddr) AlienIsCounted = true;
                        if (!AlienIsCounted)
                            RcvdAddreses.Arr[RcvdAddreses.Counter++] = AlienAddr;
                    } // else not equal
                    break; // ID = CALL

                default:
                    break;
            }// switch
            CC.NewPacketReceived = false;
        } // if (CC.NewPacketReceived)
    } // while 1
}


// ============================== Interrupts ===================================
// Transmit interrupt
ISR(TIMER1_COMPA_vect){
    if (!CC.TransmitEnable) return;
    PORTA |= (1<<PA0);          // DEBUG
    // Prepare CALL packet
    CC.TX_Pkt->Address = 0;     // Broadcast
    CC.TX_Pkt->PacketID = 0;    // Current packet ID, to avoid repeative treatment
    CC.TX_Pkt->CommandID = 0xCA;// }
    CC.TX_Pkt->Data[0] = 0x11;  // } CALL packet
    CC.TX_Pkt->Data[1] = CC.Address;

    CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
    CC_ENTER_TX();                                  // Entering TX will put device out of sleep mode
    CC.IsPowerDown = false;
    PORTA &= ~(1<<PA0); // DEBUG
}

// ******* Cycle end interrupt *******
ISR(TIMER1_CAPT_vect){ // Means overflow IRQ
    // Handle cycle counter
    if (++CC.CycleCounter == CYCLE_NUMBER) CC.CycleCounter = 0;
    // In new cycle, enable transmitting
    CC.TransmitEnable = true;

    // Powerdown CC if needed
    if (CC.CycleCounter == CYCLE_RX) {
        CC_ENTER_RX();
        CC.IsPowerDown = false;
    }
    else {
        CC_POWERDOWN();
        CC.IsPowerDown = true;
    }

    // Display received aliens
    if (RcvdAddreses.Counter > 0) LED_GREEN_ON();
    else LED_GREEN_OFF();
    // Clear recieved addresses
    RcvdAddreses.Counter = 0;
}

