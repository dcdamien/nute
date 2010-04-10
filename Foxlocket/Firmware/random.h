/* 
 * File:   random.h
 * Author: Kreyl Laurelindo
 *
 * Created on 9 Апрель 2010 г., 10:18
 */

#ifndef _RANDOM_H
#define	_RANDOM_H

#include <inttypes.h>
#include <stdbool.h>


#define RANDOM_LENGTH   3 // bits

struct Random_t{
    uint8_t Random;
    bool IsReady;
    uint8_t counter;
};

extern struct Random_t ERandom;

// =============================== Prototypes ==================================
void RandomStart(void);
void RandomAdd(uint8_t AData);


#endif	/* _RANDOM_H */

