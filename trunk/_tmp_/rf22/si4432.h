/* 
 * File:   si4432.h
 * Author: Kreyl Laurelindo
 *
 * Created on 25 Декабрь 2010 г., 21:48
 */

#ifndef SI4432_H
#define	SI4432_H

#include "stm32f10x.h"
#include <stdbool.h>
#include "spi.h"

// ================================= Pins ======================================
// ==== 1st ====
#define SI1_GPIO     GPIOA
#define SI1_SDN      GPIO_Pin_0  // Shutdown pin
#define SI1_NIRQ     GPIO_Pin_1
// ==== 2nd ====
#ifdef SI_DOUBLE
#define SI2_GPIO     GPIOB
#define SI2_SDN      GPIO_Pin_11    // Shutdown pin
#define SI2_NIRQ     GPIO_Pin_10
#define SI2_SCK      GPIO_Pin_13    // SCK
#define SI2_DO       GPIO_Pin_14    // MISO
#define SI2_DI       GPIO_Pin_15    // MOSI
#define SI2_NSEL     GPIO_Pin_12    // SS
// Clocks
#define SI2_GPIO_CLK RCC_APB2Periph_GPIOA
#define SI2_SPI_CLK  RCC_APB2Periph_SPI1
// NSel
#define SI2_NSEL_HI()    (SI2_GPIO->BSRR = SI2_NSEL)
#define SI2_NSEL_LO()    (SI2_GPIO->BRR  = SI2_NSEL)
// Shutdown pin
#define SI2_SHUTDOWN()   (SI2_GPIO->BSRR = SI2_SDN)
#define SI2_SWITCH_ON()  (SI2_GPIO->BRR  = SI2_SDN)
// NIRQ
#define SI2_NIRQ_IS_HI() GPIO_ReadInputDataBit(SI2_GPIO, SI2_NIRQ)
#define SI2_WAIT_IRQ()   while (SI2_NIRQ_IS_HI())
#endif

// ========================== Types and variables ==============================
enum SiBitrate_t {br10000};
enum SiBand_t {bnd310, bnd868};

#define SI_PKT_MAX_LENGTH  252 // Total length of PktID+Cmd+Data
struct SI_Packet_t {
    uint8_t PacketID;
    uint8_t CommandID;
    uint8_t Data[SI_PKT_MAX_LENGTH-2];
};

class Si_t {
private:
    GPIO_TypeDef* FGPIO;
    uint16_t SDN, NIRQ, NSEL;
    SPI_TypeDef* FSPI;
    // Pins
    uint8_t NIRQ_Is_Hi(void) { return GPIO_ReadInputDataBit(FGPIO, NIRQ); }
    void NSEL_Hi (void) { FGPIO->BSRR = NSEL; }
    void NSEL_Lo (void) { FGPIO->BRR  = NSEL; }
    // Registers
    void WriteRegister (const uint8_t Addr, const uint8_t AData);
    uint8_t ReadRegister (const uint8_t Addr);
    void RF_Config(const SiBitrate_t ABitrate, const SiBand_t ABand);
public:
    uint8_t State;
    uint8_t DataLength;
    union {
        uint8_t RX_PktArray[sizeof(struct SI_Packet_t)];
        struct SI_Packet_t RX_Pkt;
    };
    union {
        uint8_t TX_PktArray[sizeof(struct SI_Packet_t)];
        struct SI_Packet_t TX_Pkt;
    };
    bool NewPacketReceived;
    // Methods
    void Init (SPI_TypeDef* ASPI, const SiBitrate_t ABitrate, const SiBand_t ABand);
    // Modes
    void SwitchOn  (void) { FGPIO->BRR  = SDN; }
    void SwitchOff (void) { FGPIO->BSRR = SDN; }
    void SetMode (uint8_t AMode) { WriteRegister(0x07, AMode); }
    // IRQs
    void SetIRQs (uint8_t AIRQ1, uint8_t AIRQ2);
    void FlushIRQs (void);
    void WaitIRQ (void) { while (NIRQ_Is_Hi()); }
    // Data control
    void SetPktTotalLength (uint8_t ALength);
    void TransmitPkt(void);
    void FIFOWrite(uint8_t* PData, uint8_t ALen);
    void FIFORead (uint8_t* PData, uint8_t ALen);
    // Radio control
    void SetPower (uint8_t APower) { WriteRegister(0x6D, (uint8_t)(0x18 | APower)); }
};

extern Si_t Si;
//extern Si_t Si2;

// ============================ Register settings ==============================
// Operation modes
#define SI_READY    0x01
#define SI_RX       0x05
#define SI_TX       0x09
#define SI_RESET    0x80

// IRQs 1
#define SI_IRQ1_NONE         0x00
#define SI_IRQ1_PKT_SENT     0x04
#define SI_IRQ1_PKT_RCVD     0x02
#define SI_IRQ1_CRC_ERR      0x01
// IRQs 2
#define SI_IRQ2_NONE         0x00
#define SI_IRQ2_SYNC_DETECT  0x80
#define SI_IRQ2_VALID_PRE    0x40
#define SI_IRQ2_RSSI         0x10





#endif	/* SI4432_H */

