/*
 * File:   main.c
 * Author: Kreyl
 *
 * Created on April 14, 2011, 12:53 PM
 */

#include <avr/io.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "main.h"
#include "delay_util.h"
#include "common.h"
#include "cc2500.h"

// ============================= Types =========================================
struct {
    uint8_t Addr;
    uint8_t CycleCounter;
    bool CC_IsSleeping;
} Tear;
struct {
    uint16_t Timer;
    bool IsOn;
    uint8_t PWMDesired, PWM;
} ELED;

// ============================== General ======================================
int main(void) {
    GeneralInit();
    while (1) {
        wdt_reset();    // Reset watchdog
        CC_Task();
        LED_Task();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    DelayInit();
    // Tear init
    Tear.Addr = eeprom_read_byte(EE_TEAR_ADDRESS);
    if (Tear.Addr == 0xFF) Tear.Addr = 0;   // Erased eeprom
    Tear.CycleCounter = 0;
    // LED init
    LED_DDR  |=  (1<<LED_P);
    LED_PORT &= ~(1<<LED_P);
    ELED.PWMDesired = 0;
    ELED.PWM = 0;
    DelayReset(&ELED.Timer);
    ELED.IsOn = false;
    // CC init
    CC_Init();
    CC_SetChannel(TEAR_CHANNEL);
    CC_SetAddress(4);   //Never changes in CC itself
    // Setup Timer1: cycle timings
    TCNT1 = 0;
    TCCR1A = 0;
    OCR1A = ((uint16_t)Tear.Addr) * PKT_DURATION;   // TX start
    ICR1 = SUBCYCLE_DURATION;                       // TX + RX/Sleep duration
    TIMSK1 = (1<<OCIE1A)|(1<<ICIE1);
    CYC_TIMER_START();

    sei();
}

// ============================== Tasks ========================================
void CC_Task (void) {
    // Handle packet if received
    if (CC.NewPacketReceived) {
        CC.NewPacketReceived = false;
        EVENT_NewPacket();
    }
    // Do with CC what needed
    CC_GET_STATE();
    switch (CC.State){
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;
        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}

void LED_Task(void) {
    if (ELED.PWM == ELED.PWMDesired) return;    // Nothing to do if ok
    if (ELED.PWMDesired < ELED.PWM) {           // Lower PWM
        if (MayChangePWM()) {
            ELED.PWM--;
            PWM_SET(ELED.PWM);
        }
        // Workaround hardware PWM bug: LED does not switches off totally
        if (ELED.PWM == 0) PWMDisable();
    }
    else {
        if (ELED.PWM == 0) PWMEnable();
        if (MayChangePWM()) {
            ELED.PWM++;
            PWM_SET(ELED.PWM);
        } // if may change
    } // Fade or brighten
}

// =================================== PWM =====================================
FORCE_INLINE void PWMEnable(void){
    // Setup timer2
    TCNT2 = 0x00;
    OCR1B = 0x00;
    // Disable Timer1 interrupts
    TIMSK2 = 0;
    // B-Channel Fast PWM
    TCCR2A = (1<<COM2B1)|(1<<COM2B0)|(1<<WGM21)|(1<<WGM20);
    TCCR2B = (1<<CS20); // Highest frequency
}
FORCE_INLINE void PWMDisable(void){
    TCCR2B  = 0x00;     // Stop Timer2
}
bool MayChangePWM(void) {
    if (ELED.PWM <= PWMStepOver1)                                   return DelayElapsed(&ELED.Timer, PWMDelayLong);        // Low speed
    else if (ELED.PWM > PWMStepOver1 && ELED.PWM <= PWMStepOver2)   return DelayElapsed(&ELED.Timer, PWMDelayMid);         // Mid-speed
    else if (ELED.PWM > PWMStepOver2)                               return DelayElapsed(&ELED.Timer, PWMDelayFast);        // High-speed
    return false;
}

// ============================== Events =======================================
FORCE_INLINE void EVENT_NewPacket(void) {
    if (CC.RX_Pkt.CommandID != CMD_ID) return;
    // Other is here, light up
    ELED.PWMDesired = PWM_MAX;
    // Adjust our timer if sender address is lower, and do not otherwise
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        if (CC.RX_Pkt.SenderAddr < Tear.Addr) {
            CYC_TIMER_STOP();
            Tear.CycleCounter = CC.RX_Pkt.SenderCycle;
            TCNT1 = CC.RX_Pkt.SenderTime;
            CYC_TIMER_START();
        } // if addr
    } // Atomic
}

// ============================ Interrupts =====================================
// Transmit interrupt
ISR(TIMER1_COMPA_vect) {
    CYC_TIMER_STOP();
    // Prepare packet & transmit it
    CC.TX_Pkt.ToAddr = 0;      // Broadcast
    CC.TX_Pkt.CommandID = CMD_ID;
    CC.TX_Pkt.SenderAddr = Tear.Addr;
    CC.TX_Pkt.SenderCycle = Tear.CycleCounter;
    CC.TX_Pkt.SenderTime = TCNT1;   // No need in ATOMIC as we are in IRQ handler
    CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
    CC_ENTER_TX();
    // Wait for packet to transmit completely
    while (!CC_GDO0_IS_HI());   // After this, SYNC word is transmitted
    while (CC_GDO0_IS_HI());    // After this, packet is transmitted
    if (Tear.CycleCounter == 0) CC_ENTER_RX();  // Enter RX after TX
    CYC_TIMER_START();
}

// SubCycle end interrupt
ISR(TIMER1_CAPT_vect) {
    // Handle cycle counter
    if (++Tear.CycleCounter >= CYCLE_COUNT) {  // Zero cycle begins
        Tear.CycleCounter = 0;
        ELED.PWMDesired = 0;    // Reset light
        // Enter RX-before-TX
        CC_ENTER_RX();
    }
    else CC_ENTER_IDLE();   // Non-zero cycle
}
