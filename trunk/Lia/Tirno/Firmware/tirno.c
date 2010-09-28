/* 
 * File:   tirno.c
 * Author: Laurelindo
 *
 * Created on 27 06 2010 г., 0:30
 */
#include <avr/io.h>
#include <stdbool.h>
#include <avr/wdt.h>
//#include <avr/eeprom.h>
#include <util/delay.h>
#include "tirno.h"
//#include "delay_util.h"
//#include "battery.h"
#include "common.h"
//#include "cc2500.h"
#include "lcd110x.h"

// =============================== Types =======================================

// ============================== General ======================================
int main(void) {
    GeneralInit();

    //LCD_GotoXY(0,0);

    LCD_PrintString(0, 0, "А");
    //DisplayDrawChar(0, 0, 'a');

    //DDRA |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4); // DEBUG

//    sei();
    while (1) {
//        wdt_reset();    // Reset watchdog
        //CC_Task();
        //LED_Task();
        //Battery_Task();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    //wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator

    // Setup timer
//    DelayInit();

    LCD_Init();



    // LED init
    //LED_DDR |= (1<<LED_P);

    // CC init
//    CC_Init();
//    CC_SetChannel(CORMA_CHANNEL);
//    CC_SetAddress(4);   //Never changes in CC itself

    // Setup Timer1: cycle timings
/*
    TCNT1 = 0;
    TCCR1A = 0;
    OCR1A = ((uint16_t)Corma.Addr) * PKT_DURATION;  // TX start
    ICR1 = SUBCYCLE_DURATION;                       // TX + RX/Sleep duration
    TIMSK |= (1<<OCIE1A)|(1<<TICIE1);
    CYC_TIMER_START();
*/

    // Battery
    //BatteryInit();
}

// ============================== Tasks ========================================
//void CC_Task (void) {
/*
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
*/
//}


// ============================== Events =======================================
/*
FORCE_INLINE void EVENT_NewPacket(void) {
    if (CC.RX_Pkt.CommandID == PKT_ID_CALL) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
             Count this one if did not do it yet
            bool IsCounted = false;
            for (uint8_t i=0; i<Corma.OthersCounter; i++)
                if (Corma.OtherAddr[i] == CC.RX_Pkt.SenderAddr) {
                    IsCounted = true;
                    break;
                }
            if (!IsCounted)
                Corma.OtherAddr[Corma.OthersCounter++] = CC.RX_Pkt.SenderAddr;
            
             Adjust our timer if sender address is lower, and do not otherwise
            if (CC.RX_Pkt.SenderAddr < Corma.Addr) {
                CYC_TIMER_STOP();
                Corma.CycleCounter = CC.RX_Pkt.SenderCycle;
                TCNT1 = CC.RX_Pkt.SenderTime;
                CYC_TIMER_START();
            } // if addr
        } // Atomic
    } // if PKT_ID_Call
}
void EVENT_ADCMeasureCompleted(void) {
     Choose mode of LED
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (Battery.ADCValue <= BAT_U_DISCHARGED) {
            ELED.Blink = false;
        }
        else ELED.Blink = true;
    }
}
*/

// ============================ Interrupts =====================================
// Transmit interrupt
/*
ISR(TIMER1_COMPA_vect) {
    PORTA &= ~(1<<PA4);
    PORTA |= (1<<PA3); // DEBUG
    CYC_TIMER_STOP();
     Prepare packet & transmit it
    CC.TX_Pkt.ToAddr = 0;      // Broadcast
    CC.TX_Pkt.CommandID = PKT_ID_CALL;
    CC.TX_Pkt.SenderAddr = Corma.Addr;
    CC.TX_Pkt.SenderCycle = Corma.CycleCounter;
    CC.TX_Pkt.SenderTime = TCNT1;   // No need in ATOMIC as we are in IRQ handler
    CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
    CC_EnterTX();
     Wait for packet to transmit completely
    while (!CC_GDO0_IS_HI());   // After this, SYNC word is transmitted
    while (CC_GDO0_IS_HI());    // After this, packet is transmitted
    if (Corma.CycleCounter == 0) CC_EnterRX();  // Enter RX after TX
    CYC_TIMER_START();
    PORTA &= ~(1<<PA3); // DEBUG
}

 SubCycle end interrupt
ISR(TIMER1_CAPT_vect) { // Means overflow IRQ
    PORTA |= (1<<PA1);// DEBUG
    _delay_us(500);
     Handle cycle counter
    if (++Corma.CycleCounter >= CYCLE_COUNT) {  // Zero cycle begins
        Corma.CycleCounter = 0;
         Flinch!
        MotorSetCount (Corma.OthersCounter);
        Corma.OthersCounter = 0;
         Enter RX-before-TX
        CC_EnterRX();
    }
    else CC_ENTER_IDLE();   // Non-zero cycle
    PORTA &= ~(1<<PA1);// DEBUG
}
 * Lcd_Write(CMD,0x20); // write VOP register
Lcd_Write(CMD,0x90);
Lcd_Write(CMD,0xA4); // all on/normal display
Lcd_Write(CMD,0x2F); // Power control set(charge pump on/off)
Lcd_Write(CMD,0x40); // set start row address = 0
Lcd_Write(CMD,0xb0); // set Y-address = 0
Lcd_Write(CMD,0x10); // set X-address, upper 3 bits
Lcd_Write(CMD,0x0);  // set X-address, lower 4 bits
Lcd_Write(CMD,0xC8); // mirror Y axis (about X axis)
Lcd_Write(CMD,0xa1); // Invert screen in horizontal axis
Lcd_Write(CMD,0xac); // set initial row (R0) of the display
Lcd_Write(CMD,0x07);
Lcd_Write(CMD,0xF9); //
Lcd_Write(CMD,0xaf); // display ON/OFF

Lcd_Clear(); // clear LCD
Lcd_Write(CMD,0xa7); // invert display
_delay_ms(500);                // 1/2 Sec delay
Lcd_Write(CMD,0xa6); // normal display (non inverted)
_delay_ms(1000);               // 1 Sec delay

*/

