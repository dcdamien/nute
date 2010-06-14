/* 
 * File:   calma3c.c
 * Author: Laurelindo
 *
 * Created on 20 2009 Рі., 0:16
 */
#include <avr/io.h>
#include <inttypes.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include "olwen.h"
#include "time_utils.h"
#include "common.h"
#include "../../cc_common/cc2500.h"
#include "color_table.h"

// ============================= Types =========================================
struct {
    bool UpIsOn, DownIsOn, HandleIsOn, BothIsOn;
    uint16_t Timer, HoldTimer;
} ESens;

struct Color_t {
    uint8_t Red, Green, Blue;
};
struct {
    uint16_t Timer;
    struct Color_t DesiredColor, CurrentColor;
    uint8_t Indx;
} ELight;

bool MustShutdown;

// ============================== General ======================================
int main(void) {
    GeneralInit();
    MustShutdown = false;

    sei(); 
    while (1) {
        wdt_reset();    // Reset watchdog
        CC_Task();
        SENS_Task ();
        Light_Task ();
        //Sleep_Task ();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    // Setup timer
    TimerInit();    // Time counter

    // Light
    LED_DDR  |= (1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P);
    LED_PORT &= ~((1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P));
    LED_PWR_DDR |= (1<<LED_PWR_P);
    LED_PWR_OFF();

    TCCR0A = (1<<WGM01)|(1<<WGM00);
    TCCR0B = (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);
    TCCR2A = (1<<WGM21)|(1<<WGM20);
    TCCR2B = (0<<WGM22)|(0<<CS22)|(0<<CS21)|(1<<CS20);
    TimerResetDelay(&ELight.Timer);
    ELight.Indx = 0;
    
    // Sensors
    SENS_DDR  &= ~((1<<SENS_DOWN)|(1<<SENS_UP)|(1<<SENS_HANDLE));
    SENS_DDR  |= 1<<SENS_PWR;
    SENS_PORT &= ~((1<<SENS_DOWN)|(1<<SENS_UP)|(1<<SENS_HANDLE)); // No pull-ups
    SENS_PWR_OFF();
    ESens.DownIsOn   = false;
    ESens.UpIsOn     = false;
    ESens.HandleIsOn = false;
    ESens.BothIsOn   = false;
    TimerResetDelay (&ESens.Timer);

    // CC init
    CC_Init();
    //CC_SetAddress(4);   //Never changes in CC itself
}

FORCE_INLINE void SetDesiredColor (uint8_t ARed, uint8_t AGreen, uint8_t ABlue) {
    ELight.DesiredColor.Red   = ARed;
    ELight.DesiredColor.Green = AGreen;
    ELight.DesiredColor.Blue  = ABlue;
}
void SetTableColor (uint8_t AIndx) {
    ELight.DesiredColor.Red   = pgm_read_byte(&ColorTable[AIndx][0]);
    ELight.DesiredColor.Green = pgm_read_byte(&ColorTable[AIndx][1]);
    ELight.DesiredColor.Blue  = pgm_read_byte(&ColorTable[AIndx][2]);
}


// ============================== Tasks ========================================
void SENS_Task (void) {
    if (!TimerDelayElapsed (&ESens.Timer, SENS_POLL_T)) return;
    // Up sensor
    if (!ESens.UpIsOn && SENS_UP_IS_ON()) {     // Touch occured
        ESens.UpIsOn = true;
        if (ESens.DownIsOn) {                   // DOWN is on hold
            ESens.BothIsOn = true;
            EVENT_BothTouched();
        }
        else EVENT_UpTouched();
    }
    else if (ESens.UpIsOn && !SENS_UP_IS_ON()) {// Detouch occured
        ESens.UpIsOn   = false;
        ESens.BothIsOn = false;
    }
    // Down sensor
    if (!ESens.DownIsOn && SENS_DOWN_IS_ON()) { // Touch occured
        ESens.DownIsOn = true;
        if (ESens.UpIsOn) {                     // UP is on hold
            ESens.BothIsOn = true;
            EVENT_BothTouched();
        }
        else EVENT_DownTouched();
    }
    else if (ESens.DownIsOn && !SENS_DOWN_IS_ON()) {    // Detouch occured
        ESens.DownIsOn = false;
        ESens.BothIsOn = false;
    }
    // Handle sensor
    if (!ESens.HandleIsOn && SENS_HANDLE_IS_ON()) {
        ESens.HandleIsOn = true;
        EVENT_HandleTouched();
    }
    else if (ESens.HandleIsOn && !SENS_HANDLE_IS_ON()) {
        ESens.HandleIsOn = false;
    }

    // Holding handlers
    if (ESens.DownIsOn && !ESens.BothIsOn)
        if (TimerDelayElapsed(&ESens.HoldTimer, SENS_HOLD_TICK_TIMEOUT)) EVENT_DownHoldTick();
    if (ESens.UpIsOn && !ESens.BothIsOn)
        if (TimerDelayElapsed(&ESens.HoldTimer, SENS_HOLD_TICK_TIMEOUT)) EVENT_UpHoldTick();
}

void Light_Task(void) {
//    if (!TimerDelayElapsed(&ELight.Timer, LED_STEP_DELAY)) return;
    // Red channel
    if (ELight.CurrentColor.Red != ELight.DesiredColor.Red) {
        if (ELight.DesiredColor.Red < ELight.CurrentColor.Red) {
            ELight.CurrentColor.Red--;
            if (ELight.CurrentColor.Red == 0) LED_RED_DISABLE();
        }
        else {
            if (ELight.CurrentColor.Red == 0) LED_RED_ENABLE();
            ELight.CurrentColor.Red++;
        }
        OCR0A = ELight.CurrentColor.Red;
    }
    // Green channel
    if (ELight.CurrentColor.Green != ELight.DesiredColor.Green) {
        if (ELight.DesiredColor.Green < ELight.CurrentColor.Green) {
            ELight.CurrentColor.Green--;
            if (ELight.CurrentColor.Green == 0) LED_GREEN_DISABLE();
        }
        else {
            if (ELight.CurrentColor.Green == 0) LED_GREEN_ENABLE();
            ELight.CurrentColor.Green++;
        }
        OCR0B = ELight.CurrentColor.Green;
    }
    // Blue channel
    if (ELight.CurrentColor.Blue != ELight.DesiredColor.Blue) {
        if (ELight.DesiredColor.Blue < ELight.CurrentColor.Blue) {
            ELight.CurrentColor.Blue--;
            if (ELight.CurrentColor.Blue == 0) LED_BLUE_DISABLE();
        }
        else {
            if (ELight.CurrentColor.Blue == 0) LED_BLUE_ENABLE();
            ELight.CurrentColor.Blue++;
        }
        OCR2B = ELight.CurrentColor.Blue;
    }
}

void CC_Task (void){
    // Do with CC what needed
    CC_GET_STATE();
    switch (CC.State) {
        case CC_STB_RX_OVF:
            CC_FLUSH_RX_FIFO();
            break;
        case CC_STB_TX_UNDF:
            CC_FLUSH_TX_FIFO();
            break;

        case CC_STB_IDLE:
            // Transmit at once if IDLE
            // Prepare CALL packet
            CC.TX_Pkt.Address = 0;     // Broadcast
            CC.TX_Pkt.PacketID = 0;    // Current packet ID, to avoid repeative treatment
            CC.TX_Pkt.CommandID = 0xC0;// SetColor packet
            CC.TX_Pkt.Data[0] = ELight.DesiredColor.Red;   // }
            CC.TX_Pkt.Data[1] = ELight.DesiredColor.Green; // }
            CC.TX_Pkt.Data[2] = ELight.DesiredColor.Blue;  // } components of color

            CC_WriteTX (&CC.TX_PktArray[0], CC_PKT_LENGTH); // Write bytes to FIFO
            CC_ENTER_TX();
            break;

        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}


// ============================== Events =======================================
void EVENT_UpTouched(void) {
    SetTableColor(ELight.Indx++);
    if (ELight.Indx >= COLOR_COUNT) ELight.Indx = 0;
    // Reset hold timer
    TimerResetDelay(&ESens.HoldTimer);
}
void EVENT_UpDetouched(void) {
    
}
void EVENT_DownTouched(void) {

}
void EVENT_DownDetouched(void) {
     
}

void EVENT_HandleTouched(void) {
    SENS_PWR_ON();
}
void EVENT_HandleDetouched(void) {
    SENS_PWR_OFF();
}

void EVENT_DownHoldTick(void) { // Fires every N ms when Down is holded
    // Check if both sensors are holded
    if (ESens.UpIsOn && ESens.DownIsOn) {

    }
}
void EVENT_UpHoldTick(void) { // Fires every N ms when Up is holded
    
}
