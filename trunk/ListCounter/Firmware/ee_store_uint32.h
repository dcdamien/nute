/* 
 * File:   eeprombuf.h
 * Author: Laurelindo
 *
 * Created on 24 Январь 2010 г., 13:11
 */

#ifndef _EEPROMBUF_H
#define	_EEPROMBUF_H

#include <inttypes.h>

/*
 Data stored in blocks, each of which contains some useful data and single byte
 of service data - counter. It increases every time new data is stored.
 The buffer is circled.
 When searching last address, search lasts while two consequent values of
 counter distinct by one. When that is not right, then buffer end is found.
 There is restriction to maximum total buffer size: it must not exceed
 255 bytes, to make possible uint8_t addresses.
*/

// ================================ Defines ====================================
#define EE_START_ADDR   0
#define EE_BUF_SIZE     7

// ================================= Types =====================================
struct EE_Cell_t {
    uint8_t Counter;    // Must be first unit in structure
    uint32_t Number;
};

#define EE_CELL_SIZE    sizeof(struct EE_Cell_t)

// =============================== Prototypes ==================================
void EE_CheckIfErased(void);
uint32_t EE_ReadUint32(void);
void EE_WriteUint32(uint32_t ANumber);

// Inner use
void EE_FindCurrentAddr(uint8_t *EEAddr, uint8_t *PCounter);



#endif	/* _EEPROMBUF_H */

