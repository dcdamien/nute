/*
 * File:   main.h
 * Author: Kreyl
 *
 * Created on April 14, 2011, 1:27 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif

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
void Cycle_Task(void);
void LED_Task(void);

// Events
void EVENT_NewPacket(void);
void EVENT_TxToIdle(void);
void EVENT_CycleTimerFire(void);

#ifdef __cplusplus
}
#endif


#endif	/* MAIN_H */

