#include <avr/eeprom.h>
#include "ee_store_uint32.h"

void EE_CheckIfErased(void) {
    struct EE_Cell_t eec;
    eeprom_read_block(&eec, (uint8_t*)(EE_START_ADDR), EE_CELL_SIZE);
    if(
        (eec.Counter == 0xFF) &&
        (eec.Number == 0xFFFFFFFF)
    ) {
        // Write initial values
        eec.Counter = 0;
        eec.Number = 0;
        eeprom_write_block(&eec, (uint8_t*)EE_START_ADDR, EE_CELL_SIZE);
    }
}

uint32_t EE_ReadUint32(void) {
    return 0;
/*
    uint8_t FOffset = EEFindCurrentOffset();
    uint32_t Result;
    uint8_t FByte;
    FByte = eeprom_read_byte()
    Result =
    return eeprom_read_byte((const uint8_t*)(EE_PARAM_ADDR+FOffset));
*/
}

void EE_WriteUint32(uint32_t ANumber) {
/*
    uint8_t FOffset = EEFindCurrentOffset();                  // Point to current element
    uint8_t PrevValue = eeprom_read_byte((const uint8_t*)(EE_STATUS_ADDR+FOffset));
    FOffset++;                                                // Point to next element
    if (FOffset == EE_BUF_SIZE) FOffset = 0;                  // Handle circle buffer
    eeprom_write_byte((uint8_t*)(EE_PARAM_ADDR +FOffset), AByte);         // Store parameter
    eeprom_write_byte((uint8_t*)(EE_STATUS_ADDR+FOffset), PrevValue+1);   // Store status
*/
}

void EE_FindCurrentAddr(uint8_t *EEAddr, uint8_t *PCounter) {
    uint8_t Current, Previous;      // Two counter values
    uint8_t Addr = EE_START_ADDR;   // Address of needed block
    // Read first counter value
    Previous = eeprom_read_byte((uint8_t*)EE_START_ADDR);
    // Iterate buffer until non-equal values is found
    for (uint8_t i = 1; i < EE_BUF_SIZE; i++) {
        Addr += EE_CELL_SIZE;
        Current = eeprom_read_byte((const uint8_t*)(Addr));
        Previous++;                     // }
        if (Current != Previous) break; // } Such construction needed because simple "Cur != Prev+1" does not work due to compiler's perception
        Previous = Current;
    }
    // Addr now points to new place to write there. Previous means new counter value.
    *EEAddr = Addr;
    *PCounter = Previous;
}
