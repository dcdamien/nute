/*
 * File:   pkt_settings.h
 * Author: Kreyl Laurelindo
 *
 * Created on 16 Ноябрь 2010 г., 23:40
 *
 * Here lie settings and types of packet used, and any IDs used, too.
 */

#ifndef PKT_SETTINGS_H
#define	PKT_SETTINGS_H

#include <inttypes.h>

// ============================= Defines =======================================
#define TEAR_CHANNEL    8

// ============================== Types ========================================
struct CC_Packet_t {
    uint8_t ToAddr;
    uint16_t PktID;
    uint8_t RSSI;
    uint8_t LQI;
};
#define CC_PKT_LENGTH   (sizeof(struct CC_Packet_t)-2) // exclude RSSI & LQI


#endif	/* PKT_SETTINGS_H */

