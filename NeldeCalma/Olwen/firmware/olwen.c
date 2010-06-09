/* 
 * File:   calma3c.c
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */
#include <avr/io.h>
#include <stdbool.h>
#include "olwen.h"
#include "time_utils.h"
#include "common.h"

// ============================= Types =========================================
struct {
    bool ColorUpIsOn, ColorDownIsOn, HandleIsOn;
    uint16_t Timer;//, DurationTimer;
    //bool IsMeasuringDelay;
    
} ESens;

struct Color_t {
    uint8_t Red, Green, Blue;
};
struct {
    uint16_t Timer;
    struct Color_t DesiredColor, CurrentColor, SavedColor;
} ELight;


// ============================== General ======================================
int main(void) {
    GeneralInit();

    sei(); 

    while (1) {
        SENS_Task ();
        Light_Task ();
        //Sleep_Task ();
    } // while
}

FORCE_INLINE void GeneralInit(void) {
    // Setup hardware
    ACSR = 1<<ACD;  // Disable analog comparator
    
    // Light
    L_DDR  = (1<<RED_P)|(1<<GREEN_P)|(1<<BLUE_P);
    TCCR0A = (1<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(1<<WGM00);
    TCCR0B = (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);
    TCCR2A = (0<<COM2A1)|(0<<COM2A0)|(1<<COM2B1)|(0<<COM2B0)|(1<<WGM21)|(1<<WGM20);
    TCCR2B = (0<<WGM22)|(0<<CS22)|(0<<CS21)|(1<<CS20);
    ELight.DesiredColor.Red = 0;
    ELight.DesiredColor.Green = 108;
    ELight.DesiredColor.Blue = 0;
    TimerResetDelay(&ELight.Timer);
    
    // Setup timer
    TimerInit();    // Time counter

    // Sensors
    SENS_DDR  &= ~((1<<SENS_COLORDOWN)|(1<<SENS_COLORUP)|(1<<SENS_HANDLE));
    SENS_DDR  |= 1<<SENS_PWR;
    SENS_PORT &= ~((1<<SENS_COLORDOWN)|(1<<SENS_COLORUP)|(1<<SENS_HANDLE)); // No pull-ups
    SENS_PWR_OFF();
    ESens.ColorDownIsOn = false;
    ESens.ColorUpIsOn = false;
    ESens.HandleIsOn = false;
    TimerResetDelay (&ESens.Timer);
}

// ============================== Tasks ========================================
void SENS_Task (void) {
    if (!TimerDelayElapsed (&ESens.Timer, SENS_POLL_T)) return;
    
    if (!ESens.ColorUpIsOn && SENS_COLORUP_IS_ON()) {
        ESens.ColorUpIsOn = true;
        EVENT_ColorUpTouched();
    }
    else if (ESens.ColorUpIsOn && !SENS_COLORUP_IS_ON()) {
        ESens.ColorUpIsOn = false;
        EVENT_ColorUpDetouched();
    }

    if (!ESens.ColorDownIsOn && SENS_COLORDOWN_IS_ON()) {
        ESens.ColorDownIsOn = true;
        EVENT_ColorDownTouched();
    }
    else if (ESens.ColorDownIsOn && !SENS_COLORDOWN_IS_ON()) {
        ESens.ColorDownIsOn = false;
        EVENT_ColorDownDetouched();
    }

    if (!ESens.HandleIsOn && SENS_HANDLE_IS_ON()) {
        ESens.HandleIsOn = true;
        EVENT_HandleTouched();
    }
    else if (ESens.HandleIsOn && !SENS_HANDLE_IS_ON()) {
        ESens.HandleIsOn = false;
        EVENT_HandleDetouched();
    }
}

void Light_Task(void) {
    if (!TimerDelayElapsed(&ELight.Timer, LED_STEP_DELAY)) return;
    // Red channel
    if (ELight.CurrentColor.Red != ELight.DesiredColor.Red) {
        if (ELight.DesiredColor.Red < ELight.CurrentColor.Red) ELight.CurrentColor.Red--;
        else                                                   ELight.CurrentColor.Red++;
        OCR0A = ELight.CurrentColor.Red;
    }
    // Green channel
    if (ELight.CurrentColor.Green != ELight.DesiredColor.Green) {
        if (ELight.DesiredColor.Green < ELight.CurrentColor.Green) ELight.CurrentColor.Green--;
        else                                                       ELight.CurrentColor.Green++;
        OCR0B = ELight.CurrentColor.Green;
    }
    // Blue channel
    if (ELight.CurrentColor.Blue != ELight.DesiredColor.Blue) {
        if (ELight.DesiredColor.Blue < ELight.CurrentColor.Blue) ELight.CurrentColor.Blue--;
        else                                                     ELight.CurrentColor.Blue++;
        OCR2B = ELight.CurrentColor.Blue;
    }
}

// ============================== Events =======================================
void EVENT_ColorUpTouched(void) {

}
void EVENT_ColorUpDetouched(void) {

}
void EVENT_ColorDownTouched(void) {

}
void EVENT_ColorDownDetouched(void) {

}

void EVENT_HandleTouched(void) {
    SENS_PWR_ON();
}
void EVENT_HandleDetouched(void) {
    SENS_PWR_OFF();
}





/* void KeyDepress_Event (void) {
}
*/
