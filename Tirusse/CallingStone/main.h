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

// ================================= Defines ===================================
#define LED_DDR   DDRC
#define LED_PORT  PORTC
#define LED_P     PC6

#define EE_ADDRESS  (uint8_t*)(4) 

// ================================= Timings ===================================
// Divider = 64
#define TCCR1B_ON   (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(1<<CS01)|(1<<CS00)
#define TCCR1B_OFF  (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(0<<CS01)|(0<<CS00)

#define TIM1_STOP()     TCCR1B = TCCR1B_OFF
#define TIM1_START()    TCCR1B = TCCR1B_ON

// =============================== Packet info =================================
#define PKT_ID_CALL     0xCA

// ================================ Pseudo functions ===========================
#define LED_ON()  LED_PORT &= ~(1<<LED_P)
#define LED_OFF() LED_PORT |=  (1<<LED_P)

// =============================== Prototypes ==================================
void GeneralInit(void);

#endif	/* _MAIN_H */

