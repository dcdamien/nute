/* 
 * File:   mdl_inputs.h
 * Author: Kreyl
 *
 * Created on April 5, 2011, 1:22 AM
 */

#ifndef MDL_INPUTS_H
#define	MDL_INPUTS_H

#define DELAY_CHECK     400     // ms

class Inputs_t {
private:
    uint32_t Timer;
public:
    void Init(void);
    void Check(void);
};

extern Inputs_t Inputs;

#endif	/* MDL_INPUTS_H */

