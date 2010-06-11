/* 
 * File:   calma3c.h
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */

#ifndef _CALMA3C_H
#define	_CALMA3C_H

// ================================= Timings ===================================


// ================================= Sensors ===================================
// Timings
#define SENS_POLL_T  99 // ms
// Ports & pins
#define SENS_COLORUP      PC1
#define SENS_COLORDOWN    PC2
#define SENS_HANDLE       PC0
#define SENS_PWR          PC5
#define SENS_DDR          DDRC
#define SENS_PORT         PORTC
#define SENS_PIN          PINC

// Pseudo-functions
#define SENS_COLORUP_IS_ON()    bit_is_set (SENS_PIN, SENS_COLORUP)
#define SENS_COLORDOWN_IS_ON()  bit_is_set (SENS_PIN, SENS_COLORDOWN)
#define SENS_HANDLE_IS_ON()     bit_is_set (SENS_PIN, SENS_HANDLE)
#define SENS_PWR_OFF()  SENS_PORT &= ~(1<<SENS_PWR);
#define SENS_PWR_ON()   SENS_PORT |=  (1<<SENS_PWR);

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

// Tasks
void SENS_Task (void);
void Light_Task(void);
void CC_Task (void);

// Events
void EVENT_ColorUpTouched(void);
void EVENT_ColorUpDetouched(void);
void EVENT_ColorDownTouched(void);
void EVENT_ColorDownDetouched(void);
void EVENT_HandleTouched(void);
void EVENT_HandleDetouched(void);


#endif	/* _CALMA3C_H */

