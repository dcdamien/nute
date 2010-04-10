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

//#define DEBUG_TRANSMITTER   // Just transmit packets in time

#ifdef DEBUG_TRANSMITTER
#define TRANSMIT_ENABLE
#else
//#define TRANSMIT_ENABLE
#endif

struct {
    uint8_t Arr[30];
    uint8_t Counter;
} RcvdAddreses;
//volatile

int main(void) {
    LEDKeyInit();
    _delay_ms(270);
    UARTInit();
    UARTNewLine();
    UARTSendString_P(PSTR("Foxlocket started\r"));

    // Get self address
    CC.Address = eeprom_read_byte(0);
    if (CC.Address == 0xFF) CC.Address = 0x01;

    TimerInit();
    CC_Init();

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

//    uint8_t InnerState;
    uint8_t AlienAddr;
    bool AlienIsCounted;
    // Main cycle
    while (1){
        CC.NeededState = CC_RX;
        CC_Task();
//        InnerState = CC_ReadRegister(CC_MARCSTATE);     // Get status

        if (CC.NewPacketReceived){ // Handle packet
            switch (CC.PPacket->CommandID){
                case PKT_ID_CALL: 
                    // If equal: adjust timer & address; if lower: adjust timer and count; if bigger: just count.
                    AlienAddr = CC.PPacket->Data[1];
                    // Modify our address if needed
                    if (AlienAddr == CC.Address) {
                        TIMER_ADJUST(AlienAddr);    // Setup our timer as alien address is lower
                        CC.Address++;
                        UARTSendString_P(PSTR("\rNew addr: "));
                        UARTSendAsHex(CC.Address, true);
                        eeprom_write_byte(0, CC.Address);
                    }
                    else {
                        if (AlienAddr < CC.Address) // Setup our timer if alien address is lower
                            TIMER_ADJUST(AlienAddr);
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
                    break;

                default:
                    break;
            }// switch

            CC.NewPacketReceived = false;
            UARTSendString_P(PSTR("*\r"));
            //CC_PrintPacket();
        }
    } // while 1
}

// ============================== Interrupts ===================================
ISR(TIMER1_COMPA_vect){
    PORTA |= (1<<PA0);
    #ifdef TRANSMIT_ENABLE
    // Prepare CALL packet

    CC.PPacket->Address = 0;    // Recipient address
    CC.PPacket->PacketID = 0;   // Current packet ID, to avoid repeative treatment
    CC.PPacket->CommandID = 0xCA;
    CC.PPacket->Data[0] = 0x11;
    CC.PPacket->Data[1] = CC.Address;

    CC_TransmitPacket();
    #else
    _delay_ms(1);
    #endif
    PORTA &= ~(1<<PA0);
}

ISR(TIMER1_CAPT_vect){ // Means overflow IRQ
    #ifndef DEBUG_TRANSMITTER
    if (RcvdAddreses.Counter > 0) LED_GREEN_ON();
    else LED_GREEN_OFF();
    // Clear recieved addresses
    RcvdAddreses.Counter = 0;
    #endif
}
