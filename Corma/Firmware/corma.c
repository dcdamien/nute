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

// ============================= Types =========================================
struct {
    uint8_t Addr;
    uint8_t OtherAddr[MAX_OTHERS_COUNT];
    uint8_t OthersCounter;
    uint8_t CycleCounter;
    bool CC_IsSleeping;
} Corma;

// ============================== General ======================================
int main(void) {
    GeneralInit();

    // DEBUG
    DDRA = 0xFF;
    uint16_t Timerr;
    TimerResetDelay(&Timerr);

    sei(); 
    while (1) {
        wdt_reset();    // Reset watchdog
        CC_Task();
        Motor_TASK();
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
    Corma.OthersCounter = 0;
    Corma.CycleCounter = 0;

    // Setup motor
    MotorInit(Corma.Addr+1);

    // CC init
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

    // Do with CC what needed
    CC_GET_STATE();
    switch (CC.State){
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;

        case CC_STB_RX:
            PORTA |= (1<<PA4);
            break;
            
        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            PORTA &= ~(1<<PA4);
            break;
    }//Switch
}

// ============================== Events =======================================
FORCE_INLINE void EVENT_NewPacket(void) {
    if (CC.RX_Pkt.CommandID == PKT_ID_CALL) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            // Count this one if did not do it yet
            bool IsCounted = false;
            for (uint8_t i=0; i<Corma.OthersCounter; i++)
                if (Corma.OtherAddr[i] == CC.RX_Pkt.SenderAddr) {
                    IsCounted = true;
                    break;
                }
            if (!IsCounted)
                Corma.OtherAddr[Corma.OthersCounter++] = CC.RX_Pkt.SenderAddr;
            
            // Adjust our timer if sender address is lower, and do not otherwise
            if (CC.RX_Pkt.SenderAddr < Corma.Addr) {
                CYC_TIMER_STOP();
                Corma.CycleCounter = CC.RX_Pkt.SenderCycle;
                TCNT1 = CC.RX_Pkt.SenderTime;
/*
                if (TCNT1 > SUBCYCLE_DURATION) {
                    TCNT1 -= SUBCYCLE_DURATION;
                    NewSubcycle();
                }
*/
                CYC_TIMER_START();
            } // if addr
        } // Atomic
    } // if PKT_ID_Call
}

// ============================ Interrupts =====================================
// Transmit interrupt
ISR(TIMER1_COMPA_vect) {
    PORTA &= ~(1<<PA4);
    PORTA |= (1<<PA3); // DEBUG
    CYC_TIMER_STOP();
    // Prepare packet & transmit it
    CC.TX_Pkt.ToAddr = 0;      // Broadcast
    CC.TX_Pkt.CommandID = PKT_ID_CALL;
    CC.TX_Pkt.SenderAddr = Corma.Addr;
    CC.TX_Pkt.SenderCycle = Corma.CycleCounter;
    CC.TX_Pkt.SenderTime = TCNT1;   // No need in ATOMIC as we are in IRQ handler
    CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
    CC_EnterTX();
    // Wait for packet to transmit completely
    while (!CC_GDO0_IS_HI());   // After this, SYNC word is transmitted
    while (CC_GDO0_IS_HI());    // After this, packet is transmitted
    if (Corma.CycleCounter == 0) CC_EnterRX();  // Enter RX after TX
    CYC_TIMER_START();
    PORTA &= ~(1<<PA3); // DEBUG
}

// SubCycle end interrupt
ISR(TIMER1_CAPT_vect) { // Means overflow IRQ
    NewSubcycle();
}

void NewSubcycle(void) {
    PORTA |= (1<<PA1);// DEBUG
    _delay_us(500);
    // Handle cycle counter
    if (++Corma.CycleCounter >= CYCLE_COUNT) {  // Zero cycle begins
        Corma.CycleCounter = 0;
        // Flinch!
        MotorSetCount (Corma.OthersCounter);
        Corma.OthersCounter = 0;
        // Enter RX-before-TX
        CC_EnterRX();
    }
    else CC_ENTER_IDLE();   // Non-zero cycle
    PORTA &= ~(1<<PA1);// DEBUG
}
