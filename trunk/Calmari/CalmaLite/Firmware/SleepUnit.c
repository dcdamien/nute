// ************** Definitions **************************
//#include "defins.h"
void DeepSleep (void);	// DeepSleep for this application

// ************** Implementation ***********************
void DeepSleep (void){
	ACSR |= (1<<ACD);	// Shutdown comparator
	// Enable sleep in power-down mode
	MCUCR = (1<<SE)|(1<<SM1)|(0<<SM0);
	// Disable Watchdog	
	asm volatile ("cli"::);
	WDTCR |= (1<<WDCE)|(1<<WDE);
	WDTCR = 0x00;
	// Fall asleep
	asm volatile (
		"sei"	"\n\t"
		"sleep"	"\n\t"
		"cli"	"\n\t"
	::);
	// Enable WatchDog at 2 s
	WDTCR = (0<<WDIE)|(0<<WDP3)|(0<<WDCE)|(1<<WDE)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0);
	// Disable sleep
	MCUCR = (0<<SE)|(0<<SM1)|(0<<SM0);
}
