#include "si4432.h"
#include "stm32f10x_spi.h"
#include "delay_util.h"
#include "si4432_rfconfig.h"

// Variables
struct Sit Si;

// Local prototypes
void SiSPIInit (void);
void SiRFConfig (void);

uint8_t SiReadWriteByte (uint8_t AByte);

// ============================ Implementation =================================
void SiInit (void) {
    SiSPIInit();
    Si.NewPacketReceived = false;
    Si.TX_Pkt.PacketID = 0;
    SI_SWITCH_ON();
    Delay_ms(15);           // Wait at least 15ms before any initialization SPI commands are sent to the radio
    SiFlushIRQs();         // Release nIRQ pin
    SiSetMode (SI_RESET);  // Perform reset of all registers
    SI_WAIT_IRQ();          // Wait for chip to become ready
    SiRFConfig();
    SiFlushIRQs();         // Release nIRQ pin
}

void SiTransmitPkt(void) {
    SiFIFOWrite(Si.TX_PktArray, Si.DataLength);    // Place TX packet to FIFO
    SiSetMode(SI_TX);   // Enter TX mode
}

void SiSetReady (void) {
    SiSetMode (SI_READY);
    SiPollIRQ2 (SI_IRQ2_CHIP_READY);
}
void SiSetMode (uint8_t AMode) {
    SiWriteRegister(0x07, AMode);
}
void SiSetIRQs (uint8_t AIRQ1, uint8_t AIRQ2) {
    SiWriteRegister(0x05, AIRQ1);
    SiWriteRegister(0x06, AIRQ2);
}
void SiSetPktTotalLength (uint8_t ALength) {
    SiWriteRegister(0x3E, ALength);
    Si.DataLength = ALength;
}

void SiFIFOWrite(uint8_t* PData, uint8_t ALen) {
    uint8_t FData = 0x7F | 0x80;                // Write to FIFO register = 0x7F
    SI_NSEL_LO();
    SPI1->DR = FData;                           // Write FIFO address
    for (uint8_t i=0; i<ALen; i++) {
        while (!(SPI1->SR & SPI_I2S_FLAG_TXE)); // Wait for buffer to empty
        SPI1->DR = *PData++;                    // Write data
    }
    while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));    // Wait for SPI transmission to complete
    SI_NSEL_HI();
    FData = SPI1->DR;                           // Dummy read to reset RXNE flag
}
void SiFIFORead (uint8_t* PData, uint8_t ALen) {
    SI_NSEL_LO();
    SPI1->DR = 0x7F;                            // Write FIFO address
    while (!(SPI1->SR & SPI_I2S_FLAG_TXE));     // Wait for buffer to empty
    for (uint8_t i=0; i<ALen; i++) {
        SPI1->DR = 0;                           // Write dummy byte
        while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));// Wait for SPI transmission to complete
        *PData = SPI1->DR;                      // Read data
    }
    SI_NSEL_HI();
}

void SiFlushIRQs (void) {
    SiReadRegister(0x03);  //read the Interrupt Status1 register
    SiReadRegister(0x04);  //read the Interrupt Status2 register
}
void SiPollIRQ2 (uint8_t AIRQ) {
    uint8_t R;
    do {
        R = SiReadRegister(0x04);
    } while(!(R & AIRQ));
}

// ============================== Inner use ====================================
void SiWriteRegister (const uint8_t Addr, const uint8_t AData) {
    SI_NSEL_LO();
    SiReadWriteByte (Addr | 0x80); // Send Addr with Write flag
    SiReadWriteByte (AData);       // Send data
    SI_NSEL_HI();
}
uint8_t SiReadRegister (const uint8_t Addr) {
    uint8_t Rpl;
    SI_NSEL_LO();
    SiReadWriteByte (Addr);
    Rpl =  SiReadWriteByte (0);
    SI_NSEL_HI();
    return Rpl;
}

void SiSPIInit (void) {
    // ==== Clocks init ====
    RCC_APB2PeriphClockCmd(SI_GPIO_CLK | SI_SPI_CLK, ENABLE);
    // ==== GPIO init ====
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // Configure MOSI & SCK as Alternate Function Push Pull
    GPIO_InitStructure.GPIO_Pin  = SI_SCK | SI_DI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SI_GPIO, &GPIO_InitStructure);
    // Configure MISO as Input Floating
    GPIO_InitStructure.GPIO_Pin  = SI_DO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SI_GPIO, &GPIO_InitStructure);
    // Configure SDN & NSEL as Push Pull outputs
    GPIO_InitStructure.GPIO_Pin  = SI_SDN | SI_NSEL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(SI_GPIO, &GPIO_InitStructure);
    // Configure SI_NIRQ as Pull-up input
    GPIO_InitStructure.GPIO_Pin  = SI_NIRQ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(SI_GPIO, &GPIO_InitStructure);

    // ==== SPI init ====
    // SI4432 works at 10MHz max, setup APB2 clk and SPI divider correctly (see system_kl.h for APB2 clk)
    SPI_InitTypeDef SPI_InitStructure;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA      = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft;
    SPI_InitStructure.SPI_FirstBit  = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_Init(SPI1, &SPI_InitStructure);
    // Enable SPI
    SPI_Cmd(SPI1, ENABLE);
}

void SiRFConfig (void) {
    // Setup carrier frequency
    SiWriteRegister(0x75, SI_R75);
    SiWriteRegister(0x76, SI_R76);
    SiWriteRegister(0x77, SI_R77);
    // Output power
    SiWriteRegister(0x6D, SI_R6D);
    // GPIO setup
    SiWriteRegister(0x0B, SI_R0B);
    SiWriteRegister(0x0C, SI_R0C);
    SiWriteRegister(0x0D, SI_R0D);
    // Setup AFC
    SiWriteRegister(0x1D, SI_R1D);
    SiWriteRegister(0x1E, SI_R1E);
    SiWriteRegister(0x2A, SI_R2A);
    // Setup modem
    SiWriteRegister(0x1C, SI_R1C);
    SiWriteRegister(0x1F, SI_R1F);
    SiWriteRegister(0x20, SI_R20);
    SiWriteRegister(0x21, SI_R21);
    SiWriteRegister(0x22, SI_R22);
    SiWriteRegister(0x23, SI_R23);
    SiWriteRegister(0x24, SI_R24);
    SiWriteRegister(0x25, SI_R25);
    SiWriteRegister(0x6E, SI_R6E);
    SiWriteRegister(0x6F, SI_R6F);
    SiWriteRegister(0x70, SI_R70);
    // Deviation
    SiWriteRegister(0x71, SI_R71);
    SiWriteRegister(0x72, SI_R72);
    // Packet structure
    SiWriteRegister(0x30, SI_R30);
    SiWriteRegister(0x32, SI_R32);
    SiWriteRegister(0x33, SI_R33);
    SiWriteRegister(0x34, SI_R34);
    SiWriteRegister(0x35, SI_R35);
    SiWriteRegister(0x36, SI_R36);
    SiWriteRegister(0x37, SI_R37);
    // Headers
    SiWriteRegister(0x3F, SI_R3F);
    SiWriteRegister(0x40, SI_R40);
    SiWriteRegister(0x41, SI_R41);
    SiWriteRegister(0x42, SI_R42);
    SiWriteRegister(0x43, SI_R43);
    SiWriteRegister(0x44, SI_R44);
    SiWriteRegister(0x45, SI_R45);
    SiWriteRegister(0x46, SI_R46);
    // Crystal capacitors
    SiWriteRegister(0x09, SI_R09);

}


uint8_t SiReadWriteByte (uint8_t AByte) {
    SPI1->DR = AByte;
    while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));    // Wait for SPI transmission to complete
    return SPI1->DR;
}

