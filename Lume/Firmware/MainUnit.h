// ====================== Includes ======================
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/sleep.h>

// ================= Functions prototypes ==================
void GeneralInit (void);
void ToggleHours (void);
void ToggleHyperMinutes (void);

// ====================== Constants ======================
#define true	1
#define false	0
#define ON		1
#define OFF		0

// Modes
#define ModeLive	0
#define ModeHours	1
#define	ModeMin		2

// Timings
#define PWMDelay1		7	// Low brightness
#define PWMDelay2		4	// Mid brightness
#define PWMDelay3		1	// High brightness

// Light constants
#define PWMStepOver1	27	// Where to switch to quick PWM change mode
#define PWMStepOver2	45

#define MAX_PWM		250
#define MIN_PWM		10
#define PWM_STEP	40

// ====================== Variables ======================
volatile uint8_t Seconds, HyperMinutes, Hours;
volatile uint8_t MinToFadeIn, MinToHold, MinToFadeOut, TicsFadeIn, TicsFadeOut, TicsH;
volatile uint8_t MFadeIn, MFadeOut, HFade;
volatile uint8_t HToFadeIn, HToFadeOut, NewHour;
volatile uint8_t Mode, WaitForRelease;
volatile uint8_t BlinkOn, BlinkTics=0;
volatile uint8_t TopPWM=MAX_PWM;

// =================== Pseudo-fuctions ====================
#define POWER_OK	bit_is_set (PIND, PD3)


// ====================== includes 2 ======================
#include "LumeIO.c"
