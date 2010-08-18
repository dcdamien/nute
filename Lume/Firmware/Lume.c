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
    bool ToggleHour, ToggleMinute;      // Flags showing if toggle needed
    // Control bytes
    uint8_t HByte, MByte;
    // PWMs
    uint8_t PWM_Top;
    uint8_t HPWMFade, HPWMRise, MPWMFade, MPWMRise;
} LControl;

// Tables of accordance
const uint8_t HTable[12] = {
    0b00010100, // H0 == H12
    0b00000000, // H1
    0b00000000, // H2
    0b10000000, // H3
    0b00010000, // H4
    0b01000000, // H5
    0b00001000, // H6
    0b11000000, // H7
    0b00011000, // H8
    0b00100000, // H9
    0b00000100, // H10
    0b10100000, // H11
};
const uint8_t MTable[24] = {
    0b00101101, // M12+M11.5 }
    0b01111000, // M0.5+MN --- Needed M0.5+M12, but this must enable both DD5 & DD9
    0b01000000, // M1+M0.5 }
    0b01000001, // M1.5+M1 }
    0b01001001, // M2+M1.5 }
    0b01001010, // M2.5+M2 }
    0b01010010, // M3+M2.5 }
    0b01010011, // M3.5+M3 } All this needs DD5 & DD7 enabled
    0b01011011, // M4+M3.5 }
    0b01011100, // M4.5+M4 }
    0b01100100, // M5+M4.5 }
    0b01100101, // M5.5+M5 }
    0b01101101, // M6+M5.5 }
    0b00111000, // M6.5+MN --- Needed M6.5+M6, but this must enable both DD7 & DD8
    0b00000000, // M7+M6.5   }
    0b00000001, // M7.5+M7   }
    0b00001001, // M8+M7.5   }
    0b00001010, // M8.5+M8   }
    0b00010010, // M9+M8.5   }
    0b00010011, // M9.5+M9   } All this needs DD8 & DD9 enabled
    0b00011011, // M10+M9.5  }
    0b00011100, // M10.5+M10 }
    0b00100100, // M11+M10.5 }
    0b00100101, // M11.5+M11 }
};

// ============================ Implementation =================================
int main (void) {
    GeneralInit ();

//    LControl.MByte = MTable[];
//    WriteControlBytes();

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
    // Hours PWM
    TCCR1A = (1<<COM1A1)|(1<<COM1A0)|(1<<COM1B1)|(1<<COM1B0)|(0<<WGM11)|(1<<WGM10);
    TCCR1B = (0<<WGM13)|(1<<WGM12)|(1<<CS12)|(0<<CS11)|(0<<CS10);
    OCR1AL = 0;
    OCR1BL = 0;
    // Minutes PWM
    TCCR0A = (1<<COM0A1)|(1<<COM0A0)|(1<<COM0B1)|(1<<COM0B0)|(1<<WGM01)|(1<<WGM00);
    TCCR0B = (1<<CS02)|(0<<CS01)|(0<<CS00);
    OCR0A = 200;
    OCR0B = 20;

    // Serial port setup
    UCSR0B = (1<<TXEN0);    // TX enable, irqs disable
    UCSR0C = (1<<UMSEL01)|(1<<UMSEL00)|(0<<UDORD0)|(0<<UCPHA0)|(0<<UCPOL0); // MSB first, leading edge, idle low
    UBRR0  = 0; // Max speed

    // Keys


    // Timer2 init: realtime clock counter
    TCCR2B = (0<<CS22)|(0<<CS21)|(1<<CS20);	// DEBUG
    //TCCR2B = (0<<CS22)|(1<<CS21)|(0<<CS20);	// DEBUG: div 8
    //TCCR2B = (0<<CS22)|(1<<CS21)|(1<<CS20);	// DEBUG: div 32
    ASSR  = (1<<AS2);				// Set Async mode of the timer
    TCCR2A = 0;
    //TCCR2B = (1<<CS22)|(0<<CS21)|(1<<CS20);	// RELEASE: div 128, once per second
    TIMSK2 |= (1<<TOIE2);

    // Setup initial values
    Time.Second = 1;
    Time.HyperMinute = 0;
    Time.Hour = 0;

    LControl.ToggleHour = false;
    LControl.ToggleMinute = false;
    LControl.PWM_Top = 250;

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
FORCE_INLINE void WriteControlBytes(void) {
    while (bit_is_clear(UCSR0A, UDRE0));    // Wait until buffer is empty
    UDR0 = LControl.MByte;
    while (bit_is_clear(UCSR0A, UDRE0));    // Wait until buffer is empty
    UDR0 = LControl.HByte;
    // Toggle latch
    UCSR0A = (1<<TXC0);                     // Reset TXC0 flag
    while (bit_is_clear(UCSR0A, TXC0));     // Wait until shift register is empty
    L_PORT |=  (1<<LATCH);
    nop();
    L_PORT &= ~(1<<LATCH);
}

// ============================ Events =========================================
void EVENT_NewHour(void) {
    // Toggle hours
    uint8_t HToRise = Time.Hour, HToFade;
    if(HToRise == 0) HToFade = 11;
    else HToFade = HToRise-1;
    // Setup Hours byte
    LControl.HByte = HTable[HToRise] + HTable[HToFade];
    // Setup initial PWM
    LControl.ToggleHour = true;
    LControl.HPWMRise = 0;
    LControl.HPWMFade = LControl.PWM_Top;
}
void EVENT_NewHyperMinute(void) {
    // Setup Minutes byte
    LControl.MByte = MTable[Time.HyperMinute];
    // Setup initial PWM
    LControl.ToggleMinute = true;
    LControl.MPWMRise = 0;
    LControl.MPWMFade = LControl.PWM_Top;
    // Write bytes to setup LEDs
    WriteControlBytes();
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
    //        if (POWER_OK()) EVENT_NewHour();
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
