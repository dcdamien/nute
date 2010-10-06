/* 
 * File:   tirno.h
 * Author: Laurelindo
 *
 * Created on 24.9.2010
 */

#ifndef _TIRNO_H
#define	_TIRNO_H

#include <avr/io.h>
#include <inttypes.h>

// =============================== General =====================================
#define LOCKET_COUNT        9
#define PKT_ID_CALL         0xCA

#define CORMA_CHANNEL       7
#define EE_CORMA_ADDRESS    (uint8_t*)4
#define MAX_OTHERS_COUNT    10

// ================================== Timer ====================================
// Divider = 64
#define TCCR1B_ON   (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(1<<CS01)|(1<<CS00)
#define TCCR1B_OFF  (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(0<<CS01)|(0<<CS00)

#define CYC_TIMER_START()    TCCR1B = TCCR1B_ON
#define CYC_TIMER_STOP()     TCCR1B = TCCR1B_OFF

#define CYCLE_COUNT         4
#define PKT_DURATION        504
//#define SUBCYCLE_DURATION   3960    // 251.7 ms
#define SUBCYCLE_DURATION   5040    // 322 ms

// ================================== Light ====================================
#define LED_DDR   DDRC
#define LED_PORT  PORTC
#define LED_P     PC6

#define LED_ON()  LED_PORT |=  (1<<LED_P)
#define LED_OFF() LED_PORT &= ~(1<<LED_P)

#define LED_ON_PERIOD   99 // ms
#define LED_OFF_PERIOD  999 // ms

// =============================== Types =======================================
// States
enum State_t {StateList, StateSearch};


// =============================== Prototypes ==================================
// General
void GeneralInit(void);

void SetState(enum State_t);

// Inner use
void DisplayList(uint8_t StartElement);

// Tasks
void CC_Task (void);
void LED_Task(void);

// Events
void EVENT_NewPacket(void);
// Keys
void EVENT_KeyUp(void);
void EVENT_KeyDown(void);
void EVENT_KeyLeft(void);
void EVENT_KeyRight(void);


#endif	/* _CALMA3C_H */

