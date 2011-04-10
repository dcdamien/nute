/* 
 * File:   wand.h
 * Author: Laurelindo
 *
 * Created on 25 Ноябрь 2009 г., 19:49
 */
#ifndef _WAND_H
#define	_WAND_H

#include <avr/io.h>

// ============================= Constants =====================================
#define PWM_P   PB1
#define KEY_P   PB2

#define SLEEP_T     1000

// ========== Lighting constants ==========
// Timings, mS
#define LIGHT_LOW_T   36
#define LIGHT_MID_T   18
#define LIGHT_HIGH_T  9
// PWM values
#define PWM_STEP_LOW    36
#define PWM_STEP_MID    135

// ============= Key constants ============
// Timings, mS
#define KEY_POLL_T  99
#define TRESHOLD_DURATION    297


// =========================== Pseudo functions ================================
#define LED_ON      PORTB |=  (1<<PWM_P)
#define LED_OFF     PORTB &= ~(1<<PWM_P)
#define LED_TOGGLE  PORTB ^=  (1<<PWM_P)

#define SET_PWM(ABrightness)  OCR1A = ABrightness

// Button
#define KEY_IS_DOWN     bit_is_clear (PINB, KEY_P)

// =============================== Prototypes ==================================
void Light_Task (void);
void LightSetDelay (void);

void Sleep_Task (void);

void Key_Task (void);
//void KeyPress_Event (void);
//void KeyDepress_Event (void);

void KeyQuickPress (void);
void KeyLongPress (void);


#endif	/* _WAND_H */

