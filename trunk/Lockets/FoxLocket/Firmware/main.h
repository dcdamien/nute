/* 
 * File:   main.h
 * Author: Kreyl Laurelindo
 *
 * Created on 7 Апрель 2010 г., 19:44
 */

#ifndef _MAIN_H
#define	_MAIN_H

#include <avr/io.h>

#include "cc1101.h"

#define EE_ADDRESS  (uint8_t*)(4)

// ================================= Defines ===================================
#define MOTOR_DDR   DDRD
#define MOTOR_PORT  PORTD
#define MOTOR_P     PD4

#define MAX_COUNT_TO_FLINCH 4
// Motor timings, ms
#define MOTOR_ON_TIME       25
#define MOTOR_OFF_TIME      150


// ================================= Timings ===================================
// Divider = 64
#define TCCR1B_ON   (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(1<<CS01)|(1<<CS00)
#define TCCR1B_OFF  (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(0<<CS01)|(0<<CS00)

#define TIM1_STOP()     TCCR1B = TCCR1B_OFF
#define TIM1_START()    TCCR1B = TCCR1B_ON

#define TIMER_MULTI     8       // i.e. multiply by 256
#define CYCLE_DURATION  3125    // 200 ms
#define PKT_DURATION    131     // tics: experimental result

// =============================== Packet info =================================
#define PKT_ID_CALL     0xCA

// ================================ Pseudo functions ===========================
#define TIMER_ADJUST(AlienAddr) ATOMIC_BLOCK(ATOMIC_RESTORESTATE){\
                                    TIM1_STOP();\
                                    TCNT1 = (((uint16_t)AlienAddr) << TIMER_MULTI) + PKT_DURATION;\
                                    TIM1_START();\
                                } // atomic

#define MOTOR_ON()  MOTOR_PORT &= ~(1<<MOTOR_P)
#define MOTOR_OFF() MOTOR_PORT |=  (1<<MOTOR_P)

// =============================== Prototypes ==================================
void GeneralInit(void);

void Motor_TASK(void);
void Packet_TASK(void);

#endif	/* _MAIN_H */

