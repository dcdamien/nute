/* 
 * File:   leds.h
 * Author: Kreyl Laurelindo
 *
 * Created on 12 Март 2011 г., 15:07
 */

#ifndef LEDS_H
#define	LEDS_H

#include "stm32f10x.h"

#define PWM1_PIN    GPIO_Pin_6
#define PWM2_PIN    GPIO_Pin_7
#define PWM3_PIN    GPIO_Pin_8


class Leds_t {
private:

public:
    void Init(void);
};

extern Leds_t Leds;


#endif	/* LEDS_H */

