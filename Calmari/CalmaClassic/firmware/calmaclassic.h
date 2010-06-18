// ******************* Includes ************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

// ************** Functions prototypes *****************
uint8_t KeyState (void);
uint8_t DoLightUp (void);
uint8_t DoLightDown (void);
void DoHandleLight (void);
void DoSleep (void);

// ******************* Constants ***********************
enum {None, KeyDown, KeyDepressed}; // events
enum {DeepSleep, WaitKeyRelease, LightUp, LightAlive, LightDown}; // system states
enum {Finished, UnFinished}; // Threads state
// Pins
#define KeyPin	PB2
#define LedPin	PB1

// Timings
#define PWMDelay1		4	// Low brightness
#define PWMDelay2		2	// Mid brightness
#define PWMDelay3		1	// High brightness
#define TimeToMeasure	36	// 61 is once a second

// Light constants
#define PWMStartValue	45	// Initial LED brightness
#define PWMStepOver1	36	// Where to switch to quick PWM change mode
#define PWMStepOver2	54
#define	PWMMin			0
#define PWMMax			250
#define ILedNominal		400	// 20 mA

// *************** Pseudo functions ********************
#define KeyIsUp()       bit_is_set (PINB, KeyPin)
#define EnableKeyIRQ()  GIMSK = (0<<INT0)|(1<<PCIE)
#define DisableKeyIRQ() GIMSK = (0<<INT0)|(0<<PCIE)

// ****************** Variables ************************
volatile uint8_t Valto = None;
volatile uint8_t Sil = 0;
volatile uint8_t SilTics = 0;

// ****************** includes 2 ***********************
#include "PWMUnit.c"
#include "ADCUnit.c"

