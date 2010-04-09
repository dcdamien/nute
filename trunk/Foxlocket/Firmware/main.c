/*
 * File:   main.c of FoxLocket project
 * Author: Laurelindo
 *
 * Created on 2010.04.07
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include "main.h"
#include "uart_unit.h"
#include "cc1101.h"
#include "ledskeys.h"
#include "time_utils.h"

#include "random.h"

int main(void) {
    LEDKeyInit();
    _delay_ms(270);
    UARTInit();
    UARTNewLine();
    UARTSendString_P(PSTR("Foxlocket started\r"));

    TimerInit();
    CC_Init();
    RandomStart();

    uint16_t MainTimer;
    TimerResetDelay(&MainTimer);

    sei();

    // Main cycle
    while (1){
        if (TimerDelayElapsed(&MainTimer, 500)){
/*
            if (ERandom.IsReady){
                UARTNewLine();
                //UARTSendAsHex(ERandom.Random, true);
                UARTSendAsHex(ADCL, true);
                RandomStart();
            }
*/
//            uint8_t b=CC_ReadRegister(CC_MARCSTATE);
            uint8_t b=CC_ReadRegister(CC_RSSI);
            UARTSendUint(b);
            UARTNewLine();

            if (b==CC_ST_RX_OVERFLOW){
                CC_ENTER_IDLE();
                _delay_ms(100);
                CC_FLUSH_RX_FIFO();
                _delay_ms(100);
                CC.State = CC_Idle;
            }

            else CC.NeededState = CC_RX;
        } // if delay

        CC_Task();
/*
            if (BTN1_IS_DOWN()){
                CC_PreparePacket();
                CC_TransmitPacket();
            }
*/

    } // while 1
}


