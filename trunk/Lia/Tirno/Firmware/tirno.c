/* 
 * File:   tirno.c
 * Author: Laurelindo
 *
 * Created on 27 06 2010 г., 0:30
 */
#include <avr/io.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "tirno.h"
#include "delay_util.h"
//#include "battery.h"
#include "common.h"
//#include "cc2500.h"
#include "lcd110x.h"
#include "lcd_font.h"
#include "keys.h"

// =============================== Types =======================================
// Locket
struct Locket_t {
    uint8_t Addr;
    uint16_t Channel;
    char S[LCD_STR_WIDTH];
};
struct {
    struct Locket_t L[LOCKET_COUNT];
    uint8_t Indx;
    uint8_t TopIndx;    // Indx of locket at top of screen
} EL;


enum State_t EState;

// ============================== General ======================================
int main(void) {
    GeneralInit();

    SetState(StateList);

    uint16_t FTimer;
    bool c=true;
    //LCD_PrintString(0, 0, "Aiya Feanaro!", false);
    //LCD_DrawGauge(5);
    //LCD_GaugeValue(95);
    //DisplayDrawChar(0, 0, 'a');

    //DDRA |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4); // DEBUG

//    sei();
    while (1) {
        wdt_reset();    // Reset watchdog
        Keys_Task();
        //CC_Task();
        //LED_Task();
        //Battery_Task();

        if(DelayElapsed(&FTimer, 400)) {
            LCD_GotoXY(90, 0);
            if(c) LCD_DrawChar('*', false);
            else  LCD_DrawChar(' ', false);
            c = !c;
        }
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    //wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator

    // Init lockets
    uint16_t eeaddr = 0;
    for(uint8_t i=0; i<LOCKET_COUNT; i++) {
        eeprom_read_block(&EL.L[i], (void*)eeaddr, sizeof(struct Locket_t));
        if(EL.L[i].S[0] == 0xFF)
            EL.L[i].S[0] = 'L';
            EL.L[i].S[1] = '-';
            EL.L[i].S[2] = 'a'+i;
            EL.L[i].S[3] = 0;
        eeaddr += sizeof(struct Locket_t);
    }

    DelayInit();
    LCD_Init();
    KeysInit();
    sei();


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

// ============================ States =========================================
void SetState(enum State_t AState) {
    LCD_Clear();
    EState = AState;
    switch(AState) {
        case StateList:
            DisplayList(0); // Display list of lockets
            break;

        case StateSearch:
            LCD_PrintString(0, 0, EL.L[EL.Indx].S, false);
            LCD_PrintString_P(0, 2, PSTR("dBm:"), false);
            LCD_PrintString_P(0, 7, PSTR("Список"), true);
            LCD_DrawGauge(4);
            break;
    } // switch
}

void HandleList(void) {
    
}
void HandleSearch(void) {

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
void EVENT_KeyUp(void) {
    switch(EState) {
        case StateList: // Move down by the list
            if(EL.Indx > 0) EL.Indx--;
            if(EL.Indx < EL.TopIndx) {    // Top of screen, draw previous items
                LCD_Clear();
                DisplayList(EL.Indx-6);
            }
            else {
                LCD_PrintString(LIST_INDENT, (EL.Indx - EL.TopIndx +1), EL.L[EL.Indx+1].S, false);   // Unhighlight previous element
                LCD_PrintString(LIST_INDENT,  EL.Indx - EL.TopIndx    , EL.L[EL.Indx  ].S, true);    // Highlight current element
            }
            break;

        case StateSearch:
            break;
    } // switch
}
void EVENT_KeyDown(void) {
    switch(EState) {
        case StateList: // Move down by the list
            if(EL.Indx < LOCKET_COUNT-1) EL.Indx++;
            // Handle more than 7 lockets
            if(EL.Indx > (EL.TopIndx + 6)) {    // Bottom of screen, draw next items
                LCD_Clear();
                DisplayList(EL.Indx);
            }
            else {
                LCD_PrintString(LIST_INDENT, (EL.Indx - EL.TopIndx - 1), EL.L[EL.Indx-1].S, false);  // Unhighlight previous element
                LCD_PrintString(LIST_INDENT,  EL.Indx - EL.TopIndx     , EL.L[EL.Indx  ].S, true);   // Highlight current element
            }
            break;

        case StateSearch:
            break;
    } // switch
}
void EVENT_KeyLeft(void) {
    switch(EState) {
        case StateList:
            // Blink button
            LCD_PrintString_P(0, 7, PSTR("     "), false);
            _delay_ms(150);
            LCD_PrintString_P(0, 7, PSTR("Поиск"), true);
            _delay_ms(200);
            SetState(StateSearch);
            break;
        case StateSearch:
            // Blink button
            LCD_PrintString_P(0, 7, PSTR("      "), false);
            _delay_ms(150);
            LCD_PrintString_P(0, 7, PSTR("Список"), true);
            _delay_ms(200);
            SetState(StateList);
            break;
    } // switch
}
void EVENT_KeyRight(void) {

}

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

*/

// ============================= Inner use =====================================
void DisplayList(uint8_t StartElement) {
    uint8_t i = StartElement;
    EL.TopIndx = StartElement;
    for(uint8_t y=0; y<LCD_STR_HEIGHT-1; y++) { // -1, because we need place for menu
        if(i >= LOCKET_COUNT) break;
        LCD_PrintUint(0, y, i);
        LCD_PrintString(LIST_INDENT, y, EL.L[i].S, (i==EL.Indx));
        i++;
    }
    // Display pseudo-buttons
    LCD_PrintString_P(0, 7, PSTR("Поиск"), true);
    LCD_PrintString_P(66, 7, PSTR("Опции"), true);
}
