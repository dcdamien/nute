/* 
 * File:   calma3c.h
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */

#ifndef _CALMA3C_H
#define	_CALMA3C_H

// =============================== General =====================================
#define PKT_ID_CALL_HI  0xCA
#define PKT_ID_CALL_LO  0x11

#define CORMA_CHANNEL       7
#define EE_CORMA_ADDRESS    (uint8_t*)4




// ============================== CC timings ===================================
#define CC_RX_ON_DELAY      54 // ms
#define CC_RX_OFF_DELAY     108 // ms

// ================================== Light ====================================
// Timings
#define LED_STEP_DELAY  36  // ms

// Ports & pins
#define LED_DDR     DDRD
#define LED_PORT    PORTD


// =============================== Prototypes ==================================
// General
void GeneralInit(void);

// Tasks
void CC_Task (void);

// Events
void EVENT_NewPacket(void);

#endif	/* _CALMA3C_H */

