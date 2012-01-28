/*
 * File:   cc2500.h
 * Author: Laurelindo
 *
 * Created on 11 Декабрь 2009 г., 2:08
 */

#ifndef _CC2500_H
#define	_CC2500_H

#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_spi.h"

#include "cc2500defins.h"
#include "kl_util.h"

#define CC_MODE_RX
//#define CC_DEBUG_PINS

// ============================ Types & variables ==============================
struct CC_Packet_t {
    uint8_t ToAddr;
    uint8_t CommandID;
    uint8_t SenderAddr;
    uint8_t SenderCycle;
    uint16_t SenderTime;
    int8_t RSSI;
    uint8_t LQI;
};
#define CC_PKT_LEN  6//(sizeof(CC_Packet_t)-2)

class CC_t {
private:
    // Variables
    uint32_t Timer;
    uint8_t State;
    bool NewPktRcvd;
    // Methods
    uint8_t ReadWriteByte(uint8_t AByte);
    // Pins
    void CS_Hi(void) { GPIO_SetBits(GPIOA, GPIO_Pin_4); }
    void CS_Lo(void) { GPIO_ResetBits(GPIOA, GPIO_Pin_4); }
    bool GDO0_IsHi(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3); }
    void BusyWait(void)  {} //{ while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)); }
    void IRQEnable(void);
    void IRQDisable(void);

    void RfConfig(void);
    void WriteTX (uint8_t *PData, uint8_t ALength);
    void ReadRX  (uint8_t *PData, uint8_t ALength);
    void EnterTXAndWaitToComplete(void);
    // Registers
    void WriteRegister (const uint8_t Addr, const uint8_t AData);
    uint8_t ReadRegister (const uint8_t Addr);
    void WriteStrobe(uint8_t AStrobe);
    // Strobes
    void Reset(void)        { WriteStrobe(CC_SRES); }
    void FlushRxFIFO(void)  { WriteStrobe(CC_SFRX); }
    void EnterTX(void)      { WriteStrobe(CC_STX);  }
    void EnterRX(void);
    void EnterIdle(void)    { WriteStrobe(CC_SIDLE);}
    void PowerDown(void)    { WriteStrobe(CC_SPWD); }
    void Calibrate(void)    { WriteStrobe(CC_SCAL); }
    void FlushTxFIFO(void)  { WriteStrobe(CC_SFTX); }
    void GetState(void)     { WriteStrobe(CC_SNOP); }
public:
    union {
        uint8_t RX_PktArray[CC_PKT_LEN+2];
        CC_Packet_t RX_Pkt;
    };
    union {
        uint8_t TX_PktArray[CC_PKT_LEN+2];
        CC_Packet_t TX_Pkt;
    };
    ftVoid_Void EvtNewPkt;
    // Methods
    void Init(void);
    void Task(void);
    void SetChannel(uint8_t AChannel);
    void SetAddress(uint8_t AAddr) { WriteRegister(CC_ADDR, AAddr); }
    // IRQ handler
    void IRQHandler(void);
    // Debug
#ifdef CC_DEBUG_PINS
    void SetPin
#endif
};

extern CC_t CC;

// Interrupt
extern "C" {
void EXTI3_IRQHandler(void);
}

#endif	/* _CC1101_H */
