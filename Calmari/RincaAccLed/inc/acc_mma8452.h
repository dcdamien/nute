/*
 * File:   acc_mma.h
 * Author: Kreyl
 *
 * Created on June 4, 2011, 11:56 AM
 */

#ifndef ACC_MMA_H
#define	ACC_MMA_H

#include "kl_lib_f100.h"
#include "main.h"
#include "ch.h"
#include "hal.h"

#define ACC_IRQ_GPIO            GPIOB
#define ACC_IRQ_PIN             5

#define ACC_MOTION_TRESHOLD     16      // 1...127. The threshold resolution is 0.063g/LSB.

#define ACC_I2C_ADDR            0x1C

// Registers addresses
#define ACC_REG_STATUS          0x00
#define ACC_INT_SRC             0x0C
#define ACC_REG_XYZ_DATA_CFG    0x0E
#define ACC_FF_MT_CFG           0x15
#define ACC_FF_MT_SRC           0x16
#define ACC_FF_MT_THS           0x17
#define ACC_FF_MT_COUNT         0x18
#define ACC_REG_CONTROL1        0x2A
#define ACC_REG_CONTROL2        0x2B
#define ACC_REG_CONTROL3        0x2C
#define ACC_REG_CONTROL4        0x2D
#define ACC_REG_CONTROL5        0x2E

//#define ACC_ACCELERATIONS_NEEDED

#ifdef ACC_ACCELERATIONS_NEEDED
struct Accelerations_t {
    uint8_t Status;     // Read to reset latched data
    int8_t xMSB, xLSB, yMSB, yLSB, zMSB, zLSB;
} PACKED;
#define ACCELERATIONS_SIZE     sizeof(Accelerations_t)
#endif

class Acc_t {
private:
    EventSource IEvtSrcIrq;
    Thread *PThread;
    void IClearIrq() { // Dummy read
        uint8_t RegAddr = ACC_FF_MT_SRC, Dummy;
        i2c.CmdWriteRead(ACC_I2C_ADDR, &RegAddr, 1, &Dummy, 1);
    }
    void IWriteReg(uint8_t AAddr, uint8_t AValue) {
        uint8_t RegAddr = AAddr, RegValue = AValue;
        i2c.CmdWriteWrite(ACC_I2C_ADDR, &RegAddr, 1, &RegValue, 1);
    }
public:
#ifdef ACC_ACCELERATIONS_NEEDED
    Accelerations_t Accelerations;
    uint32_t ThresholdTop, ThresholdBottom;
    void ReadAccelerations() {
        uint8_t RegAddr = ACC_REG_STATUS;
        i2c.CmdWriteRead(ACC_I2C_ADDR, &RegAddr, 1, (uint8_t*)&Accelerations, ACCELERATIONS_SIZE);
    }
#endif
    void Init();
    void Task();
    void RegisterEvtIrq(EventListener *PEvtLstnr, uint8_t EvtMask) { chEvtRegisterMask(&IEvtSrcIrq, PEvtLstnr, EvtMask); }
};

extern Acc_t Acc;

#endif	/* ACC_MMA_H */

