/* 
 * File:   main.h of Tirusse
 * Author: Kreyl Laurelindo
 *
 * Created on 7 Апрель 2010 г., 19:44
 */

#ifndef _MAIN_H
#define	_MAIN_H

#include <avr/io.h>
#include <inttypes.h>
#include <stdbool.h>

// ================================= LED =======================================
//#define LED_DEBUG

#ifdef LED_DEBUG
#define LED_DDR   DDRC
#define LED_PORT  PORTC
#define LED_P     PC6
#define LED_ON()  LED_PORT |=  (1<<LED_P)
#define LED_OFF() LED_PORT &= ~(1<<LED_P)
#endif

// ================================= Timings ===================================
#define CC_RX_ON_DELAY      18 // ms
#define CC_RX_OFF_DELAY     108 // ms

#define DETECTOR_TIMEOUT    3996 // ms

// =============================== Packet info =================================
#define PKT_ID_CALL     0xCA

// =============================== LED defins ==================================
// Timings
#define PWMDelayLong    108  // Low brightness
#define PWMDelayMid     72  // Mid brightness
#define PWMDelayFast    18  // High brightness
// Light constants
#define PWMStartValue   45  // Initial LED brightness
#define PWMStepOver1    36  // Where to switch to quick PWM change mode
#define PWMStepOver2    54
#define	PWMMin          0
#define PWM_MAX         150

// Charge indicating brightness
#define CHARGING_PWM_MAX    18
#define CHARGING_PWM_MIN    0

// On/off russe
#define TIMER1_ENABLE()     TCCR1B = (0<<WGM13)|(1<<WGM12)|(0<<CS12)|(0<<CS11)|(1<<CS10)
#define TIMER1_DISABLE()    TCCR1B = 0

// =============================== Prototypes ==================================
void GeneralInit(void);

void PWM_Setup(void);
bool MayChangePWM(void);

void CC_Task (void);
void Stone_Task(void);
void LED_Task(void);
void IndicateCharging_TASK(void);

void EVENT_Detected(void);
void EVENT_Hide(void);
void EVENT_NewPacket(void);

#endif	/* _MAIN_H */

