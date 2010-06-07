/* 
 * File:   calma3c.c
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */
#include <avr/io.h>
#include <stdbool.h>
#include "calma3c.h"
#include "time_utils.h"

struct {
    uint16_t Timer;//, DurationTimer;
    bool IsDown;
    //bool IsMeasuringDelay;
} EKey;

int main(void) {
    // Setup hardware
    ACSR = 1<<ACD;  // Disable analog comparator
    // Setup pins
    DDRD  = (1<<PWM_RED)|(1<<PWM_GREEN)|(1<<PWM_BLUE)|(0<<SENSOR_OUT);
    PORTD = (0<<PWM_RED)|(0<<PWM_GREEN)|(0<<PWM_BLUE)|(1<<SENSOR_OUT);
    // Setup timer
    TimerInit();    // Time counter
    // Init key
    EKey.IsDown = false;
    TimerResetDelay (&EKey.Timer);

    sei(); 

    while (1) {
        Key_Task ();
        //Light_Task ();
        //Sleep_Task ();
    } // while
}

void Key_Task (void) {
    // ====== Check button when needed ======
    if (TimerDelayElapsed (&EKey.Timer, KEY_POLL_T)) {
        if (!EKey.IsDown && KEY_IS_DOWN) {     // Keypress occured
            EKey.IsDown = true;
            KeyPress_Event ();
        } // if keypress occured

        else if (EKey.IsDown && !KEY_IS_DOWN) { // Key depress occured
            EKey.IsDown = false;
            //KeyDepress_Event ();
        } // if depress occured
    } // if timeout
}


void KeyPress_Event (void) {
    LED_TOGGLE;
}


/* void KeyDepress_Event (void) {
}
*/
