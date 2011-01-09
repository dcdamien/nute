/* 
 * File:   si4432_rfconfig.h
 * Author: Kreyl Laurelindo
 *
 * Created on 27 Декабрь 2010 г., 22:40
 */

#ifndef SI4432_RFCONFIG_H
#define	SI4432_RFCONFIG_H

// Settings
#define SI_BAND_868
#define SI_DATARATE_10K
#define SI_DATA_WHITENING_ENABLE

// =================================== Defines =================================
// Operation modes
#define SI_READY    0x01
#define SI_RX       0x05
#define SI_TX       0x09
#define SI_RESET    0x80

#define SI_R08      0x00    // MultiPacket disable, auto transmit disable, LowDutyCycle disable

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
#define SI_IRQ2_CHIP_READY   0x02

// Carrier frequency
#ifdef SI_BAND_868
#define SI_R75  0x73    // Frequency Band Select
#define SI_R76  0x64    // }
#define SI_R77  0x00    // } Nominal Carrier Frequency
#endif
// Output power
#define SI_R6D  0x08    // LNA switch = 0, output power = 000(min)

// GPIO setup
#define SI_R0B  0x12    // GPIO0: set when TX
#define SI_R0C  0x15    // GPIO1: set when RX
#define SI_R0D  0x00    // GPIO2: clock output

// AFC
#define SI_R1D  0x40    // AFC Loop Gearshift Override: AFC enable, feedback loop gain = 1.5. Got from Excel.
#define SI_R1E  0x0A    // AFC Timing Control: default value
#define SI_R2A  0x00    // AFC limiter: 0 is default, 0x20 is from China

// Modem settings
#ifdef SI_DATARATE_10K
#define SI_R1C  0x1E    // IF Filter Bandwidth, got from Excel
#define SI_R1F  0x03    // Clock Recovery Gearshift Override. Got from Excel. TEST it, as datashit proposes 0x05.
#define SI_R20  0xC8    // Clock Recovery Oversampling Rate. Got from Excel.
#define SI_R21  0x00    // Clock Recovery Offset 2
#define SI_R22  0xA3    // Clock Recovery Offset 1
#define SI_R23  0xD7    // Clock Recovery Offset 0
#define SI_R24  0x00    // Clock Recovery Timing Loop Gain 1
#define SI_R25  0x26    // Clock Recovery Timing Loop Gain 0
#define SI_R6E  0x51    // TX Data Rate 1
#define SI_R6F  0xEC    // TX Data Rate 0
#ifdef SI_DATA_WHITENING_ENABLE
#define SI_R70  0x21    // Modulation Mode Control 1: txdtrtscale=1 as datarate<30kbps, data whitening enabled. TEST enphpwdn
#else
#define SI_R70  0x20
#endif
#endif  // if 10k

// Modulation & Deviation 45 kHz
#define SI_R71  0x23    // Modulation Mode Control 2. Enable FIFO. Setup GFSK. MSB of deviation=0.
//#define SI_R71  0x22    // Modulation Mode Control 2. Enable FIFO. Setup FSK. MSB of deviation=0.
#define SI_R72  0x48    // Frequency Deviation

// Packet structure
#define SI_R30  0x8D    // Enable RX & TX packet handler and CRC-16 (IBM) check
#define SI_R32  0x00    // Header Control 1: No broadcast, no header check
#define SI_R33  0x02    // Header Control 2: Disable header bytes, set variable length, set sync to two bytes, preamble length's MSB=0
#define SI_R34  0x08    // Preamble length: number of nibbles (4 bits). 8 * 4 = 32 bits = 4 bytes
#define SI_R35  0x2A    // Preamble Detection Control 1: 5 nibbles are to be received correctly. RSSI offset is 101
#define SI_R36  0x2D    // }
#define SI_R37  0xD4    // } Sync word = 2DD4

// Headers
#define SI_R3F  0x00
#define SI_R40  0x00
#define SI_R41  0x00
#define SI_R42  0x00
#define SI_R43  0xFF
#define SI_R44  0xFF
#define SI_R45  0xFF
#define SI_R46  0xFF

// Crystal capacitors
#define SI_R09  0x7F



#endif	/* SI4432_RFCONFIG_H */

