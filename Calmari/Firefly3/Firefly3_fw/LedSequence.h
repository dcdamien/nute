/*
 * LedSequence.h
 *
 *  Created on: 21 ���. 2014 �.
 *      Author: g.kruglov
 */

#ifndef LEDSEQUENCE_H_
#define LEDSEQUENCE_H_

#include "color.h"

enum LedChunkSort_t {csSetColor, csWait, csGoto, csEnd};

struct LedChunk_t {
    LedChunkSort_t ChunkSort;
    union {
        uint32_t MorphMS;       // 0 means immediately. Up to several thounds
        uint32_t Time_ms;
        uint32_t ChunkToJumpTo;
    };
    Color_t Color;
} __attribute__((packed));
#define LED_CHUNK_SZ    sizeof(LedChunk_t)  // 8 bytes

#define LED_CHUNK_CNT   54
struct LedSequence_t {
    uint32_t Cnt;
    LedChunk_t Chunk[LED_CHUNK_CNT];
    void Reset() { Cnt = 0; }
};


#endif /* LEDSEQUENCE_H_ */
