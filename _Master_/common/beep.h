/* 
 * File:   beep.h
 * Author: Kreyl Laurelindo
 *
 * Created on 30 Ноябрь 2010 г., 17:37
 */

#ifndef BEEP_H
#define	BEEP_H

#include <inttypes.h>

#define BEEP_ON_TIME    45
#define BEEP_OFF_TIME   45
#define BEEP_TOP_VALUE  200

void Task_Beep(void);
void BeepInit(void);
void Beep(uint8_t ACount);

#endif	/* BEEP_H */

