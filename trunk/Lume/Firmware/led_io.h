/* 
 * File:   led_io.h
 * Author: Kreyl Laurelindo
 *
 * Created on 19 Август 2010 г., 22:02
 */

#ifndef LED_IO_H
#define	LED_IO_H

#include <inttypes.h>
#include "common.h"

// Lights
#define L_DDR       DDRD
#define L_PORT      PORTD
#define DATA_IN     PD1
#define LATCH       PD3
#define SRCLK       PD4

#define M_PWM_DDR   DDRD
#define M_PWM_PORT  PORTD
#define M0PWM       PD6
#define M1PWM       PD5
#define H_PWM_DDR   DDRB
#define H_PWM_PORT  PORTB
#define H0PWM       PB1
#define H1PWM       PB2

// ================================ Types ======================================
enum PWMMode_t {PWMHold, PWMTop, PWMRise, PWMFade, PWMBlink, PWMOff};
struct PWM_t {
    uint8_t Value;
    uint16_t Timer, Delay;
    enum PWMMode_t Mode;
    io_uint8_t *OCRX;
};
struct LControl_t {
    uint8_t HByte, MByte;   // Control bytes
    // PWMs
    uint8_t PWM_TopValue;
    struct PWM_t Min0PWM, Min1PWM, Hr0PWM, Hr1PWM;
};

extern struct LControl_t LControl;

// ================================ Prototypes =================================
void LedIOInit(void);

void WriteControlBytes(void);

void SetupMinute(uint8_t AMinute, enum PWMMode_t AMode);
void SetupHour(uint8_t AHour, enum PWMMode_t AMode);

void SetupPWM(struct PWM_t *pwm, enum PWMMode_t mode);
void PWM_On(io_uint8_t *p);
void PWM_Off(io_uint8_t *p);
void PWM_Blink(io_uint8_t *p);

void TogglePWM(struct PWM_t *pwm);

// ================================= Constants =================================
// Timings
#define PWMDelay1   99	// Low brightness
#define PWMDelay2   4	// Mid brightness
#define PWMDelay3   1	// High brightness

// Light constants
#define PWMStepOver1	27	// Where to switch to quick PWM change mode
#define PWMStepOver2	45

#define MAX_PWM		250
#define MIN_PWM		10
#define PWM_STEP	40

// Light control
#define M12     0
#define M0_5    1
#define M1      2
#define M1_5    3
#define M2      4
#define M2_5    5
#define M3      6
#define M3_5    7
#define M4      8
#define M4_5    9
#define M5      10
#define M5_5    11
#define M6      12
#define M6_5    13
#define M7      14
#define M7_5    15
#define M8      16
#define M8_5    17
#define M9      18
#define M9_5    19
#define M10     20
#define M10_5   21
#define M11     22
#define M11_5   23


#endif	/* LED_IO_H */

