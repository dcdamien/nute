#include "si4432.h"
#include "stm32f10x_spi.h"
#include "delay_util.h"
#include "si4432_rfconfig.h"

// Variables
struct Si_t SI;

// Local prototypes
void SI_SPIInit (void);
void SI_RFConfig (void);

uint8_t SI_ReadWriteByte (uint8_t AByte);

// ============================ Implementation =================================
void SI_Init (void) {
    SI_SPIInit();
    SI.NewPacketReceived = false;
    SI_SWITCH_ON();
    Delay_ms(15);   // Wait at least 15ms before any initialization SPI commands are sent to the radio
    // Read interrupt status registers to clear the interrupt flags and release NIRQ pin
    SI_ReadRegister(0x03); //read the Interrupt Status1 register
    SI_ReadRegister(0x04); //read the Interrupt Status2 register
    // Perform software reset
    SI_WriteRegister(0x07, 0x80);
    SI_WAIT_IRQ();  // Wait for chip to become ready
    // Read interrupt status registers to clear the interrupt flags and release NIRQ pin
    SI_ReadRegister(0x03); //read the Interrupt Status1 register
    SI_ReadRegister(0x04); //read the Interrupt Status2 register
    SI_RFConfig();
}

void SI_FIFOWrite(uint8_t* PData, uint8_t ALen) {
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
void SI_FIFORead (uint8_t* PData, uint8_t ALen) {
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


// Inner use
void SI_WriteRegister (const uint8_t Addr, const uint8_t AData) {
    SI_NSEL_LO();
    SI_ReadWriteByte (Addr | 0x80); // Send Addr with Write flag
    SI_ReadWriteByte (AData);       // Send data
    SI_NSEL_HI();
}
uint8_t SI_ReadRegister (const uint8_t Addr) {
    uint8_t Rpl;
    SI_NSEL_LO();
    SI_ReadWriteByte (Addr);
    Rpl =  SI_ReadWriteByte (0);
    SI_NSEL_HI();
    return Rpl;
}

void SI_SPIInit (void) {
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

void SI_RFConfig (void) {
    // Setup carrier frequency
    SI_WriteRegister(0x75, SI_R75);
    SI_WriteRegister(0x76, SI_R76);
    SI_WriteRegister(0x77, SI_R77);
    // Setup modem
    SI_WriteRegister(0x6E, SI_R6E);
    SI_WriteRegister(0x6F, SI_R6F);
    SI_WriteRegister(0x70, SI_R70);
    // Deviation
    SI_WriteRegister(0x71, SI_R71);
    SI_WriteRegister(0x72, SI_R72);


}


uint8_t SI_ReadWriteByte (uint8_t AByte) {
    SPI1->DR = AByte;
    while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));    // Wait for SPI transmission to complete
    return SPI1->DR;
}

