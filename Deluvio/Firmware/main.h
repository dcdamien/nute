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
#define PUMP_DDR    DDRA
#define PUMP_PORT   PORTA
#define PUMP1P      PA4
#define PUMP2P      PA5
#define PUMP3P      PA6
#define PUMP4P      PA7
enum pump_t {Pump1, Pump2, Pump3, Pump4};

// Modes
//enum {ModeRegular, ModeSetHours, ModeSetMinutes} Mode;

// ============================== Prototypes ===================================
void GeneralInit(void);

void PumpOn(enum pump_t APump);
void PumpOff(enum pump_t APump);

void PrintTime(uint8_t x, uint8_t y);


#endif	/* MAIN_H */

