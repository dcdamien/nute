/*
 * ir.h
 *
 *  Created on: 04.07.2013
 *      Author: kreyl
 */

#ifndef IR_H_
#define IR_H_

#include "inttypes.h"
#include "hal.h"
#include "ch.h"
#include "kl_lib_f100.h"

#define IR_CARRIER_HZ       56000
#define IR_BIT_CNT          14
#define MAX_PWR             4005     // Top DAC value

// Delays, uS
#define IR_TICK_US          600 // Protocol smallest time unit, us
/* Header = 4 * IR_TICK_US
 * Space  = 1 * IR_TICK_US
 * Zero   = 1 * IR_TICK_US
 * One    = 2 * IR_TICK_US
 */

// Timings
#define IR_HEADER_US        2400
#define IR_ZERO_US          600
#define IR_ONE_US           1200

struct IrChunk_t {
    uint8_t On;
    uint16_t Duration;
};
#define CHUNK_CNT   (1+1+(IR_BIT_CNT*2))

#define CARRIER_PERIOD_CNT  2
#define SAMPLING_FREQ_HZ    (CARRIER_PERIOD_CNT*IR_CARRIER_HZ)

// Currents
enum DacCurrent_t {dc50mA=153, dc100mA=306, dc150mA=450, dc200mA=595, dc400mA=1152, dc800mA=2304, dc1000mA=3006};

class ir_t {
private:
    EventSource IEvtSrcTxEnd;
    IrChunk_t TxBuf[CHUNK_CNT], *PChunk; // Buffer of power values: header + all one's + 1 delay after
    uint16_t CarrierArr[CARRIER_PERIOD_CNT], ZeroArr[CARRIER_PERIOD_CNT];
    Timer_t SamplingTmr, ChunkTmr, CarrierTmr;
    uint16_t CarrierTmrPwr;
    inline void IDacCarrierDisable() {
        dmaStreamDisable(STM32_DMA1_STREAM3);
        dmaStreamSetMemory0(STM32_DMA1_STREAM3, ZeroArr);
        dmaStreamEnable(STM32_DMA1_STREAM3);
    }
    inline void IDacCarrierEnable() {
        dmaStreamDisable(STM32_DMA1_STREAM3);
        dmaStreamSetMemory0(STM32_DMA1_STREAM3, CarrierArr);
        dmaStreamEnable(STM32_DMA1_STREAM3);
    }
public:
    bool Busy;
    void Init();
    void TransmitWord(uint16_t wData, DacCurrent_t ACurrent, uint8_t PwmPercent);
    void RegisterEvtTxEnd(EventListener *PEvtLstnr, uint8_t EvtMask) { chEvtRegisterMask(&IEvtSrcTxEnd, PEvtLstnr, EvtMask); }
    // Inner use
    void IChunkTmrHandler();
};

extern ir_t ir;


#endif /* IR_H_ */