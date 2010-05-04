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

#include "main.h"
#include "cc1101.h"
#include "time_utils.h"
#include "control_unit.h"

struct {
    uint8_t Arr[30];
    uint8_t Counter;
} RcvdAddresses;

enum MotorState_t {M_Idle, M_On, M_Off};
struct {
    uint8_t Count;
    uint8_t PWMcounter;
    uint16_t Timer, TimerUpdate;
    enum MotorState_t State;
} EMotor;

int main(void) {
    GeneralInit();
    UART1_to_SPI_init();
    // ******** Main cycle *********
    while (1){
        wdt_reset();    // Reset watchdog
        CC_Task();
        Motor_TASK();
        Packet_TASK();
    } // while 1
}

FORCE_INLINE void GeneralInit(void){
    wdt_enable(WDTO_2S);

    CC.Address = 1; //Never changes in CC itself
    CC.CycleCounter = 0;

    TimerInit();
    CC_Init();

    // Setup motor
    MOTOR_DDR |= (1<<MOTOR_P);
    EMotor.State = M_Idle;
    TimerResetDelay(&EMotor.TimerUpdate);
    // Motor blink at power-on
    MOTOR_ON();
    _delay_ms(200);
    MOTOR_OFF();

    // Setup Timer1: cycle timings
    TCNT1 = 0;
    OCR1A = 1<<TIMER_MULTI; // firstly, address=1
    TCCR1A = 0;
    ICR1 = CYCLE_DURATION;
    TIMSK1 |= (1<<OCIE1A)|(1<<ICIE1);
    TIM1_START();

    sei();
}

void Motor_TASK(void){
    if (EMotor.Count > 0){
        switch (EMotor.State){
            case M_Idle:    // First came here
                TimerResetDelay(&EMotor.Timer);
                MOTOR_ON();
                EMotor.State = M_On;
                break;

            case M_On:
                if (!TimerDelayElapsed(&EMotor.Timer, MOTOR_ON_TIME)) return;
                TimerResetDelay(&EMotor.Timer);
                MOTOR_OFF();
                EMotor.State = M_Off;
                break;

            case M_Off:
                if (!TimerDelayElapsed(&EMotor.Timer, MOTOR_OFF_TIME)) return;
                // Blink ended, check if this one was the last
                EMotor.Count--;
                if (EMotor.Count > 0){
                    TimerResetDelay(&EMotor.Timer);
                    MOTOR_ON();
                    EMotor.State = M_On;
                }
                else EMotor.State = M_Idle;
                break;
        } //switch
    } // if >0
}

void Packet_TASK(void){
    if (!CC.NewPacketReceived) return;

    uint8_t AlienAddr = CC.RX_Pkt->Data[1];
    switch (CC.RX_Pkt->CommandID){
        case PKT_ID_CALL:
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
                // Modify our address if needed
                if (AlienAddr == CC.Address) {
                    TIMER_ADJUST(AlienAddr);    // Adjust our timer as alien address is lower
                    CC.CycleCounter = CC.RX_Pkt->Data[2];   // Adjust cycle counter
                    CC.TransmitEnable = false;  // Next time just listen - if there is somebody else
                    CC.Address++;               // Increase our address
                    // Change our IRQ timestamp
                    OCR1A = ((uint16_t)CC.Address) << TIMER_MULTI;
                }// if equal
                else { // not equal
                    // Adjust our timer if alien address is lower, and do not otherwise
                    if (AlienAddr < CC.Address){
                        TIMER_ADJUST(AlienAddr);                // Adjust our timer as alien address is lower
                        CC.CycleCounter = CC.RX_Pkt->Data[2];   // Adjust cycle counter
                    }
                    // Count this one if did not do it yet
                    bool AlienIsCounted = false;
                    for (uint8_t i=0; i<RcvdAddresses.Counter; i++)
                        if (RcvdAddresses.Arr[i] == AlienAddr) AlienIsCounted = true;
                    if (!AlienIsCounted)
                        RcvdAddresses.Arr[RcvdAddresses.Counter++] = AlienAddr;
                } // else not equal
            } // Atomic
            break; // ID = CALL

        default:
            break;
    }// switch
    CC.NewPacketReceived = false;
}

// ============================== Interrupts ===================================
// Transmit interrupt
ISR(TIMER1_COMPA_vect){
    if (!CC.TransmitEnable) return;
    // Prepare CALL packet
    CC.TX_Pkt->Address = 0;     // Broadcast
    CC.TX_Pkt->PacketID = 0;    // Current packet ID, to avoid repeative treatment
    CC.TX_Pkt->CommandID = 0xCA;// }
    CC.TX_Pkt->Data[0] = 0x11;  // } CALL packet
    CC.TX_Pkt->Data[1] = CC.Address;
    CC.TX_Pkt->Data[2] = CC.CycleCounter;

    CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
    CC_ENTER_TX();                                  // Entering TX will put device out of sleep mode
}

// Cycle end interrupt 
ISR(TIMER1_CAPT_vect){ // Means overflow IRQ
    // Do things needed at end of RX cycle
    if (CC.CycleCounter == 0){
        if (TimerDelayElapsed(&EMotor.TimerUpdate, 1000)){
//        if (EMotor.State == M_Idle){ // Update only when show has completed
            EMotor.Count = RcvdAddresses.Counter;
            if (EMotor.Count > MAX_COUNT_TO_FLINCH) EMotor.Count = MAX_COUNT_TO_FLINCH; // Saturate count
            RcvdAddresses.Counter = 0;
        }
    }
    // Handle cycle counter
    if (++CC.CycleCounter >= CYCLE_NUMBER){
        CC.CycleCounter = 0;
        CC.TransmitEnable = true;  // Enable transmitting in new RX cycle
    }
    else CC_ENTER_IDLE();          // Powerdown CC when needed
}
