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
#include "corma.h"
#include "time_utils.h"
#include "common/common.h"
#include "common/cc2500.h"

//#define DEBUG_UART
#ifdef DEBUG_UART
#include "uart_soft.h"
#endif

// ============================= Types =========================================
enum CC_Mode_t {CC_Sleep, CC_RX, CC_TX};
struct {
    uint16_t Timer;
    bool JustEnteredRX;
    enum CC_Mode_t Mode;
} CC_Srv;
struct {
    uint8_t Addr;
    uint8_t OtherAddr[30];
    uint8_t OtherCounter;
    uint8_t CycleCounter;
} Corma;



// ============================== General ======================================
int main(void) {
    GeneralInit();

    #ifdef DEBUG_UART
    UARTInit();
    UARTSendString_P(PSTR("Calma is here\r"));
    SetDesiredColor (50, 50, 50);
    #endif

    sei(); 
    while (1) {
        wdt_reset();    // Reset watchdog
        CC_Task();
        //Motor_TASK();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    // Setup timer
    TimerInit();    // Time counter

    // Corma init
    Corma.Addr = eeprom_read_byte(EE_CORMA_ADDRESS);
    if (Corma.Addr == 0xFF) Corma.Addr = 0;   // Erased eeprom
    Corma.OtherCounter = 0;
    Corma.CycleCounter = 0;

    // Setup motor
    MotorInit();

    // CC init
    CC_Srv.JustEnteredRX = false;
    CC_Srv.Mode = CC_TX;
    TimerResetDelay(&CC_Srv.Timer);
    CC_Init();
    CC_SetChannel(CORMA_CHANNEL);
    CC_SetAddress(4);   //Never changes in CC itself
}

// ============================== Tasks ========================================
void CC_Task (void) {
    // Handle packet if received
    if (CC.NewPacketReceived) {
        CC.NewPacketReceived = false;
        EVENT_NewPacket();
    }

    // If in sleep mode, check if it is time to wake-up; otherwise return
/*
    if (CC_Srv.DeepSleep) {
        if (TimerDelayElapsed(&CC_Srv.Timer, CC_RX_OFF_DELAY)) CC_Srv.DeepSleep = false;
        else return;
    }
*/
    // Do with CC what needed
    CC_GET_STATE();
    switch (CC.State){
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;

        case CC_STB_IDLE:   // Idle mode means that CC just has awaken
            if (CC_Srv.Mode == CC_TX) {
                // Prepare packet & transmit it

            }
            else if (CC_Srv.Mode == CC_RX) {
                CC_ENTER_RX();
                CC_Srv.JustEnteredRX = true;
            }
            break;

        case CC_STB_RX:
            // Reset timer if just entered RX
            if (CC_Srv.JustEnteredRX) {
                CC_Srv.JustEnteredRX = false;
                TimerResetDelay(&CC_Srv.Timer);
            }
            else {
                // Check if CC_RX_ON_DELAY delay elapsed
                if (TimerDelayElapsed(&CC_Srv.Timer, CC_RX_ON_DELAY)) { // Time to switch off
                    CC_ENTER_IDLE();
                    CC_Srv.Mode = CC_TX;
                    //CC_POWERDOWN();
                    //CC_Srv.Mode = CC_Sleep;
                }// if timer
            }// if not RX
            break;

        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}


// ============================== Events =======================================
FORCE_INLINE void EVENT_NewPacket(void) {
    if ((CC.RX_Pkt.CommandID == PKT_ID_CALL_HI) && (CC.RX_Pkt.Data[0] == PKT_ID_CALL_LO)) {

    } // if PKT_ID_Color
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

