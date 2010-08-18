// ============================ Includes =======================================
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/sleep.h>
#include <stdbool.h>

// ========================== Ports & pins =====================================
// Power ok
#define PWROK_DDR   DDRC
#define PWROK_PORT  PORTC
#define PWROK_PIN   PINC
#define PWROK_P     PC3
#define POWER_OK()  bit_is_set (PWROK_PIN, PWROK_P)

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


// ========================== Functions prototypes =============================
void GeneralInit (void);

// Tasks
void TASK_Toggle(void);

// Events
void EVENT_NewHour(void);
void EVENT_NewHyperMinute(void);

// Light control
void WriteControlBytes(void);

// ====================== Constants ======================
// Timings
#define PWMDelay1   7	// Low brightness
#define PWMDelay2   4	// Mid brightness
#define PWMDelay3   1	// High brightness

// Light constants
#define PWMStepOver1	27	// Where to switch to quick PWM change mode
#define PWMStepOver2	45

#define MAX_PWM		250
#define MIN_PWM		10
#define PWM_STEP	40
