/* 
 * File:   calma3c.h
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */

#ifndef _CALMA3C_H
#define	_CALMA3C_H

#include <avr/io.h>

// ================================== Light ====================================
// Timings
#define LED_STEP_DELAY  36  // ms

// Ports & pins
#define LED_DDR     DDRD
#define LED_PORT    PORTD
#define LED_P       PD6

#define LED_DISABLE()   TCCR0A &= ~((1<<COM0A1)|(1<<COM0A0));
#define LED_ENABLE()    TCCR0A |=  ((1<<COM0A1)|(0<<COM0A0));

// Switch
#define SW_DDR      DDRC
#define SW_PORT     PORTC
#define SW_PIN      PINC
#define SW_P        PC0

#define SW_IS_ON()  bit_is_clear(SW_PIN, SW_P)

#define SW_DELAY    200

// =============================== Prototypes ==================================
// General
void GeneralInit(void);

// Tasks
void Light_Task(void);
void Switch_Task(void);

// Events
void EVENT_SwitchOn(void);
void EVENT_SwitchOff(void);

#endif	/* _CALMA3C_H */

