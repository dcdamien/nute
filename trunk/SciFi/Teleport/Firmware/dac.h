/*
 * File:   dac.h
 * Author: Kreyl Laurelindo
 *
 * Created on 3 ���� 2011 �., 19:52
 */

#ifndef DAC_H
#define	DAC_H

#include "stm32f10x.h"
#include <stdbool.h>

class Dac_t {
public:
    bool MayPlay;
    uint8_t RepeatCount;
    void Init(void);
    void AmplifierOn(void)  { GPIOA->BSRR = GPIO_Pin_8; }    // Set SHUTDOWN pin high
    void AmplifierOff(void) { GPIOA->BRR  = GPIO_Pin_8; }    // Set SHUTDOWN pin low
    void WhatToPlay(uint32_t ASnd, uint32_t ALength);
};

extern Dac_t Dac;



#endif	/* DAC_H */
