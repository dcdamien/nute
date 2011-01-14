#include "defins.h"
int main (void){
	// Setup IO
	DDRB  = (0<<PB0)|(1<<PB1)|(0<<PB2)|(0<<PB3)|(0<<PB4);
	PORTB = (1<<PB0)|(1<<PB1)|(1<<PB2)|(0<<PB3)|(0<<PB4); // VCC-based LED
	
	while (1){
		EnableInput ();
		DeepSleep();
		DisableInput ();
		// **** Why wake? ****
		EventHandler();
		if (Valto==KeyPressed) {
			Valto = None;
			Wait (_2_s);
			LightUp();
			if (Valto == None) LiveInLight();
			LightDown();
		}
	}
}

void EventHandler(void){
	if (Valto == KeyDown) {
		//release key
		while (bit_is_clear (PINB, KeyPin)) Wait (_0_25_s);
		Valto = KeyPressed;
	}
}

void LightUp (void){
	uint8_t i;
	PWMStart(0);
	// Enable shutdown at Light-up
	for (i=0; i<=250; i++){
		PWMSet (i);
		EnableInput ();
		if (i<PWMStepOver) Wait (PWMSlowDelay);
		else Wait (PWMQuickDelay);
		DisableInput ();
		if (Valto != None) {
			EventHandler ();
			// if key pressed then shutdown
			if (Valto==KeyPressed) break; 
		}
	}
}

void LightDown (void){
	uint8_t i;
	for (i=PWMGet(); i>0; i--){
		PWMSet (i);
		if (i<PWMStepOver) Wait (PWMSlowDelay); 
		else Wait (PWMQuickDelay);
	}	
	PWMStop();
}

void LiveInLight (void){
	PORTB &= ~(1<<LedPin); // Light-up LED
	PWMStop();
	while (1){
		EnableInput ();
		DeepSleep();
		DisableInput ();
		if (Valto != None) {
			EventHandler ();
			// if key pressed then shutdown
			if (Valto==KeyPressed) break; 
		}
	}
	PWMStart(250);
	PORTB |= (1<<LedPin); // Shutdown LED
}

void EnableInput  (void) {
	// Enable PCIE at PB0
	PCMSK = PCMSK = (0<<PCINT5)|(0<<PCINT4)|(0<<PCINT3)|(1<<PCINT2)|(0<<PCINT1)|(1<<PCINT0);
	GIMSK = (0<<INT0)|(1<<PCIE);

	asm volatile ("sei"::);
}
void DisableInput (void){
	asm volatile ("cli"::);
	// Disable PCIE
	GIMSK = (0<<INT0)|(0<<PCIE);
}

// KeyPress interrupt
ISR (PCINT0_vect){
	if (bit_is_clear (PINB, KeyPin)) Valto = KeyDown;
}
