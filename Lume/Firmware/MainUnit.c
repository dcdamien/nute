#include "MainUnit.h"

int main (void) {
	uint8_t icounter=0;

	GeneralInit ();

	while (1) {  // forever
		if (POWER_OK) {
			// behave depending on mode
			switch (Mode) {
				case ModeLive:
					icounter++;	// 8-bit PWM
					// switch on all needed LEDs
					if (icounter == 0) {
						cli ();
						if (MFadeIn > 0) 	MinuteSwitch (MinToFadeIn,  ON);	// Switch on MinFadeIn
						if (MFadeOut > 0)	MinuteSwitch (MinToFadeOut, ON);	// Switch on MinFadeOut
						MinuteSwitch (MinToHold, ON);	// Switch on MinToHold
						sei ();
				
						if (HFade > 0) {	// Switch on HFadeIn
							cli (); 
							HourSwitch (HToFadeIn,  ON);	
							sei ();
						}
						if (HFade < TopPWM) {	// Switch on HFadeOut
							cli (); 
							HourSwitch (HToFadeOut, ON);
							sei ();
						}
					}
					// switch off 
					cli (); 
					if (icounter == MFadeIn)	MinuteSwitch (MinToFadeIn,	OFF);
					if (icounter == MFadeOut)	MinuteSwitch (MinToFadeOut,	OFF);
					if (icounter == TopPWM)		MinuteSwitch (MinToHold,	OFF);
		
					if (icounter == HFade)			HourSwitch (HToFadeIn,  OFF);	// Switch off HFadeIn
					if (icounter == TopPWM-HFade)	HourSwitch (HToFadeOut, OFF);	// Switch off HFadeOut
					sei ();
				break;
				
				case ModeHours:	// blink hours
					cli ();
					HourSwitch (HToFadeIn, BlinkOn);	// Switch on/off HFadeIn
					sei ();
				break;
				
				case ModeMin:
					cli ();
					MinuteSwitch (MinToFadeIn, BlinkOn);	// Switch on/off MinFadeIn
					MinuteSwitch (MinToHold, BlinkOn);		// Switch on/off MinToHold
					sei ();
				break;
			} // switch (Mode)
		} // if (POWER_OK)
		else {	// power failure, enter sleep mode
			FadeAll ();
			set_sleep_mode (SLEEP_MODE_PWR_SAVE);	// Left timer2 enabled
			sleep_enable ();
			sleep_cpu ();
			// Awake happened
			if (POWER_OK) ToggleHours ();
			if (POWER_OK) ToggleHyperMinutes ();
		}
	}	// while 1
}

void GeneralInit (void) {
	cli ();
	// Ports init
	DDRA   = (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7);
	DDRB  |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4);
	DDRC  |= (1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3)|(1<<PC4)|(1<<PC5);
	DDRD  |= (1<<PD0)|(1<<PD1)|(1<<PD2)|(1<<PD4)|(1<<PD5)|(1<<PD6)|(1<<PD7);
	FadeAll ();
	
	// Keys
	KeysInit ();
	
	// Mode
	Mode = ModeLive;
	
	// Timer0 init: changes PWM value and handles keys
	TCCR0 = (0<<CS02)|(1<<CS01)|(1<<CS00); // clk/64 = 15625 Hz, 61 OVF/s
	// Enable timer0 irq
	TIMSK |= (1<<TOIE0);
	
	// Timer1 init: keys handler
	ICR1 = 10000;	// TOP value of the counter. 10000: 125000/10000 = 12.5 OVF/s
	TCNT1 = 0;
	TCCR1A = (0<<WGM11)|(0<<WGM10);
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10); // CLK/8, CTC mode with ICR1 as top
	// Enable timer1 irqs
	TIMSK |= (1<<TICIE1);	

	
	// Timer2 init: realtime clock counter
	//TCCR2 = (1<<CS22)|(1<<CS21)|(0<<CS20);	// DEBUG	
	TCCR2 = (1<<CS22)|(0<<CS21)|(1<<CS20);	// RELEASE: div 128, once per second
	//TCCR2 = (0<<CS22)|(1<<CS21)|(0<<CS20);	// DEBUG: div 8
	//TCCR2 = (0<<CS22)|(1<<CS21)|(1<<CS20);	// DEBUG: div 32
	ASSR  = (1<<AS2);							// Set Async mode of the timer
	TIMSK |= (1<<TOIE2);
	
	// Setup initial values
	Seconds = 1;	
	HyperMinutes = 23;
	Hours = 1;
	NewHour = true;
	
	ToggleHours ();
	ToggleHyperMinutes ();
	
	sei();
}

// ******* Toggles *******
void ToggleHours (void) {
	if (Hours > 12) HToFadeIn = Hours-12; else HToFadeIn = Hours;
	if (HToFadeIn == 1)  HToFadeOut = 12; else HToFadeOut = HToFadeIn-1;
	HFade = 0;
	NewHour = true;
}
void ToggleHyperMinutes (void) {
	// Check if hyperminute is odd. If yes, light-up one LED, else two LEDs
	if (HyperMinutes & 0x01) {	// Odd (1, 3, etc.)
		// Nothing to fade-in
		MinToFadeIn = 0;
		if (HyperMinutes == 1) {
			MinToHold = 1;
			MinToFadeOut = 12;
		}		
		else { 
			MinToHold = ((HyperMinutes+1) >> 1);	// means (HyperMinutes+1) /2;
			MinToFadeOut = MinToHold-1;
		}
		MFadeOut = TopPWM;
	}
	else {	// even (2, 4 etc.)
		// Light-up new minute
		if (HyperMinutes == 24) {
			MinToFadeIn = 1;
			MinToHold = 12;
		}
		else {
			MinToFadeIn = ((HyperMinutes + 2)>> 1);	// means (HyperMinutes+2)/2
			MinToHold = MinToFadeIn-1;
		}
		MFadeIn = 0;
		// nothing to light-down
		MinToFadeOut = 0;				
	}
}


// ******************** Interrupts **************************
// Fade-in & Fade-out ruler
ISR (TIMER0_OVF_vect) { 	
	// Handle fade if needed
	if (Mode == ModeLive) {
		// **** Do light-up ****
		TicsFadeIn++;
		if (MFadeIn >= TopPWM) TicsFadeIn = 0;	// if lighting up is finished
		else { // else proceed with lighting up
			if ((MFadeIn <= PWMStepOver1 								&& TicsFadeIn >= PWMDelay1) || // low-speed light-up
				(MFadeIn >  PWMStepOver1 && MFadeIn <= PWMStepOver2	&& TicsFadeIn >= PWMDelay2) ||	// mid-speed light-up
				(MFadeIn >  PWMStepOver2 								&& TicsFadeIn >= PWMDelay3) ) 	// high-speed light-up
			{
				MFadeIn++;
				TicsFadeIn = 0;
			}
		}
	
		// **** Do light-down ****
		TicsFadeOut++;
		if (MFadeOut == 0) TicsFadeOut = 0; 	// if lighting down is finished
		else { // else proceed with lighting up
			if ((MFadeOut <= PWMStepOver1 								&& TicsFadeOut >= PWMDelay1) ||// low-speed light-up
				(MFadeOut >  PWMStepOver1 && MFadeOut <= PWMStepOver2 	&& TicsFadeOut >= PWMDelay2) ||// mid-speed light-up
				(MFadeOut >  PWMStepOver2 								&& TicsFadeOut >= PWMDelay3) ) // high-speed light-up
			{
				MFadeOut--;
				TicsFadeOut = 0;
			}
		}
	
		// **** Handle hours ****
		if (NewHour) {
			if (HFade == TopPWM) {	// Stop if needed
				NewHour = false;
				TicsH = 0;
			}
			else {	// proceed with light-up/down
				TicsH++;
				if ((HFade <= PWMStepOver1 								&& TicsH >= PWMDelay1) ||// low-speed light-up
					(HFade >  PWMStepOver1 && HFade <= PWMStepOver2 	&& TicsH >= PWMDelay2) ||// mid-speed light-up
					(HFade >  PWMStepOver2 								&& TicsH >= PWMDelay3) ) // high-speed light-up
				{
					HFade++;
					TicsH = 0;
				}
			} // if HFade
		} // if newhour
	}	// if mode
	else {	// Some other mode
		// **** Handle blinks ****
		if (BlinkTics++ >= 11) {
			BlinkTics=0;
			BlinkOn ^= 1;
		}
	}
}

// ======== Keys handler ===========
ISR (TIMER1_CAPT_vect) {
	if (KEY_MODE_DOWN && !WaitForRelease) {
		WaitForRelease = true;
		// change mode
		switch (Mode) {
			case ModeLive:	Mode = ModeHours; 	break;
			case ModeHours:	Mode = ModeMin;		break;
			case ModeMin:	Mode = ModeLive;	break;
		}
		ToggleHours ();
		ToggleHyperMinutes ();	
	} // if KEY_MODE_DOWN
		
	if (KEY_PLUS_DOWN && !WaitForRelease) {///
		WaitForRelease = true;
		
		if (Mode == ModeHours) {	// Add hour
			HourSwitch (HToFadeIn, OFF);	// switch-off prev hour
			HourSwitch (HToFadeOut, OFF);	// Switch off HFadeOut
			if (Hours++ == 24) Hours = 1;
			ToggleHours ();
			HToFadeOut = 0;
		}
		
		if (Mode == ModeMin) {		// Add HyperMinute
			MinuteSwitch (MinToFadeIn, OFF);	// Switch-off prev minute  
			MinuteSwitch (MinToHold, OFF);		// Switch-off prev minute
			MinuteSwitch (MinToFadeOut, OFF);	// Switch off MinFadeOut
			if (HyperMinutes++ == 24) HyperMinutes = 1;
			ToggleHyperMinutes ();
		} 
		
		if (Mode == ModeLive) {		// Increase brightness
			if (TopPWM+PWM_STEP < MAX_PWM) TopPWM += PWM_STEP;
			MFadeIn = TopPWM;
			MFadeOut = 0;
			HFade = TopPWM;
		}
	} // if KEY_PLUS_DOWN
		
	if (KEY_MINUS_DOWN && !WaitForRelease) {
		WaitForRelease = true;
		
		if (Mode == ModeHours) {	// Add hour
			HourSwitch (HToFadeIn, OFF);	// switch-off prev hour
			HourSwitch (HToFadeOut, OFF);	// Switch off HFadeOut
			if (--Hours == 0) Hours = 24;
			ToggleHours ();
			HToFadeOut = 0;
		}
			
		if (Mode == ModeMin) {		// Add HyperMinute
			MinuteSwitch (MinToFadeIn, OFF);	// Switch-off prev minute  
			MinuteSwitch (MinToHold, OFF);		// Switch-off prev minute
			MinuteSwitch (MinToFadeOut, OFF);	// Switch off MinFadeOut
			if (--HyperMinutes == 0) HyperMinutes = 24;
			ToggleHyperMinutes ();
		}

		if (Mode == ModeLive) {		// Decrease brightness
			if (TopPWM > PWM_STEP+MIN_PWM) TopPWM -= PWM_STEP;	// if (TopPWM-PWM_STEP > MIN_PWM)...
			MFadeIn = TopPWM;
			MFadeOut = 0;
			HFade = TopPWM;
		}
	} // if KEY_MINUS_DOWN
		
	// Check if all released
	if (!KEY_MODE_DOWN && !KEY_PLUS_DOWN && !KEY_MINUS_DOWN) WaitForRelease = false;
}

// ======== Time counter ===========
ISR (TIMER2_OVF_vect) { 
	//PORTA ^= (1<<PA0);

	// Handle time if needed
	if (Mode != ModeLive) return;	
	
	
	if (Seconds++ == 150) {	// 150 seconds in one hyperminute
		Seconds = 1;
		if (HyperMinutes++ == 24) {	// 24 HyperMinutes in one hour
			HyperMinutes = 1;
			if (Hours++ == 24) Hours = 1;
			if (POWER_OK) ToggleHours ();
		}
		if (POWER_OK) ToggleHyperMinutes ();
	}	// if seconds
}


