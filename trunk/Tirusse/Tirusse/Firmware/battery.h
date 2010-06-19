/* 
 * File:   battery.h
 * Author: Kreyl Laurelindo
 *
 * Created on 9 Июнь 2010 г., 23:43
 */

#ifndef _BATTERY_H
#define	_BATTERY_H

#include <avr/io.h>

// ============================== Defins =======================================
#define BAT_CHRG_P      PB1
#define BAT_CHRG_DDR    DDRB
#define BAT_CHRG_PORT   PORTB
#define BAT_CHRG_PIN    PINB

#define BAT_POLL_PERIOD 500 // ms

// ============================== Types ========================================
struct Battery_t {
    uint16_t Timer;
    bool IsCharging;
};
extern struct Battery_t Battery;

// ============================ Prototypes =====================================
void Battery_Task (void);

void BatteryInit(void);

void EVENT_ChargeStarted(void);
void EVENT_ChargeEnded(void);

#endif	/* _BATTERY_H */

