/* 
 * File:   calma3c.h
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */

#ifndef _CALMA3C_H
#define	_CALMA3C_H

// =============================== General =====================================
#define PKT_ID0_CALE    0xCA
#define PKT_ID1_CALE    0x1E

// ============================== CC timings ===================================
#define CC_RX_ON_DELAY      54 // ms
#define CC_RX_OFF_DELAY     216 // ms

// ================================== Light ====================================
// Timings
#define LED_STEP_DELAY  4  // ms

// Ports & pins
#define LED_DDR     DDRD
#define LED_PORT    PORTD
#define RED_P       PD6
#define GREEN_P     PD5
#define BLUE_P      PD3

#define LED_RED_DISABLE()   TCCR0A &= ~((1<<COM0A1)|(1<<COM0A0));
#define LED_RED_ENABLE()    TCCR0A |=  ((1<<COM0A1)|(0<<COM0A0));
#define LED_GREEN_DISABLE() TCCR0A &= ~((1<<COM0B1)|(1<<COM0B0));
#define LED_GREEN_ENABLE()  TCCR0A |=  ((1<<COM0B1)|(0<<COM0B0));
#define LED_BLUE_DISABLE()  TCCR2A &= ~((1<<COM2B1)|(1<<COM2B0));
#define LED_BLUE_ENABLE()   TCCR2A |=  ((1<<COM2B1)|(0<<COM2B0));


// =============================== Prototypes ==================================
// General
void GeneralInit(void);

void SetDesiredColor (uint8_t ARed, uint8_t AGreen, uint8_t ABlue);

// Tasks
void Light_Task(void);
void CC_Task (void);

// Events
void EVENT_NewPacket(void);

#endif	/* _CALMA3C_H */

