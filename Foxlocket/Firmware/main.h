/* 
 * File:   main.h
 * Author: Kreyl Laurelindo
 *
 * Created on 7 Апрель 2010 г., 19:44
 */

#ifndef _MAIN_H
#define	_MAIN_H

// ================================= Timings ===================================
// Divider = 1024
#define TCCR1B_ON   (1<<WGM13)|(1<<WGM12)|(1<<CS02)|(0<<CS01)|(1<<CS00)
#define TCCR1B_OFF  (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(0<<CS01)|(0<<CS00)

#define TIMER_MULTI     3   // i.e. multiply by 8
#define CYCLE_DURATION  200
#define PKT_DURATION    3   //tics

#define TIMER_ADJUST(AL_ADR)    TCNT1 = (AL_ADR << TIMER_MULTI) + PKT_DURATION

// =============================== Packet info =================================
#define PKT_ID_CALL     0xCA


#endif	/* _MAIN_H */

