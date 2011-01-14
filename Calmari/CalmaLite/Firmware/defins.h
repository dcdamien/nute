// ******************* Includes ************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

// ************** Functions prototypes *****************
void EventHandler(void);
void LightUp (void);
void LightDown (void);
void LiveInLight (void);

void EnableInput  (void);
void DisableInput (void);

// ******************* Constants ***********************
#define True	1
#define False	0
enum {None, KeyDown, KeyPressed};

#define KeyPin PB0
#define LedPin PB1

// Timings
#define PWMQuickDelay	_0_02_s
#define PWMSlowDelay	4
#define PWMStepOver		40

// ****************** Variables ************************
volatile uint8_t Valto = None;

// ****************** includes 2 ***********************
#include "delay.c"
#include "SleepUnit.c"
#include "PWMUnit.c"

