#include "spi.h"
#include "stm32f10x_spi.h"

// ==== SPI1 ====
// Pins
#define SPI1_GPIO   GPIOA
#define SPI1_SCK    GPIO_Pin_5  // SCK
#define SPI1_MISO   GPIO_Pin_6  // MISO
#define SPI1_MOSI   GPIO_Pin_7  // MOSI

#define SPI2_GPIO   GPIOB
#define SPI2_SCK    GPIO_Pin_13  // SCK
#define SPI2_MISO   GPIO_Pin_14  // MISO
#define SPI2_MOSI   GPIO_Pin_15  // MOSI



// =============================== Implementation ==============================
void SPI_Setup(SPI_TypeDef* ASPI) {
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;
    if (ASPI == SPI1) {
        // ==== Clocks init ====
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
        // ==== GPIO init ====
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        // Configure MOSI & SCK as Alternate Function Push Pull
        GPIO_InitStructure.GPIO_Pin  = SPI1_SCK | SPI1_MOSI;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);
        // Configure MISO as Input Floating
        GPIO_InitStructure.GPIO_Pin  = SPI1_MISO;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);
        // ==== SPI init ====
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
        SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;
        SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;
        SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low;
        SPI_InitStructure.SPI_CPHA      = SPI_CPHA_1Edge;
        SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft;
        SPI_InitStructure.SPI_FirstBit  = SPI_FirstBit_MSB;
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    } // if
    else if (ASPI == SPI2) {
        // ==== Clocks init ====
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,  ENABLE);
        // ==== GPIO init ====
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        // Configure MOSI & SCK as Alternate Function Push Pull
        GPIO_InitStructure.GPIO_Pin  = SPI2_SCK | SPI2_MOSI;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(SPI2_GPIO, &GPIO_InitStructure);
        // Configure MISO as Input Floating
        GPIO_InitStructure.GPIO_Pin  = SPI2_MISO;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(SPI2_GPIO, &GPIO_InitStructure);
        // ==== SPI init ====
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
        SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;
        SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;
        SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low;
        SPI_InitStructure.SPI_CPHA      = SPI_CPHA_1Edge;
        SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft;
        SPI_InitStructure.SPI_FirstBit  = SPI_FirstBit_MSB;
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    } // if
    SPI_Init(ASPI, &SPI_InitStructure);
    // Enable SPI
    SPI_Cmd(ASPI, ENABLE);
}

void SPI_BusyWait(const SPI_TypeDef* ASPI) {
    while (!(ASPI->SR & SPI_I2S_FLAG_RXNE));    // Wait for SPI transmission to complete
}

uint8_t SPI_ReadWriteByte (SPI_TypeDef* ASPI, uint8_t AByte) {
    ASPI->DR = AByte;
    SPI_BusyWait(ASPI); // Wait for SPI transmission to complete
    return ASPI->DR;
}