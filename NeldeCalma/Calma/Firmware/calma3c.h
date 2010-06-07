/* 
 * File:   calma3c.h
 * Author: Laurelindo
 *
 * Created on 20 Декабрь 2009 г., 0:16
 */

#ifndef _CALMA3C_H
#define	_CALMA3C_H

// =============================== Constants ===================================
// Timings, mS
#define KEY_POLL_T  99 

// ============================== Ports & pins =================================
#define PWM_RED     PD3
#define PWM_GREEN   PD5
#define PWM_BLUE    PD6
#define SENSOR_OUT  PD2

// ============================= Pseudo functions ==============================
// LEDs
#define LED_ON      PORTD |=  (1<<PWM_GREEN)
#define LED_OFF     PORTD &= ~(1<<PWM_GREEN)
#define LED_TOGGLE  PORTD ^=  (1<<PWM_GREEN)

// Button
#define KEY_IS_DOWN     bit_is_clear (PIND, SENSOR_OUT)

// =============================== Prototypes ==================================
void Key_Task (void);
void KeyPress_Event (void);
//void KeyDepress_Event (void);



#endif	/* _CALMA3C_H */

