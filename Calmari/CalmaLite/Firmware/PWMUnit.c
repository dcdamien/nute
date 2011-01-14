// ************** Definitions **************************
void PWMStart	(uint8_t StartValue);
void PWMSet		(uint8_t value);
uint8_t PWMGet	(void);
void PWMStop	(void);

// ************** Implementation ***********************
void PWMStart	(uint8_t StartValue){ 
	// Setup timer1 
	TCNT1 = 0x00;
	OCR1C = 0xFF;
	OCR1A = StartValue;
	// Disable interrupts
	TIMSK &= ~((1<<OCIE1A)|(1<<OCIE1B)|(1<<TOIE1));
	// Init clock
	PLLCSR |= (1<<LSM); // Set low-speed mode (32MHz), need for low-voltage operation
	PLLCSR |= (1<<PLLE); // Set PLL enable
	loop_until_bit_is_set (PLLCSR, PLOCK); // wait until PLOCK become 1
	PLLCSR |= (1<<PCKE); // Enable PCK
	// Set PWM mode, PCK. Set COM1A1/A0 to 11 for VCC-based or 10 for GND-based LED
	TCCR1 = (1<<PWM1A)|(1<<COM1A1)|(1<<COM1A0)|(0<<CS13)|(0<<CS12)|(0<<CS11)|(1<<CS10);
	// no need in GTCCR = (0<<PWM1B)|(0<<COM1B1)|(0<<COM1B0)|(0<<PSR1);
}
void PWMSet		(uint8_t value){
	if (value > 250) value = 250;
	OCR1A = value;
}
uint8_t PWMGet	(void){
	return OCR1A;
}
void PWMStop	(void){
	TCCR1  = 0x00; // Stop Timer1
	PLLCSR = 0x00; // Stop clock	
}
