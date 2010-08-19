#ifndef _LUME_H
#define	_LUME_H

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


// ========================== Functions prototypes =============================
void GeneralInit (void);

// Tasks
void TASK_Toggle(void);

// Events
void EVENT_NewHour(void);
void EVENT_NewHyperMinute(void);

#endif