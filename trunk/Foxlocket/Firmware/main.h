/* 
 * File:   main.h
 * Author: Kreyl Laurelindo
 *
 * Created on 7 Апрель 2010 г., 19:44
 */

#ifndef _MAIN_H
#define	_MAIN_H

#define EE_ADDRESS  (uint8_t*)(4)

// ================================= Timings ===================================
// Divider = 64
//#define TCCR1B_ON   (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(1<<CS01)|(1<<CS00)
#define TCCR1B_ON   (1<<WGM13)|(1<<WGM12)|(1<<CS02)|(0<<CS01)|(1<<CS00)
#define TCCR1B_OFF  (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(0<<CS01)|(0<<CS00)

#define TIM1_STOP()     TCCR1B = TCCR1B_OFF
#define TIM1_START()    TCCR1B = TCCR1B_ON

#define TIMER_MULTI     4   // i.e. multiply by 2^MULTI
#define CYCLE_DURATION  200// (200*(1000/64)) // ms * 1000/divider
#define PKT_DURATION    9   //tics

// =============================== Packet info =================================
#define PKT_ID_CALL     0xCA

// ================================ Prototypes =================================



#endif	/* _MAIN_H */

