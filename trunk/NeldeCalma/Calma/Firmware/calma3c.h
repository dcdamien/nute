/* 
 * File:   calma3c.h
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */

#ifndef _CALMA3C_H
#define	_CALMA3C_H

// =============================== General =====================================
#define PKT_ID_COLOR    0xC0

// ============================== CC timings ===================================
#define CC_RX_ON_DELAY      54 // ms
#define CC_RX_OFF_DELAY     216 // ms

// ================================== Light ====================================
// Timings
#define LED_STEP_DELAY  72  // ms
// PWM
#define RED_PWM_MAX     150
#define GREEN_PWM_MAX   150
#define BLUE_PWM_MAX    150

// Ports & pins
#define L_DDR       DDRD
#define RED_P       PD6
#define GREEN_P     PD5
#define BLUE_P      PD3

#define LED_PWR_P       PB7
#define LED_PWR_DDR     DDRB
#define LED_PWR_PORT    PORTB
#define LED_PWR_ON()    LED_PWR_PORT &= ~(1<<LED_PWR_P)
#define LED_PWR_OFF()   LED_PWR_PORT |=  (1<<LED_PWR_P)

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

