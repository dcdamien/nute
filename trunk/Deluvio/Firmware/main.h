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

// Pumps
#define PUMP_DDR    DDRA
#define PUMP_PORT   PORTA
#define PUMP1P      PA4
#define PUMP2P      PA5
#define PUMP3P      PA6
#define PUMP4P      PA7
enum pump_t {Pump1, Pump2, Pump3, Pump4};

// Sensors


// ============================== Prototypes ===================================
void PumpOn(enum pump_t APump);
void PumpOff(enum pump_t APump);

void GeneralInit(void);
void QTouchInit(void);
bool SensorIsTouched(uint8_t ASensor);

#endif	/* MAIN_H */

