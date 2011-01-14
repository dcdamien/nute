#include "si4432.h"
#include "delay_util.h"
#include "uart.h"

// Variables
Si_t Si;
#ifdef SI_DOUBLE
Si_t Si2;
#endif

// ============================ Implementation =================================
void Si_t::Init(SPI_TypeDef* ASPI, const SiBitrate_t ABitrate, const SiBand_t ABand) {
    GPIO_InitTypeDef GPIO_InitStructure;
    // ==== Variables init ====
    NewPacketReceived = false;
    TX_Pkt.PacketID = 0;
    // ==== Hardware init ====
    FSPI  = ASPI;
    SPI_Setup(FSPI);
    if (FSPI == SPI1) {
        FGPIO = GPIOA;
        SDN   = GPIO_Pin_0; // Shutdown pin
        NIRQ  = GPIO_Pin_1; // IRQ pin
        NSEL  = GPIO_Pin_8; // CS pin
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if (FSPI == SPI2) {
        FGPIO = GPIOB;
        SDN   = GPIO_Pin_11;
        NIRQ  = GPIO_Pin_10;
        NSEL  = GPIO_Pin_12;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }
    // Configure SDN & NSEL as Push Pull outputs
    GPIO_InitStructure.GPIO_Pin  = NSEL | SDN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(FGPIO, &GPIO_InitStructure);
    // Configure NIRQ as Pull-up input
    GPIO_InitStructure.GPIO_Pin  = NIRQ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(FGPIO, &GPIO_InitStructure);
    // ==== Init registers ====
    SwitchOn();
    Delay.ms(27);           // Wait at least 27ms before any initialization SPI commands are sent to the radio
    this->IRQsRead();       // Release nIRQ pin
    SetMode (SI_MODE_RESET);// Perform reset of all registers
    IRQWait();              // Wait for chip to become ready
    RF_Config(ABitrate, ABand);
    SetPower(7);        // Maximum
    //SetPower(0);        // Minimum
    IRQsSet(SI_IRQ1_NONE, SI_IRQ2_NONE);
}

void Si_t::TransmitPkt(void) {
    FIFOWrite(Si.TX_PktArray, Si.PktLength);    // Place TX packet to FIFO
    SetMode(SI_MODE_TX);   // Enter TX mode
}

void Si_t::FIFOWrite(uint8_t* PData, uint8_t ALen) {
    uint8_t FData = 0x7F | 0x80;        // Write to FIFO register = 0x7F
    NSEL_Lo();
    FSPI->DR = FData;                   // Write FIFO address
    for (uint8_t i=0; i<ALen; i++) {    // Iterate data
        SPI_BusyWait(FSPI);             // Wait for SPI transmission to complete
        FData = FSPI->DR;               // Dummy read to reset RXNE flag
        FSPI->DR = *PData++;            // Write data
    }
    SPI_BusyWait(FSPI);                 // Wait for SPI transmission to complete
    NSEL_Hi();
    FData = FSPI->DR;                   // Dummy read to reset RXNE flag
}
void Si_t::FIFORead (void) {
    NSEL_Lo();
    SPI_ReadWriteByte(FSPI, 0x7F);  // Write FIFO address
    for (uint8_t i=0; i<PktLength; i++) RX_PktArray [i] = SPI_ReadWriteByte(FSPI, 0);
    NSEL_Hi();
}

void Si_t::IRQsSet (uint8_t AIRQ1, uint8_t AIRQ2) {
    WriteRegister(0x05, AIRQ1);
    WriteRegister(0x06, AIRQ2);
    this->IRQsRead();
}
void Si_t::IRQsRead (void) {
    IRQ1 = ReadRegister(0x03);  //read the Interrupt Status1 register
    IRQ2 = ReadRegister(0x04);  //read the Interrupt Status2 register
}

// Radio control

// ============================== Inner use ====================================
void Si_t::WriteRegister (const uint8_t Addr, const uint8_t AData) {
    NSEL_Lo();
    SPI_ReadWriteByte (FSPI, Addr | 0x80);  // Send Addr with Write flag
    SPI_ReadWriteByte (FSPI, AData);        // Send data
    NSEL_Hi();
}
uint8_t Si_t::ReadRegister (const uint8_t Addr) {
    uint8_t Rpl;
    NSEL_Lo();
    SPI_ReadWriteByte (FSPI, Addr);
    Rpl =  SPI_ReadWriteByte (FSPI, 0);
    NSEL_Hi();
    return Rpl;
}


// ============================ Radio settings =================================
void Si_t::RF_Config(const SiBitrate_t ABitrate, const SiBand_t ABand) {
    // ==== Bitrate ====
    switch (ABitrate) {
        case br10000:
            // Setup modem
            WriteRegister(0x1C, 0x1E);  // IF Filter Bandwidth
            WriteRegister(0x1F, 0x03);  // Clock Recovery Gearshift Override. Got from Excel. TEST it, as datashit proposes 0x05.
            WriteRegister(0x20, 0xC8);  // Clock Recovery Oversampling Rate.
            WriteRegister(0x21, 0x00);  // Clock Recovery Offset 2
            WriteRegister(0x22, 0xA3);  // Clock Recovery Offset 1
            WriteRegister(0x23, 0xD7);  // Clock Recovery Offset 0
            WriteRegister(0x24, 0x00);  // Clock Recovery Timing Loop Gain 1
            WriteRegister(0x25, 0x26);  // Clock Recovery Timing Loop Gain 0
            WriteRegister(0x6E, 0x51);  // TX Data Rate 1
            WriteRegister(0x6F, 0xEC);  // TX Data Rate 0
            WriteRegister(0x70, 0x21);  // Modulation Mode Control 1: txdtrtscale=1 as datarate<30kbps, data whitening enabled. TEST enphpwdn
            break;
    }

    // ==== RF Band ====
    switch (ABand) {
        case bnd310:
            break;
        case bnd868:
            // Setup carrier frequency
            WriteRegister(0x75, 0x73);    // Frequency Band Select
            WriteRegister(0x76, 0x64);    // }
            WriteRegister(0x77, 0x00);    // } Nominal Carrier Frequency
            break;
    }
    // ==== Common settings ====
    // GPIO setup
    WriteRegister(0x0B, 0x12);  // GPIO0: set when TX
    WriteRegister(0x0C, 0x15);  // GPIO1: set when RX
    WriteRegister(0x0D, 0x00);  // GPIO2: clock output
    // Crystal capacitors
    WriteRegister(0x09, 0x7F);

    // Setup AFC
    WriteRegister(0x1D, 0x40);  // AFC Loop Gearshift Override: AFC enable, feedback loop gain = 1.5. Got from Excel.
    WriteRegister(0x1E, 0x0A);  // AFC Timing Control: default value
    WriteRegister(0x2A, 0x00);  // AFC limiter: 0 is default, 0x20 is from China

    // Modulation & Deviation 45 kHz
    WriteRegister(0x71, 0x23);  // Modulation Mode Control 2. Enable FIFO. Setup GFSK. MSB of deviation=0.
    // WriteRegister(0x71, 0x22);// Modulation Mode Control 2. Enable FIFO. Setup FSK. MSB of deviation=0.
    WriteRegister(0x72, 0x48);  // Frequency Deviation

    // Packet structure
    WriteRegister(0x30, 0x8D);  // Enable RX & TX packet handler and CRC-16 (IBM) check
    WriteRegister(0x32, 0x00);  // Header Control 1: No broadcast, no header check
    WriteRegister(0x33, 0x02);  // Header Control 2: Disable header bytes, set variable length, set sync to two bytes, preamble length's MSB=0
    WriteRegister(0x34, 0x08);  // Preamble length: number of nibbles (4 bits). 8 * 4 = 32 bits = 4 bytes
    WriteRegister(0x35, 0x2A);  // Preamble Detection Control 1: 5 nibbles are to be received correctly. RSSI offset is 101
    WriteRegister(0x36, 0x2D);  // }
    WriteRegister(0x37, 0xD4);  // } Sync word = 2DD4

    // Headers
    WriteRegister(0x3F, 0);
    WriteRegister(0x40, 0);
    WriteRegister(0x41, 0);
    WriteRegister(0x42, 0);
    WriteRegister(0x43, 0xFF);
    WriteRegister(0x44, 0xFF);
    WriteRegister(0x45, 0xFF);
    WriteRegister(0x46, 0xFF);

    // FIFO settings
    //WriteRegister(0x08, 0x00);// MultiPacket disable, auto transmit disable, LowDutyCycle disable
}
