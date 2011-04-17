/*
 * File:   main.h
 * Author: Kreyl
 *
 * Created on April 14, 2011, 1:27 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define EE_TEAR_ADDRESS 0
// ================================== Timer ====================================
// Divider = 64
#define TCCR1B_ON   (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(1<<CS01)|(1<<CS00)
#define TCCR1B_OFF  (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(0<<CS01)|(0<<CS00)

#define CYC_TIMER_START()    TCCR1B = TCCR1B_ON
#define CYC_TIMER_STOP()     TCCR1B = TCCR1B_OFF

#define CYCLE_COUNT         4
#define PKT_DURATION        504
//#define SUBCYCLE_DURATION   3960    // 251.7 ms
#define SUBCYCLE_DURATION   5040    // 322 ms

// ================================== Light ====================================
#define LED_DDR         DDRD
#define LED_PORT        PORTD
#define LED_P           PD3

#define PWM_MAX         250
// Timings
#define PWMDelayLong    108 // Low brightness
#define PWMDelayMid     72  // Mid brightness
#define PWMDelayFast    18  // High brightness

// Light constants
#define PWMStepOver1	36	// Where to switch to quick PWM change mode
#define PWMStepOver2	54

#define PWM_SET(APWM)   OCR2B = APWM


// =============================== Prototypes ==================================
// General
void GeneralInit(void);

// PWM
bool PWMDelayElapsed(void);
void PWMEnable(void);
void PWMDisable(void);

// Tasks
void CC_Task (void);
void LED_Task(void);

// Events
void EVENT_NewPacket(void);

#endif	/* MAIN_H */

