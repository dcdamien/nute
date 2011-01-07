/* 
 * File:   time_utils.h
 * Author: Laurelindo
 *
 * Created on 2009 г., 0:40
 */

#ifndef _TIME_UTILS_H
#define	_TIME_UTILS_H

#include <inttypes.h>
#include <stdbool.h>

// ========================== Function Prototypes ==============================
void DelayLoop (volatile uint32_t ACounter);
void Delay_ms (uint32_t Ams);

void DelayInit(void);
bool DelayElapsed(uint32_t *AVar, const uint32_t ADelay);
void DelayReset(uint32_t *AVar);

#endif	/* _TIME_UTILS_H */

