/*
 * filter.h
 *
 *  Created on: 25 ����. 2014 �.
 *      Author: Kreyl
 */

#ifndef FILTER_H_
#define FILTER_H_

#include "cmd_uart.h"

template <uint32_t Sz, uint32_t Divider>
class FilterFir_t {
private:
    int32_t *a;
    int32_t x[Sz-1], W;
public:
    void Init(const int32_t *PCoefSettings) { a = (int32_t*)PCoefSettings; }
    int32_t AddAndCalc(int32_t x0) {
//        Uart.Printf("\r %d   ", x0);
        // Calculate filter
        int32_t rslt = x0 * a[0], R = W;
        for(uint32_t i=1; i<Sz; i++) {
            rslt += x[R] * a[i];
//            Uart.Printf("x%u=%d; ", R, x[R], i);
            if(++R >= Sz-1) R = 0;
        }
        // Add value to buffer
        if(W == 0) W = Sz - 2;
        else W--;
        x[W] = x0;
//        Uart.Printf("rslt=%d", rslt);
        return rslt / Divider;
    }
};



#endif /* FILTER_H_ */
