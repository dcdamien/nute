/* 
 * File:   main.h
 * Author: Kreyl Laurelindo
 *
 * Created on 29 Ноябрь 2010 г., 19:49
 */

#ifndef MAIN_H
#define	MAIN_H

#include "common.h"
#include <avr/io.h>
#include <stdbool.h>

// Power ok
#define PWROK_DDR   DDRA
#define PWROK_PORT  PORTA
#define PWROK_PIN   PINA
#define PWROK_P     PA3
#define POWER_OK()  bit_is_set (PWROK_PIN, PWROK_P)

// Pumps
#define PUMP_COUNT  4
#define PUMP_DDR    DDRA
#define PUMP_PORT   PORTA
#define PUMP1P      PA4
#define PUMP2P      PA5
#define PUMP3P      PA6
#define PUMP4P      PA7
enum pump_t {Pump1=1, Pump2=2, Pump3=3, Pump4=4};

// ============================== Prototypes ===================================
void GeneralInit(void);

void PumpOn(enum pump_t APump);
#define PUMP_OFF_ALL( ) PUMP_PORT &= ~((1<<PUMP1P)|(1<<PUMP2P)|(1<<PUMP3P)|(1<<PUMP4P));

void EVENT_NewMinute(void);

#endif	/* MAIN_H */

