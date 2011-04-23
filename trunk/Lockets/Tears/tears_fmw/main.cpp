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
//#include <avr/eeprom.h>
#include <stdlib.h>     // Randoms
#include "main.h"
#include "delay_util.h"
#include "common.h"
#include "cc2500.h"

// ============================= Types =========================================
struct LED_t {
    uint16_t Timer;
    bool IsOn;
    uint8_t PWMDesired, PWM;
};

LED_t ELED;

#define SUBCYCLE_MAX    7
#define LISTEN_TIME     210
struct Cycle_t {
    uint16_t Timer, CurrentDelay;
    uint8_t CurrentSubCycle;
};
Cycle_t Cycle;

#define OTHERS_COUNTS_COUNT 4   // How many past counts to store
#define OTHERS_MAX_ID_COUNT 4   // Maximum others count value
class Others_t {
private:
    uint8_t FPastCounts[OTHERS_COUNTS_COUNT];
    uint16_t FIDs[OTHERS_MAX_ID_COUNT];
    uint8_t FIDsCount;
public:
    void Init(void);
    void AddNew(uint16_t OtherID);
    void StoreCount(void);
    uint8_t GetMaxCount(void);
};
Others_t Others;


// ============================== General ======================================
int main(void) {
    GeneralInit();

    DDRC |= (1<<PC2);   // DEBUG

    while (1) {
        wdt_reset();    // Reset watchdog
        CC_Task();
        Cycle_Task();
        LED_Task();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    //wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    DelayInit();
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

    // Setup cycles
    Cycle.CurrentDelay = LISTEN_TIME;
    Cycle.CurrentSubCycle = SUBCYCLE_MAX;
    CC.OldState = CC_STB_IDLE;
    EVENT_CycleTimerFire(); // To enter first cycle

    Others.Init();

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

        case CC_STB_TX:
            CC.OldState = CC_STB_TX;
            break;

        case CC_STB_IDLE:
            if (CC.OldState == CC_STB_TX) {
                CC.OldState = CC_STB_IDLE;
                EVENT_TxToIdle();
            }
            break;

        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}

void LED_Task(void) {
    if (ELED.PWM == ELED.PWMDesired) return;    // Nothing to do if equal
    if (ELED.PWMDesired < ELED.PWM) {           // Lower PWM
        if (PWMDelayElapsed()) {
            ELED.PWM--;
            PWM_SET(ELED.PWM);
        }
        if (ELED.PWM == 0) PWMDisable();
    }
    else {
        if (ELED.PWM == 0) PWMEnable();
        if (PWMDelayElapsed()) {
            ELED.PWM++;
            PWM_SET(ELED.PWM);
        } // if may change
    } // Fade or brighten
}

void Cycle_Task(void) {
    if (DelayElapsed(&Cycle.Timer, Cycle.CurrentDelay)) EVENT_CycleTimerFire();
}

// =================================== PWM =====================================
FORCE_INLINE void PWMEnable(void){
    // Setup timer2
    TCNT2 = 0x00;
    OCR1B = 0x00;
    // Disable Timer1 interrupts
    TIMSK2 = 0;
    // B-Channel Fast PWM
    TCCR2A = (1<<COM2B1)|(0<<COM2B0)|(1<<WGM21)|(1<<WGM20);
    TCCR2B = (1<<CS20); // Highest frequency
}
FORCE_INLINE void PWMDisable(void){
    TCCR2A = 0x00;  // Disconnect output
    TCCR2B = 0x00;  // Stop Timer2
}
bool PWMDelayElapsed(void) {
    if (ELED.PWM <= PWMStepOver1)                                   return DelayElapsed(&ELED.Timer, PWMDelayLong);        // Low speed
    else if (ELED.PWM > PWMStepOver1 && ELED.PWM <= PWMStepOver2)   return DelayElapsed(&ELED.Timer, PWMDelayMid);         // Mid-speed
    else if (ELED.PWM > PWMStepOver2)                               return DelayElapsed(&ELED.Timer, PWMDelayFast);        // High-speed
    return false;
}

// ============================== Events =======================================
FORCE_INLINE void EVENT_NewPacket(void) {   // Other is here
    Others.AddNew(CC.RX_Pkt.PktID);
}

// End of transmission
void EVENT_TxToIdle(void) {
    DelayReset(&Cycle.Timer);
    if (Cycle.CurrentSubCycle == 0) {
        CC_ENTER_RX();
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            Cycle.CurrentDelay = LISTEN_TIME;
        }
    }
    else if (Cycle.CurrentSubCycle == SUBCYCLE_MAX) {    // Change length of last subcycle
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            Cycle.CurrentDelay = LISTEN_TIME + (((uint8_t)rand()) >> 4);
        }
    }
    // Otherwise, stay in IDLE for LISTEN_TIME.
}
// End of RX or IDLE time, end of subcycle
void EVENT_CycleTimerFire(void) {
    // Handle end of subcycle
    Cycle.CurrentSubCycle++;
    if (Cycle.CurrentSubCycle > SUBCYCLE_MAX) { // New cycle begins
        Cycle.CurrentSubCycle = 0;
        // Setup packet to transmit
        CC.TX_Pkt.ToAddr = 4;      // For same device only
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            CC.TX_Pkt.PktID = (uint16_t)rand(); // Unicue ID of sequence of packets
        }
        // Decide what to do with light
        Others.StoreCount();
        if (Others.GetMaxCount() != 0) ELED.PWMDesired = PWM_MAX;
        else ELED.PWMDesired = 0;
    } // if zero cycle

    // Transmit packet
    CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
    CC_ENTER_TX();
}

// ============================ Others_t =======================================
void Others_t::Init() {
    FIDsCount = 0;
    for(uint8_t i=0; i<OTHERS_COUNTS_COUNT; i++) FPastCounts[i] = 0;
}
void Others_t::AddNew(uint16_t OtherID) {
    // Get out if maximum achieved
    if (FIDsCount == OTHERS_MAX_ID_COUNT) return;
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        // Count this one if did not do it yet
        bool IsCounted = false;
        for (uint8_t i=0; i<FIDsCount; i++)
            if (FIDs[i] == OtherID) {
                IsCounted = true;
                break;
            }
        // Add ID if not counted
        if (!IsCounted) FIDs[FIDsCount++] = OtherID;
    }
}
void Others_t::StoreCount() {
    // Shift array left
    for (uint8_t i=0; i<OTHERS_COUNTS_COUNT-1; i++)
        FPastCounts[i] = FPastCounts[i+1];
    // Remember current count
    FPastCounts[OTHERS_COUNTS_COUNT-1] = FIDsCount;
    // Reset current counter
    FIDsCount = 0;
}
uint8_t Others_t::GetMaxCount() {
    uint8_t imax = 0;
    for (uint8_t i=0; i<OTHERS_COUNTS_COUNT; i++)
        if (FPastCounts[i] > imax) imax = FPastCounts[i];
    return imax;
}

