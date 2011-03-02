/* 
 * File:   cc2500.h
 * Author: Laurelindo
 *
 * Created on 11 Декабрь 2009 г., 2:08
 */

#ifndef _CC1101_H
#define	_CC1101_H

#include <inttypes.h>
#include <stdbool.h>
#include "stm32f10x.h"
#include "stm32f10x_spi.h"

#include "cc1101defins.h"

// ================================== Defins ===================================
// Ports
#define CC_GPIO         GPIOA
#define CC_GPIO_CLK     RCC_APB2Periph_GPIOA
#define CC_AFIO_CLK     RCC_APB2Periph_AFIO

#define CC_GDO0         GPIO_Pin_0
#define CC_CS           GPIO_Pin_1
#define CC_MOSI         GPIO_Pin_7
#define CC_MISO         GPIO_Pin_6
#define CC_SCLK         GPIO_Pin_5
// SPI
#define CC_SPI          SPI1
#define CC_SPI_CLK      RCC_APB2Periph_SPI1
// IRQ
#define CC_GDO0_PINSOURCE   GPIO_PinSource0
#define CC_GDO0_PORTSOURCE  GPIO_PortSourceGPIOA
#define CC_GDO0_EXTI_LINE   EXTI_Line0              // As EXTI0 connected to Pin0
#define CC_GDO0_EXTI_IRQn   EXTI0_IRQn

// ============================ Types & variables ==============================
struct CCSrv_t {
    uint32_t Timer;
};
extern CCSrv_t CCsrv;


#define CC_PKT_LEN          6
#define CC_PKT_DTA_LEN      CC_PKT_LEN-2
#define CC_PKT_EXTRA_LEN    CC_PKT_LEN+2
struct CC_Packet_t{
    uint8_t PacketID;
    uint8_t CommandID;
    uint8_t Payload[CC_PKT_DTA_LEN];
    uint8_t RSSI;
    uint8_t LQI;
};

class CC_t {
private:
    uint8_t ReadWriteByte(uint8_t AByte);
    void WriteStrobe(uint8_t AStrobe);
    // Pins
    void CS_Hi(void) { CC_GPIO->BSRR = CC_CS; }
    void CS_Lo(void) { CC_GPIO->BRR  = CC_CS; }
    void BusyWait(void) { while (GPIO_ReadInputDataBit(CC_GPIO, CC_MISO)); }
    // Methods
    void RfConfig(void);
public:
    uint8_t State;
    union {
        uint8_t RX_PktArray[CC_PKT_EXTRA_LEN];
        CC_Packet_t RX_Pkt;
    };
    union {
        uint8_t TX_PktArray[CC_PKT_EXTRA_LEN];
        CC_Packet_t TX_Pkt;
    };
    bool GDO0_WasHi;
    // Methods
    void Init(void);
    void SetChannel(uint8_t AChannel);
    void WriteTX (uint8_t *PData, uint8_t ALength);
    void ReadRX  (uint8_t *PData, uint8_t ALength);
    void EnterTXAndWaitToComplete (void);
    // Registers
    void WriteRegister (const uint8_t Addr, const uint8_t AData);
    uint8_t ReadRegister (const uint8_t Addr);
    // IRQ
    void IRQDisable(void) { /* NVIC_DisableIRQ(CC_GDO0_EXTI_IRQn);  */}   // Disable Exti line
    void IRQEnable (void) { /* NVIC_EnableIRQ (CC_GDO0_EXTI_IRQn); */}
    void IRQReset  (void) { /* EXTI_ClearFlag (CC_GDO0_EXTI_LINE); */}
    bool GDO0_IsHi(void) { return GPIO_ReadInputDataBit(CC_GPIO, CC_GDO0); }
    // Strobes
    void Reset(void)        { WriteStrobe(CC_SRES); }
    void FlushRxFIFO(void)  { WriteStrobe(CC_SFRX); }
    void EnterTX(void)      { WriteStrobe(CC_STX);  }
    void EnterRX(void)      { WriteStrobe(CC_SRX);  }
    void EnterIdle(void)    { WriteStrobe(CC_SIDLE);}
    void PowerDown(void)    { WriteStrobe(CC_SPWD); }
    void Calibrate(void)    { WriteStrobe(CC_SCAL); }
    void FlushTxFIFO(void)  { WriteStrobe(CC_SFTX); }
    void GetState(void)     { WriteStrobe(CC_SNOP); }
};

extern CC_t CC;


// ================================ Prototypes =================================
void Task_CC (void);

void EVENT_NewPacket(void);


#endif	/* _CC1101_H */

