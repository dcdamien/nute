/*
 * nute.cpp
 *
 *  Created on: 06.05.2012
 *      Author: kreyl
 */

#include "nute.h"
#include "cc1101.h"

Nute_t Nute;

void Nute_t::Init(uint8_t ASelfAddr) {
    IState = nsIdle;
    TX_Pkt.AddrFrom = ASelfAddr;
}

void Nute_t::Task() {
    switch (IState) {
#ifdef NUTE_MODE_STATION
        case nsSearch: DoSearch(); break;
#else   // Tixe
        case nsIdle:
            CC.Receive();
            IState = nsWaitingRx;
            break;

        case nsWaitingRx:
            // Rise event in case of new packet
            if (NewPktRcvd) {
                NewPktRcvd = false;
                IState = nsIdle;
                RxHandler();
            }
            break;

#endif
        default: break;
    }
}

// ============================ Commands =======================================
#ifdef NUTE_MODE_STATION
void Nute_t::Search(Tixe_t *PTixe) {
    IPTixe = PTixe;
    // Reset tixe values
    IPTixe->PwrID = LOWEST_PWR_LVL_ID;
    IPTixe->IsOnline = false;
    // Prepare to search
    IState = nsSearch;
    ISearchState = ssDoTx;
}
#endif

// ============================ Proceedings ====================================
#ifdef NUTE_MODE_STATION
void Nute_t::DoSearch() {
    if (ISearchState == ssDoTx) {   // Prepare pkt and transmit it
        TX_Pkt.AddrTo = IPTixe->Address;
        TX_Pkt.PwrID = IPTixe->PwrID;
        TX_Pkt.Cmd = NUTE_CMD_PING;
        // Setup output power
        CC.SetPower(IPTixe->PwrID);
        klPrintf("Pwr: %u\r", IPTixe->PwrID);
        // Start transmission
        CC.Transmit();
        NewPktRcvd = false;
        Delay.Reset(&ITmr);
        ISearchState = ssDoRx;
    }
    else {  // Do RX
        if (NewPktRcvd) {
            AdjustPwr(&(IPTixe->PwrID));
            // Check if correct Pkt - FIXME
            IState = nsIdle;
            IPTixe->IsOnline = true;
            if(IPTixe->Callback != 0) IPTixe->Callback();
        }
        // Check if timeout
        else if (Delay.Elapsed(&ITmr, REPLY_WAITTIME)) {
            CC.EnterIdle();
            klPrintf("t\r");
            if (IPTixe->PwrID == HIGHEST_PWR_LVL_ID) { // No answer even at top power, get out
                IState = nsIdle;
                if(IPTixe->Callback != 0) IPTixe->Callback();
            }
            else {  // Top not achieved
                IPTixe->PwrID++;
                ISearchState = ssDoTx;
            }
        } // if timeout
    } // do rx
}

#endif

// ============================ Common =========================================
void Nute_t::AdjustPwr(uint8_t *PPwrID) {
    int16_t RSSI_dBm = CC.RSSI_dBm(RX_Pkt.RSSI);
    int16_t Diff = (DESIRED_RSSI - RSSI_dBm) % 4;   // every single ID mean 4dB difference
    int16_t NewPwrID = *PPwrID + Diff;
    if      (NewPwrID > HIGHEST_PWR_LVL_ID) NewPwrID = HIGHEST_PWR_LVL_ID;
    else if (NewPwrID < LOWEST_PWR_LVL_ID)  NewPwrID = LOWEST_PWR_LVL_ID;
    klPrintf("PwrOld: %u; ", *PPwrID);
    *PPwrID = (uint8_t)NewPwrID;
    klPrintf("PwrNew: %u\r", *PPwrID);
}
