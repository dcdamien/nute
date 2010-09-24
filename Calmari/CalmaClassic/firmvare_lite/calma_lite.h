// ******************* Includes ************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <stdbool.h>

// =================================== PWM =====================================
// Timings
#define PWMDelayLong    27  // Low brightness
#define PWMDelayMid     18  // Mid brightness
#define PWMDelayFast    3   // High brightness

// Light constants
#define PWM_MAX         255
#define PWMStepOver1	36	// Where to switch to quick PWM change mode
#define PWMStepOver2	54

// ================================= Common ====================================
// Pins
#define KeyPin	PB2
#define LedPin	PB1

#define KEY_POLL_TIMEOUT    495 // ms

// *************** Pseudo functions ********************
#define KEY_IS_DOWN()   bit_is_set (PINB, KeyPin)

// ============================ Prototypes =====================================
void GeneralInit(void);

// PWM
bool MayChangePWM(void);
void PWMEnable(void);
void PWMDisable(void);

// Tasks
void Key_Task(void);
void LED_Task(void);
void Sleep_Task(void);

// Events
void EVENT_KeyPressed(void);