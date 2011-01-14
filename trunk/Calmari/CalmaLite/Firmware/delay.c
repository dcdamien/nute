#include <avr\interrupt.h>
#define _0_02_s 1
#define _0_05_s 3
#define _0_1_s  6
#define _0_2_s	12	
#define _0_25_s	15	
#define _0_5_s	31	
#define	_0_75_s	46	
#define _1_s	61	
#define _2_s	122	
#define _3_s	183	
#define _4_s	244	

void Wait (uint8_t ticks_to_wait){
	TCCR0A = 0x00;
	TCCR0B = (0<<CS02)|(1<<CS01)|(1<<CS00);// Timer0 clock select: 011 - 61 ovfs/s
	TIMSK |= (1<<TOIE0);					// Enable Timer0 IRQ
	MCUCR = (1<<SE)|(0<<SM1)|(0<<SM0);	// set idle sleep mode
	while(ticks_to_wait--){
		asm volatile (
			"sei"	"\n\t"
			"sleep"	"\n\t"
			"cli"	"\n\t"
			"wdr"	"\n\t"	// Reset WatchDog
		::);
		if (Valto != None) break;
	}
	MCUCR =0x00;
	TIMSK &= (0<<TOIE0);						// Disable Timer0 IRQ
	TCCR0B = (0<<CS02)|(0<<CS01)|(0<<CS00);	// Stop Timer0
}

EMPTY_INTERRUPT(TIM0_OVF_vect);
