/* 
 * File:   calma3c.h
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */

#ifndef _CALMA3C_H
#define	_CALMA3C_H

#include <avr/io.h>
#include <inttypes.h>

// =============================== General =====================================
#define PKT_ID0_CALE    0xCA
#define PKT_ID1_CALE    0x1E

// ================================= Sensors ===================================
// Timings
#define SENS_POLL_TIME  99 // ms
#define SENS_BOTHDOWN_IGNORE_TIME    999 // ms
#define SENS_HOLD_TICK_TIMEOUT  999 //ms

// Ports & pins
#define SENS_UP     PC1
#define SENS_DOWN   PC2
#define SENS_HANDLE PC0
#define SENS_PWR    PC5
#define SENS_DDR    DDRC
#define SENS_PORT   PORTC
#define SENS_PIN    PINC

// IRQ
#define HANDLE_IRQ_SETUP_MASK() PCMSK1 |=  (1<<PCINT8)
#define HANDLE_IRQ_ENABLE()     PCICR  |=  (1<<PCIE1)   // Handle at PC0 == PCINT8 => PCIE1
#define HANDLE_IRQ_DISABLE()    PCICR  &= ~(1<<PCIE1)
#define HANDLE_IRQ_CLEAR()      PCIFR  |=  (1<<PCIF1)

// Pseudo-functions
#define SENS_UP_IS_ON()     bit_is_set (SENS_PIN, SENS_UP)
#define SENS_DOWN_IS_ON()   bit_is_set (SENS_PIN, SENS_DOWN)
#define SENS_HANDLE_IS_ON() bit_is_set (SENS_PIN, SENS_HANDLE)
#define SENS_PWR_OFF()      SENS_PORT &= ~(1<<SENS_PWR);
#define SENS_PWR_ON()       SENS_PORT |=  (1<<SENS_PWR);

// ================================== Light ====================================
// Timings
#define LED_STEP_DELAY  4  // ms
// "Shutdown" color
#define CLR_SHDN_RED    0
#define CLR_SHDN_GREEN  0
#define CLR_SHDN_BLUE   7

// Ports & pins
#define LED_DDR     DDRD
#define LED_PORT    PORTD
#define RED_P       PD6
#define GREEN_P     PD5
#define BLUE_P      PD3

#define LED_PWR_P       PB7
#define LED_PWR_DDR     DDRB
#define LED_PWR_PORT    PORTB
#define LED_PWR_ON()    LED_PWR_DDR |=  (1<<LED_PWR_P)
#define LED_PWR_OFF()   LED_PWR_DDR &= ~(1<<LED_PWR_P)

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
void SetTableColor (void);

// Tasks
void SENS_Task (void);
void Light_Task(void);
void CC_Task (void);
void Sleep_Task (void);

// Events
void EVENT_UpTouched(void);
void EVENT_DownTouched(void);
void EVENT_BothTouched(void);

void EVENT_HandleTouched(void);
void EVENT_HandleDetouched(void);

void EVENT_DownHoldTick(void);
void EVENT_UpHoldTick(void);

#endif	/* _CALMA3C_H */

