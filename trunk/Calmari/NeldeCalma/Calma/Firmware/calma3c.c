/* 
 * File:   calma3c.c
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */
#include <avr/io.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include "calma3c.h"
#include "time_utils.h"
#include "../../cc_common/common.h"
#include "../../cc_common/cc2500.h"

#include "uart_soft.h"

// ============================= Types =========================================
struct Color_t {
    uint8_t Red, Green, Blue;
};
struct {
    uint16_t Timer;
    struct Color_t DesiredColor, CurrentColor;
} ELight;
struct {
    uint16_t Timer;
    bool JustEnteredRX;
    bool DeepSleep;
} CC_Srv;

// ============================== General ======================================
int main(void) {
    GeneralInit();

    UARTInit();

    UARTSendString_P(PSTR("Calma is here\r"));

    //SetDesiredColor (50, 50, 50);

    sei(); 
    while (1) {
        wdt_reset();    // Reset watchdog
        Light_Task ();
        CC_Task();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    wdt_enable(WDTO_2S);
    ACSR = 1<<ACD;  // Disable analog comparator
    // Setup timer
    TimerInit();    // Time counter

    // Light
    LED_DDR  |=   (1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P);
    LED_PORT &= ~((1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P));
    TCCR0A = (1<<WGM01)|(1<<WGM00);
    TCCR0B = (0<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00);  // 1 MHz/8 = 125 kHz of timer infut freq. 125 kHz/255 = 490 Hz of PWM freq.
    TCCR2A = (1<<WGM21)|(1<<WGM20);
    TCCR2B = (0<<WGM22)|(0<<CS22)|(1<<CS21)|(0<<CS20);
    TimerResetDelay(&ELight.Timer);

    // CC init
    CC_Srv.JustEnteredRX = false;
    CC_Srv.DeepSleep = false;
    TimerResetDelay(&CC_Srv.Timer);
    CC_Init();
    CC_SetAddress(4);   //Never changes in CC itself
}

FORCE_INLINE void SetDesiredColor (uint8_t ARed, uint8_t AGreen, uint8_t ABlue) {
    ELight.DesiredColor.Red   = ARed;
    ELight.DesiredColor.Green = AGreen;
    ELight.DesiredColor.Blue  = ABlue;
}

// ============================== Tasks ========================================
void Light_Task(void) {
    if (!TimerDelayElapsed(&ELight.Timer, LED_STEP_DELAY)) return;
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

void CC_Task (void) {
    // Handle packet if received
    if (CC.NewPacketReceived) {
        CC.NewPacketReceived = false;
        EVENT_NewPacket();
    }

    // If in sleep mode, check if it is time to wake-up; otherwise return
    if (CC_Srv.DeepSleep) {
        if (TimerDelayElapsed(&CC_Srv.Timer, CC_RX_OFF_DELAY)) CC_Srv.DeepSleep = false;
        else return;
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

        case CC_STB_IDLE:   // Idle mode means that CC just has awaken
            CC_ENTER_RX();
            CC_Srv.JustEnteredRX = true;
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
                    CC_POWERDOWN();
                    CC_Srv.DeepSleep = true;
                }// if timer
            }// if not RX
            break;

        default: // Just get out in case of RX, TX, FSTXON, CALIBRATE, SETTLING
            break;
    }//Switch
}


// ============================== Events =======================================
FORCE_INLINE void EVENT_NewPacket(void) {
    if ((CC.RX_Pkt.CommandID == PKT_ID0_CALE) && (CC.RX_Pkt.Data[0] == PKT_ID1_CALE)) {
        SetDesiredColor(CC.RX_Pkt.Data[1], CC.RX_Pkt.Data[2], CC.RX_Pkt.Data[3]);
    } // if PKT_ID_Color
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


}

