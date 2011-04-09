/*
 * File:   sound_data.h
 * Author: Kreyl Laurelindo
 *
 * Created on 3 Март 2011 г., 19:52
 */

#ifndef SOUND_DATA_H
#define	SOUND_DATA_H

#include <inttypes.h>

#ifdef __cplusplus
 extern "C" {
#endif

//#define DEBUG_SHORT_SOUND

#ifdef DEBUG_SHORT_SOUND
    #define SND1_LEN    9
#else
    #define SND1_LEN    21683
#endif

#define SND2_LEN    1857

extern const uint16_t Snd1[SND1_LEN];
extern const uint16_t Snd2[SND2_LEN];



#ifdef __cplusplus
}
#endif

#endif	/* SOUND_DATA_H */

