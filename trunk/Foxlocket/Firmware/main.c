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
    uint16_t Timer, TransmitTimer;
    uint16_t WhenTransmit;
    bool IsActive;
} Cycle;

int main(void) {
    LEDKeyInit();
    _delay_ms(270);
    UARTInit();
    UARTNewLine();
    UARTSendString_P(PSTR("Foxlocket started\r"));

    //eeprom_write_byte(0, 1);
    // Get self address
    CC.Address = eeprom_read_byte(0);
    if (CC.Address == 0xFF) CC.Address = 0x01;
    CC.Address = 1;


    TimerInit();
    CC_Init();

    Cycle.IsActive = false;
    TimerResetDelay(&Cycle.Timer);
    Cycle.WhenTransmit = PKT_DURATION*CC.Address;

    // Setup Timer1
    TCNT1 = 0;
    OCR1A = CC.Address << 5;
    TCCR1A = 0;
    TCCR1B = TCCR1B_ON;
    ICR1 = CYCLE_DURATION;
    TIMSK |= (1<<OCIE1A)|(1<<TICIE1);

    sei();

    DDRA |= (1<<PA0)|(1<<PA1);
    PORTA &= ~((1<<PA0)|(1<<PA1));

    uint8_t InnerState;
    // Main cycle
    while (1){
        //CC_Task();
        InnerState = CC_ReadRegister(CC_MARCSTATE);     // Get status
        if (InnerState != CC_ST_IDLE) PORTA |= (1<<PA0);
        else PORTA &= ~(1<<PA0);

/*
        if (TimerDelayElapsed(&Cycle.Timer, 500))
            if (!Cycle.IsActive){
                Cycle.IsActive = true;
                // Reset transmit timer
                TimerResetDelay(&Cycle.TransmitTimer);
            }
            else Cycle.IsActive = false;
        }// if timer

        if (Cycle.IsActive){


        }// if cycle
*/
    } // while 1
/*
        if (CC.NewPacketReceived){
            CC.NewPacketReceived = false;
            UARTSendString_P(PSTR("*\r"));
//            CC_PrintPacket();
        }
*/

/*
        if (TimerDelayElapsed(&MainTimer, 500)){
            uint8_t b=CC_ReadRegister(CC_MARCSTATE);
//            uint8_t b=CC_ReadRegister(CC_RSSI);
            UARTSendUint(b);
            UARTNewLine();
        } // if delay
*/
/*
        CC.NeededState = CC_RX;
        CC_Task();
*/
    
}

// ============================== Interrupts ===================================
ISR(TIMER1_COMPA_vect){
    //PORTA |= (1<<PA0);
    // Prepare CALL packet
    CC.PPacket->Address = 0;    // Recipient address
    CC.PPacket->PacketID = 0;   // Current packet ID, to avoid repeative treatment
    CC.PPacket->CommandID = 0xCA;
    CC.PPacket->Data[0] = 0x11;
    CC.PPacket->Data[1] = CC.Address;

    CC_TransmitPacket();
//    _delay_ms(2);
    //PORTA &= ~(1<<PA0);
}

ISR(TIMER1_CAPT_vect){
    PORTA |= (1<<PA1);
    _delay_ms(2);
    PORTA &= ~(1<<PA1);
}

/*
 *             if (b==CC_ST_RX_OVERFLOW){
                CC_ENTER_IDLE();
                _delay_ms(100);
                CC_FLUSH_RX_FIFO();
                _delay_ms(100);
                CC.State = CC_Idle;
            }
            else CC.NeededState = CC_RX;

*/
/*
            if (ERandom.IsReady){
                UARTNewLine();
                //UARTSendAsHex(ERandom.Random, true);
                UARTSendAsHex(ADCL, true);
                RandomStart();
            }
*/

