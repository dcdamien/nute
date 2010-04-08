/* 
 * File:   cc1101.c
 * Author: Laurelindo
 *
 * Created on 06/03/2010 г., 2:08
 */

#include <util/delay.h>
#include <inttypes.h>
#include "cc1101.h"
#include "time_utils.h"
// DEBUG
#include "uart_unit.h"
#include "ledskeys.h"

struct CC_t CC;

void CC_Task (void){
    uint8_t InnerState, FifoSize;
    // Check state
    InnerState = CC_ReadRegister(CC_MARCSTATE);     // Get status
    switch (CC.State){
        case CC_Idle:
            // Wait if temporary state
            if (InnerState==CC_ST_FS_WAKEUP6 || InnerState==CC_ST_FS_WAKEUP7 || InnerState==CC_ST_CALIBRATE8 || InnerState==CC_ST_SETTLING9 || InnerState==CC_ST_SETTLING10 || InnerState==CC_ST_SETTLING11 || InnerState==CC_ST_FSTXON)
                return;
            // Wait if still transmitting
            if (InnerState==CC_ST_TX19 || InnerState==CC_ST_TX20) return;

            if (CC.NeededState == CC_RX) {
                CC_ENTER_RX();
                CC.State = CC_RX;
            }
            return;
            break;


        case CC_RX:
            if (CC.NeededState != CC_RX) {
                CC_ENTER_IDLE();
                CC.State = CC_Idle;
            }
            // Check if something is recieved
            if (CC_GDO0_IS_HI()){ // GDO0 asserts when packet has been recieved, and CRC ok
                FifoSize = CC_ReadRegister(CC_RXBYTES); // Get bytes in FIFO
                if (FifoSize > 0) {
                    //UARTSendUint(FifoSize);
                    //UARTNewLine();
                    CC_ReadRX(&CC.PctArray[0], FifoSize);
                    CC_PrintPacket();
                }
            } // if gdo high
            break;

        default: break;
    } // switch
}

void CC_Init(void){
    // ******** Hardware init section *******
    // Setup ports
    CC_DDR  &= ~((1<<CC_GDO0)|(1<<CC_GDO2)|(1<<CC_MISO));
    CC_DDR  |=   (1<<CC_CS)|(1<<CC_MOSI)|(1<<CC_SCLK);
    CC_PORT |=   (1<<CC_GDO0)|(1<<CC_GDO2)|(CC_MISO); // Enable pull-ups
    // Set initial values
    CC_SCLK_LO;
    CC_CS_HI;
    // Setup SPI: MSB first, master, SCK idle low, f/4
    SPCR = (0<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(0<<SPR1)|(0<<SPR0);
    SPSR = (1<<SPI2X);

    // ******* Firmware init section *******
    CC.State = CC_Idle;
    CC.Address = 4; // DEBUG
    TimerResetDelay(&CC.Timer);
    CC.PPacket = (CC_Packet_p)&CC.PctArray[0];  // treat array as structure
    CC_RESET();
    CC_FLUSH_RX_FIFO();
    CC_RfConfig();
}

void CC_TransmitPacket(void){
    // Packet must be prepared already
    uint8_t InnerState = CC_ReadRegister(CC_MARCSTATE); // Get radio status
    CC_WriteTX (&CC.PctArray[0], CC_PKT_LENGTH);        // Write bytes to FIFO
    CC.State = CC_Idle;                                 // Packet is now sent
    if (InnerState!=CC_ST_TX19 && InnerState!=CC_ST_TX20) CC_ENTER_TX();    // Enter TX mode if not in it
}

#ifdef CC_PRINT_DEBUG
void CC_PrintPacket(void){
    for (uint8_t i=0; i<CC_PKT_LENGTH+2; i++){
        UARTSendAsHex(CC.PctArray[i], 1);
        UARTSendByte(' ');
    }
    UARTNewLine();
}
#endif


void CC_PreparePacket(void){
    CC.PPacket->Address = 4;    // Recipient address
    CC.PPacket->PacketID = 0;   // Current packet ID, to avoid repeative treatment
    CC.PPacket->CommandID = 1;  // Something to test
    for (uint8_t i=0; i<CC_PKT_LENGTH-3; i++) CC.PPacket->Data[i] = i;    // Something to test
}

// ============================= Inner use =====================================
void CC_WriteBurst(uint8_t ARegAddr, uint8_t *PData, uint8_t ALength){
    CC_CS_LO;                                                   // Start transmission
    while (CC_MISO_IS_HI());                                      // Wait for chip to become ready
    CC_WriteByte(ARegAddr|CC_WRITE_FLAG|CC_BURST_FLAG);         // Address with write & burst flags
    for (uint8_t i=0; i<ALength; i++) CC_WriteByte(*PData++);   // Write bytes themselves
    CC_CS_HI;                                                   // End transmission
}
void CC_WriteBurst_P(uint8_t ARegAddr, prog_uint8_t *PData, uint8_t ALength){
    CC_CS_LO;                                                   // Start transmission
    while (CC_MISO_IS_HI());                                      // Wait for chip to become ready
    CC_WriteByte(ARegAddr|CC_WRITE_FLAG|CC_BURST_FLAG);         // Address with write & burst flags
    for (uint8_t i=0; i<ALength; i++) CC_WriteByte(pgm_read_byte (PData++));   // Write bytes themselves
    CC_CS_HI;                                                   // End transmission
}

void CC_WriteTX (uint8_t *PData, uint8_t ALength){
    CC_WriteBurst(CC_FIFO, PData, ALength);
}
void CC_ReadRX  (uint8_t *PData, uint8_t ALength){
    CC_CS_LO;                                                   // Start transmission
    while (CC_MISO_IS_HI());                                      // Wait for chip to become ready
    CC_WriteByte(CC_FIFO|CC_READ_FLAG|CC_BURST_FLAG);           // Address with read & burst flags
    for (uint8_t i=0; i<ALength; i++) *PData++ = CC_ReadByte(); // Write bytes themselves
    CC_CS_HI;                                                   // End transmission
}

uint8_t CC_ReadRegister (uint8_t ARegAddr){
    CC_CS_LO;                               // Start transmission
    while (CC_MISO_IS_HI());                // Wait for chip to become ready
    CC_WriteByte(ARegAddr | CC_READ_FLAG);  // Transmit header byte: set READ bit and BURST flag
    uint8_t FReply = CC_ReadByte();         // Read reply
    CC_CS_HI;                               // End transmission
    return FReply;
}
void CC_WriteRegister (uint8_t ARegAddr, uint8_t AData){
    CC_CS_LO;               // Start transmission
    while (CC_MISO_IS_HI());// Wait for chip to become ready
    CC_WriteByte(ARegAddr); // Transmit header byte
    CC_WriteByte(AData);    // Write data
    CC_CS_HI;               // End transmission
}
void CC_WriteStrobe (uint8_t AStrobe){
    CC_CS_LO;               // Start transmission
    while (CC_MISO_IS_HI());// Wait for chip to become ready
    CC_WriteByte(AStrobe);  // Write strobe
    CC_CS_HI;               // End transmission
}

// **** Used to setup CC with needed values ****
void CC_RfConfig(void){
    CC_WriteRegister(CC_FSCTRL1,  CC_FSCTRL1_VALUE);    // Frequency synthesizer control.
    CC_WriteRegister(CC_FSCTRL0,  CC_FSCTRL0_VALUE);    // Frequency synthesizer control.
    CC_WriteRegister(CC_FREQ2,    CC_FREQ2_VALUE);      // Frequency control word, high byte.
    CC_WriteRegister(CC_FREQ1,    CC_FREQ1_VALUE);      // Frequency control word, middle byte.
    CC_WriteRegister(CC_FREQ0,    CC_FREQ0_VALUE);      // Frequency control word, low byte.
    CC_WriteRegister(CC_MDMCFG4,  CC_MDMCFG4_VALUE);    // Modem configuration.
    CC_WriteRegister(CC_MDMCFG3,  CC_MDMCFG3_VALUE);    // Modem configuration.
    CC_WriteRegister(CC_MDMCFG2,  CC_MDMCFG2_VALUE);    // Modem configuration.
    CC_WriteRegister(CC_MDMCFG1,  CC_MDMCFG1_VALUE);    // Modem configuration.
    CC_WriteRegister(CC_MDMCFG0,  CC_MDMCFG0_VALUE);    // Modem configuration.
    CC_WriteRegister(CC_CHANNR,   CC_CHANNR_VALUE);     // Channel number.
    CC_WriteRegister(CC_DEVIATN,  CC_DEVIATN_VALUE);    // Modem deviation setting (when FSK modulation is enabled).
    CC_WriteRegister(CC_FREND1,   CC_FREND1_VALUE);     // Front end RX configuration.
    CC_WriteRegister(CC_FREND0,   CC_FREND0_VALUE);     // Front end RX configuration.
    CC_WriteRegister(CC_MCSM0,    CC_MCSM0_VALUE);      // Main Radio Control State Machine configuration.
    CC_WriteRegister(CC_FOCCFG,   CC_FOCCFG_VALUE);     // Frequency Offset Compensation Configuration.
    CC_WriteRegister(CC_BSCFG,    CC_BSCFG_VALUE);      // Bit synchronization Configuration.
    CC_WriteRegister(CC_AGCCTRL2, CC_AGCCTRL2_VALUE);   // AGC control.
    CC_WriteRegister(CC_AGCCTRL1, CC_AGCCTRL1_VALUE);   // AGC control.
    CC_WriteRegister(CC_AGCCTRL0, CC_AGCCTRL0_VALUE);   // AGC control.
    CC_WriteRegister(CC_FSCAL3,   CC_FSCAL3_VALUE);     // Frequency synthesizer calibration.
    CC_WriteRegister(CC_FSCAL2,   CC_FSCAL2_VALUE);     // Frequency synthesizer calibration.
    CC_WriteRegister(CC_FSCAL1,   CC_FSCAL1_VALUE);     // Frequency synthesizer calibration.
    CC_WriteRegister(CC_FSCAL0,   CC_FSCAL0_VALUE);     // Frequency synthesizer calibration.
    CC_WriteRegister(CC_FSTEST,   CC_FSTEST_VALUE);     // Frequency synthesizer calibration.
    CC_WriteRegister(CC_TEST2,    CC_TEST2_VALUE);      // Various test settings.
    CC_WriteRegister(CC_TEST1,    CC_TEST1_VALUE);      // Various test settings.
    CC_WriteRegister(CC_TEST0,    CC_TEST0_VALUE);      // Various test settings.
    CC_WriteRegister(CC_FIFOTHR,  CC_FIFOTHR_VALUE);    // fifo threshold
    CC_WriteRegister(CC_IOCFG2,   CC_IOCFG2_VALUE);     // GDO2 output pin configuration.
    CC_WriteRegister(CC_IOCFG0,   CC_IOCFG0_VALUE);     // GDO0 output pin configuration.
    CC_WriteRegister(CC_PKTCTRL1, CC_PKTCTRL1_VALUE);   // Packet automation control.
    CC_WriteRegister(CC_PKTCTRL0, CC_PKTCTRL0_VALUE);   // Packet automation control.
    CC_WriteRegister(CC_ADDR,     CC_ADDR_VALUE);       // Device address.
    CC_WriteRegister(CC_PKTLEN,   CC_PKTLEN_VALUE);     // Packet length.

    CC_WriteRegister(CC_PATABLE, CC_PATABLE0_VALUE);
    
    CC_WriteRegister(CC_MCSM2, CC_MCSM2_VALUE);
    CC_WriteRegister(CC_MCSM1, CC_MCSM1_VALUE);
}


// ============================= Low level =====================================
uint8_t CC_ReadWriteByte(uint8_t AByte){
    SPDR = AByte;	// Start transmission
    // Wait for transmission to complete
    while (bit_is_clear (SPSR, SPIF));
    uint8_t Response = SPDR;
    return Response;
}

