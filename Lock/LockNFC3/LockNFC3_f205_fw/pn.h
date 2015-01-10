/*
 * pn.h
 *
 *  Created on: 09 ���. 2015 �.
 *      Author: Kreyl
 */

#ifndef PN_H_
#define PN_H_

#include "ch.h"
#include "kl_lib_f2xx.h"
#include "pn_defins.h"

#if 1 // ===================== GPIO, DMA etc. ==================================
// SPI clock is up to 5MHz (um p.45)
#define PN_SPI      SPI1

// ==== DMA ====
#define PN_TX_DMA           STM32_DMA2_STREAM5
#define PN_TX_DMA_CHNL      3
#define PN_TX_DMA_MODE_NOIRQ \
    STM32_DMA_CR_CHSEL(PN_TX_DMA_CHNL) |               \
    DMA_PRIORITY_MEDIUM |                              \
    STM32_DMA_CR_MSIZE_BYTE | /* Size byte */          \
    STM32_DMA_CR_PSIZE_BYTE |                          \
    STM32_DMA_CR_MINC |       /* Mem pointer increase */  \
    STM32_DMA_CR_DIR_M2P      /* Mem to peripheral */
#define PN_TX_DMA_MODE_IRQ  (PN_TX_DMA_MODE_NOIRQ | STM32_DMA_CR_TCIE)

#define PN_RX_DMA           STM32_DMA2_STREAM2
#define PN_RX_DMA_CHNL      3
#define PN_RX_DMA_MODE      STM32_DMA_CR_CHSEL(PN_RX_DMA_CHNL) |               \
                            DMA_PRIORITY_HIGH |                                \
                            STM32_DMA_CR_MSIZE_BYTE | /* Memory Size - Byte */ \
                            STM32_DMA_CR_PSIZE_BYTE | /* Periph Size - Byte */ \
                            STM32_DMA_CR_MINC |    /* Mem pointer increase */  \
                            STM32_DMA_CR_DIR_P2M | /* Periph to Mem */         \
                            STM32_DMA_CR_TCIE      /* Enable Transmission Int C */


// ==== PN532 GPIOs PINs ====
#define PN_GPIO             GPIOA
#define PN_IRQ_GPIO         GPIOA
#define PN_NSS_GPIO         GPIOA
#define PN_IRQ_PIN          1
#define PN_NSS_PIN          0
#define PN_SCK_PIN          5
#define PN_MISO_PIN         6
#define PN_MOSI_PIN         7
#define PN_RST_PIN          4

#if PN_IRQ_PIN == 0
#define PN_IRQ_HANDLER    EXTI0_IRQHandler
#elif PN_IRQ_PIN == 1
#define PN_IRQ_HANDLER    EXTI1_IRQHandler
#elif PN_IRQ_PIN == 2
#define PN_IRQ_HANDLER    EXTI2_IRQHandler
#elif PN_IRQ_PIN == 3
#define PN_IRQ_HANDLER    EXTI3_IRQHandler
#elif PN_IRQ_PIN == 4
#define PN_IRQ_HANDLER    EXTI4_IRQHandler
#endif

#endif

// Buf sizes
#define PN_MAX_DATA_SZ      265  // Max Data Lenghth=265 including TFI um. page 29

// Timings
#define PN_ACK_TIMEOUT      27 // ms
#define PN_DATA_TIMEOUT     180 // ms

#if 1 // ======================= Auxilary structures ===========================
struct PnPrologue_t {
    uint8_t Preamble;       // Always 0x00
    uint8_t SoP0;           // Start of Packet Code 0
    uint8_t SoP1;           // Start of Packet Code 1
    uint8_t Len;            // Length
    uint8_t LCS;            // Length Checksum
} __attribute__ ((__packed__));
#define PROLOGUE_SZ  sizeof(PnPrologue_t)

struct PnPrologueExt_t {
    uint8_t Preamble;       // Always 0x00
    uint8_t SoP0;           // Start of Packet Code 0
    uint8_t SoP1;           // Start of Packet Code 1
    uint8_t NPLC;           // Normal Packet Length - 0xFF always for extended frame
    uint8_t NPL;            // Normal Packet Length Checksum - 0xFF always for extended frame
    uint8_t LengthHi;       // MSByte of Length
    uint8_t LengthLo;       // LSByte of Length
    uint8_t LCS;            // Length Checksum
    void CalcLCS() { LCS = -(LengthHi + LengthLo); }
} __attribute__ ((__packed__));
#define PROLOGUE_EXT_SZ  sizeof(PnPrologueExt_t)

//struct PnData_t {
//    uint8_t TFI;
//    uint8_t PD0;
//    union {
//        uint8_t Tg;
//        uint8_t Err;
//        uint8_t Slot;
//    };
//    uint8_t Buf[PN_MAX_DATA_SIZE-1];
//} __attribute__ ((__packed__));

struct PnEpilogue_t {
    uint8_t DCS;
    uint8_t Postamble;
} __attribute__ ((__packed__));
#define EPILOGUE_SZ  sizeof(PnEpilogue_t)

struct PnAckNack_t {
    uint8_t Preamble;
    uint8_t SoP0;           // Start of Packet Code 0
    uint8_t SoP1;           // Start of Packet Code 1
    uint8_t Code0;
    uint8_t Code1;
    uint8_t Postamble;
    bool operator == (const PnAckNack_t &APkt) { return (Preamble == APkt.Preamble) and (SoP0 == APkt.SoP0) and (SoP1 == APkt.SoP1) and (Code0 == APkt.Code0) and (Code1 == APkt.Code1) and (Postamble == APkt.Postamble); }
} __attribute__ ((__packed__));

const PnAckNack_t PnPktAck = {0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00};

// Auxilary Data indxs, sizes etc
#define PN_PROLOGUE_INDX    1
#define PN_DATA_EXT_INDX    (1 + PROLOGUE_EXT_SZ)   // index in buffer
#define PN_DATA_INDX        (1 + PROLOGUE_SZ)       // index in buffer
#define PN_TX_SZ(ALength)   (1 + PROLOGUE_EXT_SZ + ALength + EPILOGUE_SZ)

#endif

#if 1 // =========================== PN class ==================================
enum PnState_t {psOff, psSetup, psConfigured};

class PN532_t {
private:
    PnState_t State;
    IrqPin_t IIrqPin;
    uint32_t ILength; // General variable
    // Frame
    uint8_t IBuf[1 + PROLOGUE_EXT_SZ + PN_MAX_DATA_SZ + EPILOGUE_SZ]; // Seq type + prologue +...
    uint8_t *PSeqType = IBuf;
    PnPrologue_t    *Prologue    = (PnPrologue_t*)   &IBuf[PN_PROLOGUE_INDX];  // Exclude Seq type
    PnPrologueExt_t *PrologueExt = (PnPrologueExt_t*)&IBuf[PN_PROLOGUE_INDX];  // Exclude Seq type
    uint8_t *PData;
    void WriteEpilogue(uint16_t ALength) { // [TFI + PD0 + PD1 + � + PDn + DCS] = 0x00
        uint8_t *p = &IBuf[PN_DATA_EXT_INDX]; // Beginning of TFI+Data
        uint8_t Dcs = 0;
        for(uint16_t i=0; i<ALength; i++) Dcs += *p++;
        Dcs = - Dcs;
        *p++ = Dcs; // DCS
        *p = 0x00;  // Postamble
    }
    // Gpio
    inline void IRstLo()  { PinClear(PN_GPIO, PN_RST_PIN); }
    inline void IRstHi()  { PinSet  (PN_GPIO, PN_RST_PIN); }
    inline void INssLo()  { PinClear(PN_NSS_GPIO, PN_NSS_PIN); chThdSleepMilliseconds(1); } // TODO: useconds?
    inline void INssHi()  { PinSet  (PN_NSS_GPIO, PN_NSS_PIN); }
    // Inner use
    void IReset();
    uint8_t ServiceCmd(uint8_t CmdID, uint32_t ADataLength, ...);
    // ==== Data Exchange ====
    uint8_t ReceiveAck();
    uint8_t ReceiveData();
    void ITransmit(void *Ptr, uint32_t ALength);
    void IReceive(void *Ptr, uint32_t ALength);
    uint8_t WaitReplyReady(uint32_t ATimeout);

    // ==== Hi lvl ====
    void FieldOn()  { ServiceCmd(PN_CMD_RF_CONFIGURATION, 2, 0x01, 0x01); }
    void FieldOff() { ServiceCmd(PN_CMD_RF_CONFIGURATION, 2, 0x01, 0x00); }
public:
    void Init();
    // Inner use
    void ITask();
    Thread *PThd;
    Spi_t ISpi;
    inline void IrqSpiHandler();    // SPI IRQ Handler
    inline void IrqPinHandler();    // EXTI P70_IRQ Handler
};
#endif

extern PN532_t Pn;

#endif /* PN_H_ */
