/*
 * cc1101.cpp
 *
 *  Created on: Feb 12, 2013
 *      Author: g.kruglov
 */

#include "cc1101.h"

cc1101_t CC;

void cc1101_t::Init() {
    // ==== GPIO ====
    PinSetupOut      (GPIOA, CC_CS,   omPushPull, pudNone);
    PinSetupAlterFunc(GPIOA, CC_SCK,  omPushPull, pudNone, AF5);
    PinSetupAlterFunc(GPIOA, CC_MISO, omPushPull, pudNone, AF5);
    PinSetupAlterFunc(GPIOA, CC_MOSI, omPushPull, pudNone, AF5);
    PinSetupIn       (GPIOA, CC_GDO0, pudNone);
    PinSetupIn       (GPIOA, CC_GDO2, pudNone);
    CsHi();

    // ==== SPI ====    MSB first, master, SCK idle low, Baudrate=f/2
    rccEnableSPI1(FALSE);
    // NoCRC, FullDuplex, 8bit, MSB, Baudrate, Master, ClkLowIdle(CPOL=0),
    // FirstEdge(CPHA=0), NSS software controlled and is 1
    CC_SPI->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_MSTR;
    CC_SPI->CR2 = 0;
    CC_SPI->I2SCFGR &= ~((uint16_t)SPI_I2SCFGR_I2SMOD);
    CC_SPI->CR1 |= SPI_CR1_SPE; // Enable SPI

    // ==== Init CC ====
    CReset();
    FlushRxFIFO();
    RfConfig();

    GetState();
    Uart.Printf("CC: %X\r", IState);


    // ==== IRQs ====
//    IrqPin0.Init(GPIOA, 4, GPIO_Mode_IPD);
//    IrqPin0.IrqSetup(EXTI_Trigger_Falling);
//    IrqPin0.IrqEnable();
}

// ========================== TX, RX, freq and power ===========================
void cc1101_t::SetChannel(uint8_t AChannel) {
    // CC must be in IDLE mode
    while(IState != CC_STB_IDLE) EnterIdle();
    // Now set channel
    WriteRegister(CC_CHANNR, AChannel);
}

//void cc1101_t::WaitUntilChannelIsBusy() {
//    uint8_t b;
//    for(uint32_t i=0; i<207; i++) {
//        b = ReadRegister(CC_PKTSTATUS);
//        if(b & 0b00010000) break;
//        //Uart.Printf("C");
//    }
//    //Uart.Printf("\r");
//}

void cc1101_t::Transmit(void *Ptr, uint8_t Length) {
    // WaitUntilChannelIsBusy();   // If this is not done, time after time FIFO is destroyed
    do {
        EnterIdle();
    } while(IState != CC_STB_IDLE);
    WriteTX((uint8_t*)Ptr, Length);
    EnterTX();
}
void cc1101_t::TransmitAndWaitIdle(void *Ptr, uint8_t Length) {
    Transmit(Ptr, Length);
    while(!GDO0IsHi());     // Wait until sync word is sent
    while(GDO0IsHi());      // Wait until transmission completed
}

void cc1101_t::Receive(void) {
    while(IState != CC_STB_IDLE) EnterIdle();
    //Aim = caRx;
    EnterRX();  // After that, some time will be wasted to recalibrate
}

// Return RSSI in dBm
int16_t cc1101_t::RSSI_dBm(uint8_t ARawRSSI) {
    int16_t RSSI = ARawRSSI;
    if (RSSI >= 128) RSSI -= 256;
    RSSI = (RSSI / 2) - 74;    // now it is in dBm
    return RSSI;
}


// =========================== Registers & Strobes =============================
uint8_t cc1101_t::ReadWriteByte(uint8_t AByte) {
    CC_SPI->DR = AByte;
    while (!(CC_SPI->SR & SPI_SR_RXNE));  // Wait for SPI transmission to complete
    return CC_SPI->DR;
}

uint8_t cc1101_t::ReadRegister (uint8_t ARegAddr){
    CsLo();                                 // Start transmission
    BusyWait();                             // Wait for chip to become ready
    ReadWriteByte(ARegAddr | CC_READ_FLAG); // Transmit header byte
    uint8_t FReply = ReadWriteByte(0);      // Read reply
    CsHi();                                 // End transmission
    return FReply;
}
void cc1101_t::WriteRegister (uint8_t ARegAddr, uint8_t AData){
    CsLo();                     // Start transmission
    BusyWait();                 // Wait for chip to become ready
    ReadWriteByte(ARegAddr);    // Transmit header byte
    ReadWriteByte(AData);       // Write data
    CsHi();                     // End transmission
}
void cc1101_t::WriteStrobe (uint8_t AStrobe){
    CsLo();                             // Start transmission
    BusyWait();                         // Wait for chip to become ready
    IState = ReadWriteByte(AStrobe);    // Write strobe
    CsHi();                             // End transmission
    IState &= 0b01110000;               // Mask needed bits
}

void cc1101_t::WriteTX(uint8_t* Ptr, uint8_t Length) {
    CsLo();                                                 // Start transmission
    BusyWait();                                             // Wait for chip to become ready
    ReadWriteByte(CC_FIFO|CC_WRITE_FLAG|CC_BURST_FLAG);     // Address with write & burst flags
    uint8_t b;
    //Uart.Printf("TX: ");
    for (uint8_t i=0; i<Length; i++) {
        b = *Ptr++;
        ReadWriteByte(b);  // Write bytes
      //  Uart.Printf("%X ", b);
    }
    CsHi();    // End transmission
    //Uart.Printf("\r");
}

// ==== Used to setup CC with needed values ====
void cc1101_t::RfConfig() {
    WriteRegister(CC_FSCTRL1,  CC_FSCTRL1_VALUE);    // Frequency synthesizer control.
    WriteRegister(CC_FSCTRL0,  CC_FSCTRL0_VALUE);    // Frequency synthesizer control.
    WriteRegister(CC_FREQ2,    CC_FREQ2_VALUE);      // Frequency control word, high byte.
    WriteRegister(CC_FREQ1,    CC_FREQ1_VALUE);      // Frequency control word, middle byte.
    WriteRegister(CC_FREQ0,    CC_FREQ0_VALUE);      // Frequency control word, low byte.
    WriteRegister(CC_MDMCFG4,  CC_MDMCFG4_VALUE);    // Modem configuration.
    WriteRegister(CC_MDMCFG3,  CC_MDMCFG3_VALUE);    // Modem configuration.
    WriteRegister(CC_MDMCFG2,  CC_MDMCFG2_VALUE);    // Modem configuration.
    WriteRegister(CC_MDMCFG1,  CC_MDMCFG1_VALUE);    // Modem configuration.
    WriteRegister(CC_MDMCFG0,  CC_MDMCFG0_VALUE);    // Modem configuration.
    WriteRegister(CC_CHANNR,   CC_CHANNR_VALUE);     // Channel number.
    WriteRegister(CC_DEVIATN,  CC_DEVIATN_VALUE);    // Modem deviation setting (when FSK modulation is enabled).
    WriteRegister(CC_FREND1,   CC_FREND1_VALUE);     // Front end RX configuration.
    WriteRegister(CC_FREND0,   CC_FREND0_VALUE);     // Front end RX configuration.
    WriteRegister(CC_MCSM0,    CC_MCSM0_VALUE);      // Main Radio Control State Machine configuration.
    WriteRegister(CC_FOCCFG,   CC_FOCCFG_VALUE);     // Frequency Offset Compensation Configuration.
    WriteRegister(CC_BSCFG,    CC_BSCFG_VALUE);      // Bit synchronization Configuration.
    WriteRegister(CC_AGCCTRL2, CC_AGCCTRL2_VALUE);   // AGC control.
    WriteRegister(CC_AGCCTRL1, CC_AGCCTRL1_VALUE);   // AGC control.
    WriteRegister(CC_AGCCTRL0, CC_AGCCTRL0_VALUE);   // AGC control.
    WriteRegister(CC_FSCAL3,   CC_FSCAL3_VALUE);     // Frequency synthesizer calibration.
    WriteRegister(CC_FSCAL2,   CC_FSCAL2_VALUE);     // Frequency synthesizer calibration.
    WriteRegister(CC_FSCAL1,   CC_FSCAL1_VALUE);     // Frequency synthesizer calibration.
    WriteRegister(CC_FSCAL0,   CC_FSCAL0_VALUE);     // Frequency synthesizer calibration.
    WriteRegister(CC_TEST2,    CC_TEST2_VALUE);      // Various test settings.
    WriteRegister(CC_TEST1,    CC_TEST1_VALUE);      // Various test settings.
    WriteRegister(CC_TEST0,    CC_TEST0_VALUE);      // Various test settings.
    WriteRegister(CC_FIFOTHR,  CC_FIFOTHR_VALUE);    // fifo threshold
    WriteRegister(CC_IOCFG2,   CC_IOCFG2_VALUE);     // GDO2 output pin configuration.
    WriteRegister(CC_IOCFG0,   CC_IOCFG0_VALUE);     // GDO0 output pin configuration.
    WriteRegister(CC_PKTCTRL1, CC_PKTCTRL1_VALUE);   // Packet automation control.
    WriteRegister(CC_PKTCTRL0, CC_PKTCTRL0_VALUE);   // Packet automation control.
    WriteRegister(CC_PKTLEN,   12);                  // Packet length, dummy

    WriteRegister(CC_PATABLE, CC_PATABLE_INITIAL);

    WriteRegister(CC_MCSM2, CC_MCSM2_VALUE);
    WriteRegister(CC_MCSM1, CC_MCSM1_VALUE);
}

