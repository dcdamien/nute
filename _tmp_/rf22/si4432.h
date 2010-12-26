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

// ================================= Pins ======================================
#define SI_GPIO     GPIOA
#define SI_SDN      GPIO_Pin_0  // Shutdown pin
#define SI_NIRQ     GPIO_Pin_1
#define SI_SCK      GPIO_Pin_5  // SCK
#define SI_DO       GPIO_Pin_6  // MISO
#define SI_DI       GPIO_Pin_7  // MOSI
#define SI_NSEL     GPIO_Pin_8  // SS
// Clocks
#define SI_GPIO_CLK RCC_APB2Periph_GPIOA
#define SI_SPI_CLK  RCC_APB2Periph_SPI1
// NSel
#define SI_NSEL_HI()    (SI_GPIO->BSRR = SI_NSEL)
#define SI_NSEL_LO()    (SI_GPIO->BRR  = SI_NSEL)
// Shutdown pin
#define SI_SHUTDOWN()   (SI_GPIO->BSRR = SI_SDN)
#define SI_SWITCH_ON()  (SI_GPIO->BRR  = SI_SDN)

// ========================== Types and variables ==============================
#define SI_PKT_DATA_LENGTH  4 //SI_PKT_LENGTH-3
struct SI_Packet_t {
    uint8_t Address;
    uint8_t PacketID;
    uint8_t CommandID;
    uint8_t Data[SI_PKT_DATA_LENGTH];
    uint8_t RSSI;
    uint8_t LQI;
};

struct Si_t {
    uint8_t State;
    union {
        uint8_t RX_PktArray[sizeof(struct SI_Packet_t)];
        struct SI_Packet_t RX_Pkt;
    };
    union {
        uint8_t TX_PktArray[sizeof(struct SI_Packet_t)];
        struct SI_Packet_t TX_Pkt;
    };
    bool NewPacketReceived;
};

extern struct Si_t SI;

// ============================= Prototypes ====================================
void SI_Init (void);


void SI_WriteRegister (const uint8_t Addr, const uint8_t AData);
uint8_t SI_ReadRegister (const uint8_t Addr);

#endif	/* SI4432_H */

