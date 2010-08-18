#include "Lume.h"
#include "common.h"
#include <util/delay.h>
// ============================ Types & variables ==============================
struct {
    uint8_t Hour;
    uint8_t HyperMinute;
    uint8_t Second;
} Time;

enum {ModeRegular, ModeSetHours, ModeSetMinutes} Mode;

struct {
    uint8_t HToFade, HToRise;
    uint8_t MinToFade, MinToRise;
    bool ToggleHour, ToggleMinute;      // Flags showing if toggle needed
    // Control bytes
    uint8_t HByte, MByte;
    // PWMs
    uint8_t PWM_Top;
    uint8_t HPWMFade, HPWMRise, MPWMFade, MPWMRise;
} LControl;

// Tables of accordance
const uint8_t HTable[12] = {
    0b10100000, // H0 == H12
    0b00000000, // H1
    0b00000000, // H2
    0b10000000, // H3
    0b10000000, // H4
    0b01000000, // H5
    0b01000000, // H6
    0b11000000, // H7
    0b11000000, // H8
    0b00100000, // H9
    0b00100000, // H10
    0b10100000, // H11
};

// ============================ Implementation =================================
int main (void) {
    GeneralInit ();

    L_WriteByte(0b10011100);
    L_WriteByte(0b10110001);
    L_Latch();

    L_WriteByte(0b00000000);
    //_delay_ms(10);
    L_Latch();


   sei();

   while (1) {  // forever
        TASK_Toggle();
   }	// while 1
}

void GeneralInit(void) {
    // Light control
    L_DDR  |=   (1<<DATA_IN)|(1<<LATCH)|(1<<SRCLK);
    L_PORT &= ~((1<<DATA_IN)|(1<<LATCH)|(1<<SRCLK));
    M_PWM_DDR  |= (1<<M0PWM)|(1<<M1PWM);
    H_PWM_DDR  |= (1<<H0PWM)|(1<<H1PWM);
    // H PWM
    TCCR1A = (1<<COM1A1)|(1<<COM1A0)|(1<<COM1B1)|(1<<COM1B0)|(0<<WGM11)|(1<<WGM10);
    TCCR1B = (0<<WGM13)|(1<<WGM12)|(1<<CS12)|(0<<CS11)|(0<<CS10);
    OCR1AL = 200;
    OCR1BL = 20;

    // Serial port setup
    UCSR0B = (1<<TXEN0);    // TX enable, irqs disable
    UCSR0C = (1<<UMSEL01)|(1<<UMSEL00)|(1<<UDORD0)|(0<<UCPHA0)|(0<<UCPOL0); // LSB first, leading edge, idle low
    UBRR0  = 0; // Max speed

    // Keys
//    KeysInit ();

    // Timer2 init: realtime clock counter
    //TCCR2B = (1<<CS22)|(1<<CS21)|(0<<CS20);	// DEBUG
    //TCCR2B = (0<<CS22)|(1<<CS21)|(0<<CS20);	// DEBUG: div 8
    //TCCR2B = (0<<CS22)|(1<<CS21)|(1<<CS20);	// DEBUG: div 32
    ASSR  = (1<<AS2);				// Set Async mode of the timer
    TCCR2A = 0;
    TCCR2B = (1<<CS22)|(0<<CS21)|(1<<CS20);	// RELEASE: div 128, once per second
    TIMSK2 |= (1<<TOIE2);

    // Setup initial values
    Time.Second = 1;
    Time.HyperMinute = 23;
    Time.Hour = 0;

    LControl.ToggleHour = false;
    LControl.ToggleMinute = false;
    LControl.PWM_Top = 250;
    LControl.HByte = 0;
    LControl.MByte = 0;

    Mode = ModeRegular;

    // Start-up time setup
    EVENT_NewHour();
    EVENT_NewHyperMinute();
}

// =============================== Tasks =======================================
// Check if need toggle something
void TASK_Toggle(void) {
    if(!POWER_OK()) return;

    if(LControl.ToggleHour) {
    
    }

    if(LControl.ToggleMinute) {

    }
}

// =============================== Light control ===============================
FORCE_INLINE void L_WriteByte(uint8_t AByte) {
    while (bit_is_clear(UCSR0A, UDRE0));    // Wait until buffer is empty
    UDR0 = AByte;
    UCSR0A = (1<<TXC0); // Reset TXC0 flag 
}
FORCE_INLINE void L_Latch(void) {
    while (bit_is_clear(UCSR0A, TXC0));    // Wait until shift register is empty
    L_PORT |=  (1<<LATCH);
    nop();
    L_PORT &= ~(1<<LATCH);
}

// ============================ Events =========================================
void EVENT_NewHour(void) {
    // Toggle hours
    uint8_t HToRise = Time.Hour, HToFade;
    HToRise = 4;
    HToFade = 3;

    //if(Time.Hour == 0) HToFade = 11;
    //else HToFade = Time.Hour-1;
    // Setup Hours byte
    LControl.HByte = 0b10000000;//HTable[HToRise] + HTable[HToFade];
/*
    L_WriteByte(0b11110000);
    L_WriteByte(0b00001111);
    L_Latch();
*/

    // Setup initial PWM
    LControl.ToggleHour = true;
    LControl.HPWMRise = 0;
    LControl.HPWMFade = LControl.PWM_Top;
}
void EVENT_NewHyperMinute(void) {
    // Toggle hyperminutes
    LControl.MinToRise = Time.HyperMinute;
    if(Time.HyperMinute == 0) LControl.MinToFade = 23;
    else LControl.MinToFade = Time.HyperMinute-1;
    // Setup initial PWM
    LControl.ToggleMinute = true;
    LControl.MPWMRise = 0;
    LControl.MPWMFade = LControl.PWM_Top;

    // Write control bytes
/*
    L_WriteByte(LControl.MByte);
    L_WriteByte(LControl.HByte);
    L_Latch();
*/
}



// =========================== Interrupts ======================================
// Time counter
ISR (TIMER2_OVF_vect) { 
    //H_PWM_PORT ^= (1<<H0PWM);

    // Get out in settings mode
    if (Mode != ModeRegular) return;

    Time.Second++;
    if(Time.Second > 150) {    // 150 seconds in one hyperminute
        Time.Second = 1;
        Time.HyperMinute++;
        if(Time.HyperMinute > 23) { // 24 HyperMinutes in one hour
            Time.HyperMinute = 0;
            Time.Hour++;
            if(Time.Hour > 11) Time.Hour = 0;
            if (POWER_OK()) EVENT_NewHour();
        } // if Hyperminute > 23
        if (POWER_OK()) EVENT_NewHyperMinute();
    }// Second
}
/*
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
*/
