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

#define SI_DOUBLE

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
    void NSEL_Hi (void) { FGPIO->BSRR = NSEL; }
    void NSEL_Lo (void) { FGPIO->BRR  = NSEL; }
    // Registers
    void WriteRegister (const uint8_t Addr, const uint8_t AData);
    uint8_t ReadRegister (const uint8_t Addr);
    void RF_Config(const SiBitrate_t ABitrate, const SiBand_t ABand);
public:
    uint8_t State;
    uint8_t PktLength;
    union {
        uint8_t RX_PktArray[sizeof(struct SI_Packet_t)];
        struct SI_Packet_t RX_Pkt;
    };
    union {
        uint8_t TX_PktArray[sizeof(struct SI_Packet_t)];
        struct SI_Packet_t TX_Pkt;
    };
    bool NewPacketReceived;
    uint8_t IRQ1, IRQ2;
    // Methods
    void Init (SPI_TypeDef* ASPI, const SiBitrate_t ABitrate, const SiBand_t ABand);
    // Modes
    void SwitchOn  (void) { FGPIO->BRR  = SDN; }
    void SwitchOff (void) { FGPIO->BSRR = SDN; }
    void SetMode (uint8_t AMode) { WriteRegister(0x07, AMode); }
    // IRQs
    uint8_t NIRQ_Is_Hi(void) { return GPIO_ReadInputDataBit(FGPIO, NIRQ); }
    void IRQsSet (uint8_t AIRQ1, uint8_t AIRQ2);
    void IRQsRead (void);
    void IRQWait (void) { while (NIRQ_Is_Hi()); }
    // Data control
    void PktLengthSet (uint8_t ALength) { WriteRegister(0x3E, ALength); PktLength = ALength; }
    void PktLengthGet (void) { PktLength = ReadRegister(0x4B); }
    void TransmitPkt(void);
    void FIFOWrite(uint8_t* PData, uint8_t ALen);
    void FIFORead (void);
    void FIFOReset(void) { WriteRegister(0x08, 0x02); WriteRegister(0x08, 0x00); }
    // Radio control
    void SetPower (uint8_t APower) { WriteRegister(0x6D, (uint8_t)(0x18 | APower)); }
};

extern Si_t Si;
#ifdef SI_DOUBLE
extern Si_t Si2;
#endif
// ============================ Register settings ==============================
// Operation modes
#define SI_MODE_READY    0x01
#define SI_MODE_RX       0x05
#define SI_MODE_TX       0x09
#define SI_MODE_RESET    0x80

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

