/* 
 * File:   dac.h
 * Author: Kreyl Laurelindo
 *
 * Created on 3 Март 2011 г., 19:52
 */

#ifndef DAC_H
#define	DAC_H

#include "stm32f10x.h"
#include <stdbool.h>

class Dac_t {
private:
    bool MayPlay;
    void AmplifierOn(void)  { GPIOA->BSRR = GPIO_Pin_8; }    // Set SHUTDOWN pin high
    void AmplifierOff(void) { GPIOA->BRR  = GPIO_Pin_8; }    // Set SHUTDOWN pin low
public:
    void Init(void);
    void PlayLoop(void);
    void StopLoop(void) { MayPlay = false; } // Stop playing continuosly
    void CheckIfStop(void);
};

extern Dac_t Dac;

// Declare DMA1_Channel3 IRQ. Use externC to make it visible from asm file.
extern "C" {
void DMA1_Channel3_IRQHandler(void);
}

#endif	/* DAC_H */

