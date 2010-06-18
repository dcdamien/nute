#include <avr/io.h>
#include <avr/wdt.h>
#include "calmaclassic.h"

int main (void){
    // ************* Init sequence *************
    // Enable WatchDog at 2 s
    wdt_enable(WDTO_2S);
    // Shutdown comparator
    ACSR |= (1<<ACD);
    // Setup IO
    DDRB  = (0<<KeyPin)|(1<<LedPin);
    PORTB = (0<<KeyPin)|(1<<LedPin); // VCC-based LED
    // Enable Key IRQ
    PCMSK = (1<<KeyPin);
    EnableKeyIRQ();
		
    uint8_t state = LightUp;
	
    // **************** Main cycle *******************
    while (1) {
        // ************ System timer ******************
        // Enable Timer0 and IRQ
        TCCR0A = 0x00;
        TCCR0B = (0<<CS02)|(1<<CS01)|(1<<CS00); // Timer0 clock select: 011 - 61 ovfs/s
        TIMSK |= (1<<TOIE0);			// Enable Timer0 IRQ
        MCUCR = (1<<SE)|(0<<SM1)|(0<<SM0);	// Enable idle sleep mode
        asm volatile (
            "sei"	"\n\t"
            "sleep"	"\n\t"
            "cli"	"\n\t"
            "wdr"	"\n\t"	// Reset WatchDog
        ::);
        MCUCR =0x00;		// disable sleep

        // ************** State handler *****************
        // state changes in case of keypress, light fadeout or fadein completetion, and after wake
        switch (state) {
            case WaitKeyRelease:
                    // nothing to do
            break;

            case LightUp:
                // Check if light ramp completed
                if (DoLightUp() == Finished) state = LightAlive;
            break;

            case LightAlive:
                ADCStart ();
                DoHandleLight();
            break;

            case LightDown:
                // check if fade completed
                if (DoLightDown() == Finished) state = DeepSleep;
            break;

            case DeepSleep:
                DoSleep ();
            break;
        }

        // ************** Event handler *****************
        if (Valto == KeyDown) {
            // After wake
            if  (state == DeepSleep) state = WaitKeyRelease;
            // Test if key released
            if	(KeyIsUp) {
                    SilTics = 0; // reset timer
                    if ((state==LightAlive) || (state==LightUp))	state = LightDown;
                    if (state == WaitKeyRelease)					state = LightUp;
                    Valto = None;
            }
        }	// if event
    }
}


uint8_t DoLightUp (void){
	if (Sil >= PWMStartValue) { // if lighting up is finished
		SilTics = 0; 
		return Finished;
	}
	else { // else proceed with lighting up
		if (Sil == 0)	PWMStart (); // Start-up PWM
		if ((Sil <= PWMStepOver1 && SilTics >= PWMDelay1) || 							// low-speed light-up
			(Sil >  PWMStepOver1 && Sil <= PWMStepOver2 && SilTics >= PWMDelay2) ||	// mid-speed light-up
			(Sil >  PWMStepOver2 && SilTics >= PWMDelay3) ) 							// high-speed light-up
		{
			PWMSet (Sil++);
			SilTics = 0;
		}
		return UnFinished;
	}
}
uint8_t DoLightDown (void){
	if (Sil == 0) {		// if lighting down is finished
		SilTics = 0;
		PWMStop (); 	// Shutdown PWM
		return Finished;
	}
	else {				// else proceed with fade
		if (
		(Sil <= PWMStepOver1 && SilTics >= PWMDelay1) || 							// low-speed
		(Sil >  PWMStepOver1 && Sil <= PWMStepOver2 && SilTics >= PWMDelay2) ||	// mid-speed
		(Sil >  PWMStepOver2 && SilTics >= PWMDelay3) ) 							// high-speed 
		{
			PWMSet (--Sil);
			SilTics = 0;
		}
		return UnFinished;
	}
}
void DoHandleLight (void){
	// Test if time to measure
	if (SilTics == TimeToMeasure) {
		// Reset Timing
		SilTics = 0;
		DisableKeyIRQ;
		// Measure
		uint16_t ILedN = ADCMeasure ();
		// Adjust current
		if (ILedN > ILedNominal && Sil > PWMMin) Sil--;
		if (ILedN < ILedNominal && Sil < PWMMax) Sil++;
		PWMSet (Sil);
		EnableKeyIRQ;
	}
}
void DoSleep (void) {
	ADCStop ();
	// Enable sleep in power-down mode
	MCUCR = (1<<SE)|(1<<SM1)|(0<<SM0);
	// Disable Watchdog	
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

// ******************** Interrupts **************************
// Timer0 interrupt
ISR (TIM0_OVF_vect) {
	// Increase timer
	SilTics++;
}

// Key interrupt
ISR (PCINT0_vect){
    if (!KeyIsUp)  Valto = KeyDown;
}

