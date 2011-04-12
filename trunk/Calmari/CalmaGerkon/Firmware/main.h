/*
 * File:   main.h
 * Author: Kreyl
 *
 * Created on April 11, 2011, 7:38 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <stdbool.h>
#include <avr/io.h>

// =================================== PWM =====================================
// Pins
#define PWM_P       PB1

#define PWM_SET(APWM)   OCR1A = APWM

// Timings
#define PWMDelayLong    108 // Low brightness
#define PWMDelayMid     72  // Mid brightness
#define PWMDelayFast    18  // High brightness

// Light constants
#define PWM_MAX         250
#define PWMStartValue	45	// Initial LED brightness
#define PWMStepOver1	36	// Where to switch to quick PWM change mode
#define PWMStepOver2	54

// ================================= Key    ====================================
// Pins
#define KEY_P               PB0
#define KEY_PCINT           PCINT0
#define KEY_POLL_TIMEOUT    252 // ms
#define KEY_IS_DOWN()       bit_is_clear(PINB, KEY_P)

// ============================ Prototypes =====================================
void GeneralInit(void);

// PWM
bool MayChangePWM(void);
void PWMEnable(void);
void PWMDisable(void);

// Tasks
void Key_Task(void);
void PWM_Task(void);
void Sleep_Task(void);

// Events
void EVENT_KeyPressed(void);

#endif	/* MAIN_H */

