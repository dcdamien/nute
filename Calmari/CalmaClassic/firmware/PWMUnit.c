// ************** Definitions **************************
void PWMStart	(void);
void PWMSet		(uint8_t value);
void PWMStop	(void);

// ************** Implementation ***********************
void PWMStart	(void){ 
	// Setup timer1 
	TCNT1 = 0x00;
	OCR1C = 0xFF;
	OCR1A = 0x00;
	OCR1B = 0x00;
	// Disable Timer1 interrupts
	TIMSK &= ~((1<<OCIE1A)|(1<<OCIE1B)|(1<<TOIE1));
	// Init clock
	PLLCSR |= (1<<LSM); // Set low-speed mode (32MHz), need for low-voltage operation
	PLLCSR |= (1<<PLLE); // Set PLL enable
	loop_until_bit_is_set (PLLCSR, PLOCK); // wait until PLOCK become 1
	PLLCSR |= (1<<PCKE); // Enable PCK
	// Set PWM mode; PCK is freq source. UnComment desired rows
	// ********* SingleChannelVCC **********
	TCCR1 = (1<<PWM1A)|(1<<COM1A1)|(1<<COM1A0)|(0<<CS13)|(0<<CS12)|(0<<CS11)|(1<<CS10);
	// ********* TwoChannelVCC    **********
	//TCCR1 = (1<<PWM1A)|(1<<COM1A1)|(1<<COM1A0)|(0<<CS13)|(0<<CS12)|(0<<CS11)|(1<<CS10);
	//GTCCR = (1<<PWM1B)|(1<<COM1B1)|(1<<COM1B0)|(0<<PSR1); 
	// ********* SingleChannelGND **********
	//TCCR1 = (1<<PWM1A)|(1<<COM1A1)|(0<<COM1A0)|(0<<CS13)|(0<<CS12)|(0<<CS11)|(1<<CS10);
	// ********* TwoChannelGND	  **********
	//TCCR1 = (1<<PWM1A)|(1<<COM1A1)|(0<<COM1A0)|(0<<CS13)|(0<<CS12)|(0<<CS11)|(1<<CS10);
	//GTCCR = (1<<PWM1B)|(1<<COM1B1)|(0<<COM1B0)|(0<<PSR1); 
}
void PWMSet		(uint8_t value) {
	if (value > 250) value = 250;
	OCR1A = value;
}
void PWMStop	(void){
	TCCR1  = 0x00; // Stop Timer1
	GTCCR  = 0x00; // Stop second channel
	PLLCSR = 0x00; // Stop clock	
}
