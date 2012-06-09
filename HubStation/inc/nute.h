/*
 * nute.h
 *
 *  Created on: 06.05.2012
 *      Author: kreyl
 */

#ifndef NUTE_H_
#define NUTE_H_

#include "stdint.h"
#include "kl_lib.h"
#include "cc1101_rf_settings.h"

// Choose mode - station or tixe
#ifndef NUTE_MODE_STATION
#define NUTE_MODE_TIXE
#endif

// Power levels
#define LOWEST_PWR_LVL_ID   plN30dBm
#define HIGHEST_PWR_LVL_ID  plP5dBm
//#define HIGHEST_PWR_LVL_ID  plN6dBm
#define DESIRED_RSSI        (-90)       // dBm

// Timings
#ifndef NUTE_MODE_STATION
#define RECALIBRATE_DELAY   7002    // ms; recalibrate if no packet received within this time
#endif
#ifdef CC_BITRATE_10K
// Pkt duration is 45 ms
#define REPLY_WAITTIME  108  // ms; delay between start of transmission and end of answer reception, = 2x PktDuration
#elif defined CC_BITRATE_38K4
// Pkt duration is 15 ms
#define REPLY_WAITTIME  33  // ms; delay between start of transmission and end of answer reception, = 2x PktDuration
#elif defined CC_BITRATE_250K
// Pkt duration is 4 ms
#define REPLY_WAITTIME  11  // ms; delay between start of transmission and end of answer reception, = 2x PktDuration
#endif

// Commands and replies
#define NUTE_CMD_PING           0x00
#define NUTE_RPL_PING           0x01
#define NUTE_RPL_UNSUPPORTED    0xFF

struct Situation_t {
    uint8_t State;                  // State of Tixe
    //uint16_t Battery;
    Time_t Time;                    // GPS time
    uint8_t IsFixed, SatCount;      // GPS fix and sattelite count
    uint16_t Precision;             // GPS precision
    int32_t Lattitude, Longitude;   // GPS coordinates
} PACKED;

struct Area_t {     // Size = 1 + 4 * 4 = 17 bytes
    uint8_t ID;
    int32_t TopLeftLattitude, TopLeftLongitude, BottomRightLattitude, BottomRightLongitude;
} PACKED;


struct Pkt_t {
    uint8_t AddrTo;
    uint8_t AddrFrom;
    uint8_t PwrID;
    uint8_t Cmd;
    union {
        uint8_t Arr[18];
        Situation_t Situation;
        Area_t AreaInfo;
    };
    uint8_t RSSI;
    uint8_t LQI;
} PACKED;
#define CC_PKT_LEN  (sizeof(Pkt_t)-2)

#define TIXE_ADDR_OFFSET    72  // Tixe address is i+offset, where i is hardware address or number in array

#ifdef NUTE_MODE_STATION
enum RadioTask_t {rtDoTx, rtDoRx};

struct Tixe_t {
    bool IsOnline, IsToBeFound;
    uint8_t PwrID;
    Situation_t Situation;
};
#define TIXE_COUNT  50
extern Tixe_t Tixe[TIXE_COUNT];

#endif

// Main class of protocol
enum NuteState_t {nsIdle, nsSearch, nsPing, nsWaitingRx, nsTransmitting};
class Nute_t {
private:
    uint32_t ITimer;
#ifdef NUTE_MODE_STATION
    RadioTask_t IRadioTask;
    uint32_t ITixeNumber;
    void DoSearch(void);
    void DoPing(void);
#else

#endif
    void AdjustPwr(uint8_t *PPwrID);
public:
    NuteState_t State;
    Pkt_t RX_Pkt, TX_Pkt;
    void Init(uint8_t ASelfAddr);
    void Task(void);
    void HandleNewPkt(void);
    void HandleTxEnd(void);
    void HandleTixeReply(uint8_t AID);  // Call this when answer received
#ifdef NUTE_MODE_STATION
    void Ping(uint32_t ATixeNumber);
    void Search(uint32_t ATixeNumber);
#endif
};

extern Nute_t Nute;

#endif /* NUTE_H_ */
