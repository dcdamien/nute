/* 
 * File:   corma.c
 * Author: Laurelindo
 *
 * Created on 27 06 2010 г., 0:30
 */
#include <avr/io.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "corma.h"
#include "time_utils.h"
#include "motor.h"
#include "common/common.h"
#include "common/cc2500.h"

//#define DEBUG_UART
#ifdef DEBUG_UART
#include "uart_soft.h"
#endif

// ============================= Types =========================================
struct {
    uint8_t Addr;
    uint8_t OtherAddr[MAX_OTHERS_COUNT];
    uint8_t OtherCounter;
    uint8_t CycleCounter;
    bool CC_Sleeping;
} Corma;

// ============================== General ======================================
int main(void) {
    GeneralInit();

    #ifdef DEBUG_UART
    UARTInit();
    UARTSendString_P(PSTR("Calma is here\r"));
    #endif

    // DEBUG
    DDRA = 0xFF;
    uint16_t Timerr;
    TimerResetDelay(&Timerr);

    sei(); 
    while (1) {
        wdt_reset();    // Reset watchdog
        CC_Task();
        //Motor_TASK();
        if (TimerDelayElapsed(&Timerr, 20)) {
            PORTA ^= 1<<PA7;
        }

    } // while
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator

    // Setup timer
    TimerInit();

    // Corma init
    Corma.Addr = eeprom_read_byte(EE_CORMA_ADDRESS);
    if (Corma.Addr == 0xFF) Corma.Addr = 0;   // Erased eeprom
    Corma.OtherCounter = 0;
    Corma.CycleCounter = 0;

    // Setup motor
    //MotorInit(Corma.Addr);

    // CC init
    Corma.CC_Sleeping = false;
    CC_Init();
    CC_SetChannel(CORMA_CHANNEL);
    CC_SetAddress(4);   //Never changes in CC itself

    // Setup Timer1: cycle timings
    TCNT1 = 0;
    TCCR1A = 0;
    OCR1A = ((uint16_t)Corma.Addr) * PKT_DURATION;  // TX start
    ICR1 = SUBCYCLE_DURATION;                       // TX + RX/Sleep duration
    TIMSK |= (1<<OCIE1A)|(1<<TICIE1);
    CYC_TIMER_START();
}

// ============================== Tasks ========================================
void CC_Task (void) {
    // Handle packet if received
    if (CC.NewPacketReceived) {
        CC.NewPacketReceived = false;
        EVENT_NewPacket();
    }

    // Check if sleeping
    if (Corma.CC_Sleeping) return;  // Nothing to do here. We'll wake in interrupt.

    // Do with CC what needed
    CC_GET_STATE();
    switch (CC.State){
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;

        case CC_STB_IDLE:
            if (Corma.CycleCounter == 0) {  // rx cycle
                // Enter RX-after-TX
   //             CC_ENTER_RX();
                Corma.CC_Sleeping = false;
            }
            else { // TX cycle
                PORTA |= (1<<PA2);// DEBUG
                // May be IDLE only after TX
                //CC_POWERDOWN();
                Corma.CC_Sleeping = true;
                _delay_us(1500);
                PORTA &= ~(1<<PA2); // DEBUG
            }
            break;

        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}

// ============================== Events =======================================
FORCE_INLINE void EVENT_NewPacket(void) {
    if (CC.RX_Pkt.CommandID == PKT_ID_CALL) {

    } // if PKT_ID_Call
    #ifdef DEBUG_UART
    UARTSendUint(CC.RX_Pkt.PacketID);
    UARTSend(' ');
    UARTSendAsHex(CC.RX_Pkt.Data[1]);
    UARTSend(' ');
    UARTSendAsHex(CC.RX_Pkt.Data[2]);
    UARTSend(' ');
    UARTSendAsHex(CC.RX_Pkt.Data[3]);

    UARTSend(' ');
    UARTSend(' ');
    UARTSendUint(CC.RX_Pkt.RSSI);
    UARTSend(' ');
    UARTSendAsHex(CC.RX_Pkt.LQI);
    UARTNewLine();
    #endif
}

// ============================ Interrupts =====================================
// Transmit interrupt
ISR(TIMER1_COMPA_vect) {
    PORTA |= (1<<PA3); // DEBUG
    // Enter TX mode
    CC_ENTER_IDLE();
    CC_GDO0_IRQ_DISABLE();  // Do not interrupt during transmit
    // Prepare packet & transmit it
    CC.TX_Pkt.ToAddr = 0;      // Broadcast
    CC.TX_Pkt.CommandID = PKT_ID_CALL;
    CC.TX_Pkt.SenderAddr = Corma.Addr;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        CC.TX_Pkt.SenderTime = TCNT1;
    }
    CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
    CC_ENTER_TX();
    Corma.CC_Sleeping = false;
    PORTA &= ~(1<<PA3); // DEBUG
}

// SubCycle end interrupt
ISR(TIMER1_CAPT_vect) { // Means overflow IRQ
    PORTA |= (1<<PA1);// DEBUG
    _delay_us(500);
    // Handle cycle counter
    if (++Corma.CycleCounter >= CYCLE_COUNT) Corma.CycleCounter = 0;

    if (Corma.CycleCounter == 0) {  // RX cycle
        // Enter RX-before-TX
//        CC_ENTER_RX();
//        CC_GDO0_IRQ_ENABLE();   // Enable RX interrupt
        Corma.CC_Sleeping = false;
    }
    PORTA &= ~(1<<PA1);// DEBUG
}