/* 
 * File:   main.h
 * Author: Kreyl Laurelindo
 *
 * Created on 7 Апрель 2010 г., 19:44
 */

#ifndef _MAIN_H
#define	_MAIN_H

#define PKT_DURATION    36 //ms

// ================================= Timings ===================================
// Divider = 1024
#define TCCR1B_ON   (1<<WGM13)|(1<<WGM12)|(1<<CS02)|(0<<CS01)|(1<<CS00)
#define TCCR1B_OFF  (1<<WGM13)|(1<<WGM12)|(0<<CS02)|(0<<CS01)|(0<<CS00)

#define CYCLE_DURATION  300


#endif	/* _MAIN_H */

