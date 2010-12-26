#include "si4432.h"
#include "stm32f10x_spi.h"
#include "delay_util.h"

// Variables
struct Si_t SI;

// Local prototypes
void SI_SPIInit (void);
void SI_RFConfig (void);

// ============================ Implementation =================================
void SI_Init (void) {
    SI_SPIInit();
    SI.NewPacketReceived = false;
    SI_RFConfig();
    SI_SWITCH_ON();
    
}


// Inner use
void SI_WriteRegister (const uint8_t Addr, const uint8_t AData) {
    // Prepare data
    uint16_t FData = Addr;
    FData <<= 8;
    FData |= AData;
    FData |= 0x8000;    // Set RW bit to 1, indicating write operation
    // Send data
    SI_NSEL_LO();
    SPI1->DR = FData;
    // Wait for SPI transmission to complete
    while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));
    SI_NSEL_HI();
    FData = SPI1->DR;   // Dummy read to reset RXNE flag
}
uint8_t SI_ReadRegister (const uint8_t Addr) {
    // Prepare data
    uint16_t FData = Addr;
    FData <<= 8;
    FData &= 0x7FFF;    // Set RW bit to 0, indicating read operation
    // Exchange data
    SI_NSEL_LO();
    SPI1->DR = FData;
    // Wait for SPI transmission to complete
    while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));
    SI_NSEL_HI();
    return SPI1->DR;
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
    SPI_InitStructure.SPI_DataSize  = SPI_DataSize_16b;
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
    
}


