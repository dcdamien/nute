/* 
 * File:   main.h of Tirusse
 * Author: Kreyl Laurelindo
 *
 * Created on 7 Апрель 2010 г., 19:44
 */

#ifndef _MAIN_H
#define	_MAIN_H

#include <avr/io.h>
#include "../cc_common/cc1101.h"

// ================================= Defines ===================================
#define LED_DDR   DDRC
#define LED_PORT  PORTC
#define LED_P     PC6

#define EE_ADDRESS  (uint8_t*)(4) 

// ================================= Timings ===================================
#define CC_RX_ON_DELAY      18 // ms
#define CC_RX_OFF_DELAY     108 // ms

#define DETECTOR_TIMEOUT    3996 // ms

// =============================== Packet info =================================
#define PKT_ID_CALL     0xCA

// ================================ Pseudo functions ===========================
#define LED_ON()  LED_PORT |=  (1<<LED_P)
#define LED_OFF() LED_PORT &= ~(1<<LED_P)

// =============================== Prototypes ==================================
void GeneralInit(void);
void CC_Task (void);
void Stone_Task(void);

void LED_Task(void);
void EVENT_Detected(void);
void EVENT_Hide(void);
void EVENT_NewPacket(void);

#endif	/* _MAIN_H */

