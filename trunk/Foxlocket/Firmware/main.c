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
//#include <avr/eeprom.h>

#include "main.h"
#include "uart_unit.h"
#include "cc1101.h"
#include "ledskeys.h"
#include "time_utils.h"

//#define DEBUG_TRANSMITTER   // Just transmit packets in time
#define TRANSMIT_ENABLE


struct {
    uint8_t Arr[30];
    uint8_t Counter;
} RcvdAddreses;
volatile bool TransmitEnable;

int main(void) {
    LEDKeyInit();
    _delay_ms(270);
    UARTInit();
    UARTNewLine();
    UARTSendString_P(PSTR("Foxlocket started\r"));

    // Get self address
    //CC.Address = eeprom_read_byte(0);
    //if (CC.Address == 0xFF) CC.Address = 0x01;
    CC.Address = 1; //Never changes in CC itself

    TimerInit();
    CC_Init();
    TransmitEnable = false;

    // Setup Timer1
    TCNT1 = 0;
    OCR1A = CC.Address << TIMER_MULTI;
    TCCR1A = 0;
    TCCR1B = TCCR1B_ON;
    ICR1 = CYCLE_DURATION;
    TIMSK |= (1<<OCIE1A)|(1<<TICIE1);

    sei();

    DDRA |= (1<<PA0)|(1<<PA1);
    PORTA &= ~((1<<PA0)|(1<<PA1));

    #ifdef DEBUG_TRANSMITTER
    while(1);
    #endif

    uint8_t InnerState;
    uint8_t AlienAddr;
    bool AlienIsCounted;
    CC.NeededState = CC_RX;

    uint16_t FTimer;
    TimerResetDelay(&FTimer);

    // Main cycle
    while (1){
        CC_Task();

        // Print state
        if (TimerDelayElapsed(&FTimer, 500)){
            InnerState = CC_ReadRegister(CC_MARCSTATE); // Get radio status
            UARTSendString_P(PSTR("\rState: "));
            UARTSendUint(InnerState);
        }

        if (CC.NewPacketReceived){ // Handle packet
            switch (CC.RX_Pkt->CommandID){
                case PKT_ID_CALL: 
                    // If equal: adjust timer & address; if lower: adjust timer and count; if bigger: just count.
                    AlienAddr = CC.RX_Pkt->Data[1];
                    // Modify our address if needed
                    if (AlienAddr == CC.Address) {
                        TimerAdjust();              // Setup our timer as alien address is lower
                        TransmitEnable = false;     // Next time just listen - if there is somebody else
                        CC.Address++;
//                        eeprom_write_byte(0, CC.Address);
                        UARTSendString_P(PSTR("\rNew Addr: "));
                        UARTSendAsHex(CC.Address, true);
                        UARTNewLine();
                    }
                    else {
                        if (AlienAddr < CC.Address) // Setup our timer if alien address is lower
                            TimerAdjust();
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
                    }// else: isn't equal


                    UARTSendString_P(PSTR("\rAlien: "));
                    UARTSendAsHex(AlienAddr, true);
                    UARTSendString_P(PSTR("\rOurs:  "));
                    UARTSendAsHex(CC.Address, true);
                    UARTNewLine();

                    for (uint8_t i=0; i<RcvdAddreses.Counter; i++){
                        UARTSendAsHex(RcvdAddreses.Arr[i], false);
                        UARTSendByte(' ');
                    }
                    UARTNewLine();

                    break;

                default:
                    break;
            }// switch

            CC.NewPacketReceived = false;
            //UARTSendString_P(PSTR("*\r"));
            //CC_PrintPacket();
        } // if (CC.NewPacketReceived)
    } // while 1
}

FORCE_INLINE void TimerAdjust(void){
    // Stop timer
    TCCR1B = TCCR1B_OFF;
    TCNT1H = CC.RX_Pkt->Data[3];
    TCNT1L = CC.RX_Pkt->Data[4];

    // Start timer
    TCCR1B = TCCR1B_ON;
}

// ============================== Interrupts ===================================
ISR(TIMER1_COMPA_vect){
    #ifdef TRANSMIT_ENABLE
    if (TransmitEnable){
        // Prepare CALL packet
        CC.TX_Pkt->Address = 0;    // Recipient address
        CC.TX_Pkt->PacketID = 0;   // Current packet ID, to avoid repeative treatment
        CC.TX_Pkt->CommandID = 0xCA;
        CC.TX_Pkt->Data[0] = 0x11;
        CC.TX_Pkt->Data[1] = CC.Address;

        CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH);     // Write bytes to FIFO
        CC.NeededState = CC_TX;
    }
    #else
    _delay_ms(1);
    #endif
    
}

ISR(TIMER1_CAPT_vect){ // Means overflow IRQ
    #ifndef DEBUG_TRANSMITTER
    TransmitEnable = true;  // May transmit next time
    if (RcvdAddreses.Counter > 0) LED_GREEN_ON();
    else LED_GREEN_OFF();

/*
    UARTSendUint(RcvdAddreses.Counter);
    UARTNewLine();
*/

    // Clear recieved addresses
    RcvdAddreses.Counter = 0;
    #endif
}
