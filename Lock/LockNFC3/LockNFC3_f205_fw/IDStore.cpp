/*
 * IDStore.cpp
 *
 *  Created on: 25.11.2011
 *      Author: Kreyl
 */

#include "IDStore.h"

//#define DO_NOT_SAVE   // Use this to save Flash when debugging

IdKind_t IDStore_t::Check(ID_t &sID, uint32_t *PIndx) {
    if     (IDSecret.ContainsID(sID, PIndx))  return ikSecret;
    else if(IDAccess.ContainsID(sID, PIndx))  return ikAccess;
    else if(IDAdder.ContainsID(sID, PIndx))   return ikAdder;
    else if(IDRemover.ContainsID(sID, PIndx)) return ikRemover;
    else return ikNone;
}

// =============================== Load/save ===================================
void IDStore_t::Load() {
    HasChanged = false;
    if(SD.OpenRead(IDSTORE_FILENAME) == OK) {
        IDAccess.Load(IDSTORE_FILENAME);
        SD.Close();
        Uart.Printf("\rIDs loaded");
    }
}

void IDStore_t::Save(void) {
    HasChanged = false;
    if(SD.OpenRewrite(IDSTORE_FILENAME) == OK) {
//        IDAccess.Save(ID_GROUP_ACCESS);

        SD.Close();
        Uart.Printf("\rIDs saved");
    }
}
