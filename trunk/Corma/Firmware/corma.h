/* 
 * File:   calma3c.h
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */

#ifndef _CALMA3C_H
#define	_CALMA3C_H

// =============================== General =====================================
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
#define PKT_DURATION        360     // tics: experimental result, 21 ms
#define SUBCYCLE_DURATION   3960    // 251.7 ms

// ================================== Light ====================================
// Timings
#define LED_STEP_DELAY  36  // ms

// Ports & pins
#define LED_DDR     DDRD
#define LED_PORT    PORTD


// =============================== Prototypes ==================================
// General
void GeneralInit(void);
void NewSubcycle(void);

// Tasks
void CC_Task (void);


// Events
void EVENT_NewPacket(void);

#endif	/* _CALMA3C_H */

