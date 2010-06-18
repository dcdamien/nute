// ************** Definitions **************************
// 2.56 V reference w/o capacitor, not left-adjusted, channel ADC3	
//#define _UBat	(1<<REFS1)|(0<<REFS0)|(0<<ADLAR)|(1<<REFS2)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0)
// 1.1 V reference w/o capacitor, not left-adjusted, channel dif ADC2-ADC3 x1
//#define _ILed	(1<<REFS1)|(0<<REFS0)|(0<<ADLAR)|(0<<REFS2)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(0<<MUX0)
// 1.1 V reference w/o capacitor, not left-adjusted, channel dif ADC2-ADC3 x20
#define _ILed	(0<<REFS2)|(1<<REFS1)|(0<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0)
void ADCStart (void);
uint16_t ADCMeasure (void);
void ADCStop (void);

// ************** Implementation ***********************
void ADCStart (void) {
	ADMUX = _ILed;
	// make first conversion
	// Unipolar mode, reversed polarity
	ADCSRB = (0<<BIN)|(1<<IPR);
	// ADC enabled, IRQ enabled, 125 kHz
	ADCSRA = (1<<ADEN)|(0<<ADSC)|(0<<ADATE)|(1<<ADIF)|(1<<ADIE)|(0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	MCUCR = (1<<SE)|(0<<SM1)|(0<<SM0);	 // Enable idle sleep mode
	asm volatile (
		"sei"	"\n\t"
		"sleep"	"\n\t"
		"cli"	"\n\t"
		"wdr"	"\n\t"	// Reset WatchDog
	::);
	MCUCR = 0x00;		// disable sleep
	// leave ADC enabled
}

uint16_t ADCMeasure (void) {
	uint16_t result=0;
	uint8_t i;

	MCUCR = (1<<SE)|(0<<SM1)|(0<<SM0);	 // Enable idle sleep mode
	ADMUX = _ILed;
	
	// disconnect timer1
	TCCR1 = (1<<PWM1A)|(0<<COM1A1)|(0<<COM1A0)|(0<<CS13)|(0<<CS12)|(0<<CS11)|(1<<CS10);
	
	for (i=8;i;--i){
		//ADCSRA |= (1<<ADSC)|(1<<ADIF);
		asm volatile (
			"sei"	"\n\t"
			"sleep"	"\n\t"
			"cli"	"\n\t"
			"wdr"	"\n\t"	// Reset WatchDog
		::);
		result += ADC;
	}
	MCUCR = 0x00;		// disable sleep
	
	// start timer
	TCCR1 = (1<<PWM1A)|(1<<COM1A1)|(1<<COM1A0)|(0<<CS13)|(0<<CS12)|(0<<CS11)|(1<<CS10);

	result /= 8;
	return result;
}

void ADCStop (void) {
	ADCSRA = (0<<ADEN)|(0<<ADSC)|(0<<ADATE)|(1<<ADIF)|(0<<ADIE)|(0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

// ******************** Interrupts **************************
// ADC interrupt
EMPTY_INTERRUPT (ADC_vect);

