#include <avr/io.h>
#include "led_io.h"
#include "common.h"
#include "delay_util.h"

// ============================= Variables =====================================
struct LControl_t LControl;

// Tables of accordance
const uint8_t HTable[12] = {
    0b0, // H0 == H12
    0b0, // H1
    0b0, // H2
    0b0, // H3
    0b0, // H4
    0b0, // H5
    0b0, // H6
    0b0, // H7
    0b0, // H8
    0b0, // H9
    0b0, // H10
    0b0, // H11
};
const uint8_t MTable[24][2] = { // First byte for minutes bits, second for minute byte
    {0b10000000, 0b00101000},   // M12
    {0b00000000, 0b01000000},   // M0.5
    {0b00000000, 0b10000000},   // M1
    {0b00000000, 0b01000001},   // M1.5
    {0b00000000, 0b10001000},   // M2
    {0b00000000, 0b01000010},   // M2.5
    {0b00000000, 0b10010000},   // M3
    {0b00000000, 0b01000011},   // M3.5
    {0b00000000, 0b10011000},   // M4
    {0b00000000, 0b01000100},   // M4.5
    {0b00000000, 0b10100000},   // M5
    {0b00000000, 0b01000101},   // M5.5
    {0b00000000, 0b10101000},   // M6
    {0b01000000, 0b00000000},   // M6.5
    {0b10000000, 0b00000000},   // M7
    {0b01000000, 0b00000001},   // M7.5
    {0b10000000, 0b00001000},   // M8
    {0b01000000, 0b00000010},   // M8.5
    {0b10000000, 0b00010000},   // M9
    {0b01000000, 0b00000011},   // M9.5
    {0b10000000, 0b00011000},   // M10
    {0b01000000, 0b00000100},   // M10.5
    {0b10000000, 0b00100000},   // M11
    {0b01000000, 0b00000101},   // M11.5
};

// =========================== Implementation ==================================
FORCE_INLINE void LedIOInit(void) {
    L_DDR  |=   (1<<DATA_IN)|(1<<LATCH)|(1<<SRCLK);
    L_PORT &= ~((1<<DATA_IN)|(1<<LATCH)|(1<<SRCLK));
    M_PWM_DDR  |= (1<<M0PWM)|(1<<M1PWM);
    H_PWM_DDR  |= (1<<H0PWM)|(1<<H1PWM);
    M_PWM_PORT |= (1<<M0PWM)|(1<<M1PWM);
    H_PWM_PORT |= (1<<H0PWM)|(1<<H1PWM);
    // Hours PWM
    TCCR1A = (0<<WGM11)|(1<<WGM10);
    TCCR1B = (0<<WGM13)|(1<<WGM12)|(1<<CS12)|(0<<CS11)|(0<<CS10);
    // Minutes PWM & delay counter
    TCCR0A = (1<<WGM01)|(1<<WGM00);
    TCCR0B = (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);
    TIMSK0 = (1<<TOIE0);

    // Serial port setup
    UCSR0B = (1<<TXEN0);    // TX enable, irqs disable
    UCSR0C = (1<<UMSEL01)|(1<<UMSEL00)|(0<<UDORD0)|(0<<UCPHA0)|(0<<UCPOL0); // MSB first, leading edge, idle low
    UBRR0  = 0; // Max speed

    LControl.PWM_Top = 255;
    LControl.Min0PWM.OCRX = &OCR0A;
    LControl.Min1PWM.OCRX = &OCR0B;
    LControl.Hr0PWM.OCRX  = &OCR1AL;
    LControl.Hr1PWM.OCRX  = &OCR1BL;
}

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

void SetupMinute(uint8_t AMinute, enum PWMMode_t AMode) {
    // Setup channel
    LControl.HByte |= MTable[AMinute][0];
    LControl.MByte |= MTable[AMinute][1];
    // Setup PWM
    if(AMinute & 0x01) SetupPWM(&LControl.Min0PWM, AMode);    // even => integers: 1 means M0_5, 2 - M1 and so on
    else               SetupPWM(&LControl.Min1PWM, AMode);
}

void SetupPWM(struct PWM_t *pwm, enum PWMMode_t mode) {
    pwm->Mode = mode;
    DelayReset(&(pwm->Timer));
    if(mode == PWMRise) {
        pwm->Value = 0;
        *(pwm->OCRX) = 0;
        pwm->Delay = PWMDelay1;
    }
    else {
        pwm->Value = LControl.PWM_Top;
        *(pwm->OCRX) = LControl.PWM_Top;
        pwm->Delay = PWMDelay1;     // !!!!!!!FIXME
    } // else

    // Switch PWM on
    if     (pwm->OCRX == &OCR0A)  TCCR0A |= ((1<<COM0A1)|(1<<COM0A0));
    else if(pwm->OCRX == &OCR0B)  TCCR0A |= ((1<<COM0B1)|(1<<COM0B0));
    else if(pwm->OCRX == &OCR1AL) TCCR1A |= ((1<<COM1A1)|(1<<COM1A0));
    else if(pwm->OCRX == &OCR1BL) TCCR1A |= ((1<<COM1B1)|(1<<COM1B0));
}

void TogglePWM(struct PWM_t *pwm) {
    if(pwm->Mode == PWMHold) return;                            // Nothing to do here
    if(!DelayElapsed(&(pwm->Timer), pwm->Delay)) return;   // Not in time
    if(pwm->Mode == PWMRise) {
        pwm->Value++;
        if(pwm->Value == LControl.PWM_Top) pwm->Mode = PWMHold;

    } // if mode
    else {
        pwm->Value--;
        if(pwm->Value == 0) {
            pwm->Mode = PWMHold;
            // Disconnect PWM
            if     (pwm->OCRX == &OCR0A)  TCCR0A &= ~((1<<COM0A1)|(1<<COM0A0));
            else if(pwm->OCRX == &OCR0B)  TCCR0A &= ~((1<<COM0B1)|(1<<COM0B0));
            else if(pwm->OCRX == &OCR1AL) TCCR1A &= ~((1<<COM1A1)|(1<<COM1A0));
            else if(pwm->OCRX == &OCR1BL) TCCR1A &= ~((1<<COM1B1)|(1<<COM1B0));
        }
    }
    *(pwm->OCRX) = pwm->Value;
}


