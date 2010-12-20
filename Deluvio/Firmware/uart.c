#include "uart.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>

// 8 bit, no parity, 1 stop bit 

// ************** Implementation ***********************
void UARTInit (void) {
    // Setup port
    //UARTDDR  &= ~(1<<RxPin);	// RX_PIN is input
    //UARTPort |=  (1<<RxPin);
    SET_TX_PIN ();		// Set the TX line to idle state
    UARTDDR  |=  (1<<TxPin);	// TX_PIN is output
//    MCUCR = 0x00;		// Set IRQ0 to low level
//    GIFR = (1<<INTF0);
//    GIMSK = (1<<INT0);
#ifdef UART_HARDWARE
#ifdef __AVR_ATmega16A__
    UBRRH = 0; 
    UBRRL = 0;  // 250 kBit @ 4MHz
    //UBRRL = 25; // 9600 @ 4MHz
    UCSRB = (0<<RXCIE)|(0<<RXEN)|(0<<UDRIE)|(0<<TXCIE)|(1<<TXEN);
    UCSRC = (1<<URSEL)|(0<<UMSEL)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
#endif
#endif
}
void UARTSend (uint8_t AByte) {
#ifdef UART_HARDWARE
    UCSRA |= (1<<TXC);
    UDR = AByte;
    while(bit_is_clear(UCSRA, TXC));
#else
    uint8_t i;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        // send start bit
        CLEAR_TX_PIN ();
        _delay_us (UARTTxOneBit+1);
        // Send data bits
        for (i=0; i<8; i++, AByte >>=1) {
            if (AByte & 1) SET_TX_PIN ();  // send 1
            else CLEAR_TX_PIN ();          // send 0
            _delay_us (UARTTxOneBit);
        }
        // Send stop bit
        SET_TX_PIN ();	// send 1
        _delay_us (UARTTxOneBit);
    } //ATOMIC_BLOCK
#endif
}
void UARTSendAsHex (uint8_t AByte){
    UARTSend(UintToHexChar (AByte >> 4));
    UARTSend(UintToHexChar (AByte & 0x0F));
}

char UintToHexChar (uint8_t b) {
    return ((b<=0x09) ? (b+'0') : (b+'A'-10));
}


// ============================== High-level ===================================
void UARTNewLine (void) {
    UARTSend ('\r');
}

// Send as digits
void UARTSendUint (uint16_t ANumber) {
    uint8_t digit = '0';
    bool ShouldPrint = false;
    // >10000
    while (ANumber >= 10000) {
        digit++;
        ANumber -= 10000;
    }
    if (digit != '0'){
        UARTSend (digit);
        ShouldPrint = true;
    }
    digit = '0';
    // >1000
    while (ANumber >= 1000){
        digit++;
        ANumber -= 1000;
    }
    if ((digit != '0') || ShouldPrint) {
        UARTSend (digit);
        ShouldPrint = true;
    }
    digit = '0';

    // > 100
    while (ANumber >= 100) {		// Still larger than 100 ?
        digit++;			// Increment first digit
        ANumber -= 100;
    }
    if ((digit != '0') || ShouldPrint) {
            UARTSend (digit);
            ShouldPrint = true;
    }
    digit = '0';
    // > 10
    while (ANumber >= 10) {		// Still larger than 10 ?
        digit++;			// Increment second digit
        ANumber -= 10;
    }
    UARTSend (digit);
    UARTSend ('0'+ANumber);
}
void UARTSendInt (int16_t ANumber) {
    if (ANumber < 0) {
        UARTSend ('-');
        ANumber = -ANumber;
    }
    else UARTSend (' ');
    UARTSendUint (ANumber);
}

void UARTSendString (const char *S) {
    while (*S != '\0') UARTSend (*S++);
}
void UARTSendStringLen (const char *S, const uint8_t ALength) {
    for (uint8_t i=0; i<ALength; i++) UARTSend (*S++);
}
void UARTSendString_P (const char *S) {
    uint8_t FChar;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
        while ((FChar = pgm_read_byte(S++)) != '\0') UARTSend (FChar);
    }
}

void UARTSendArr (uint8_t *Arr, uint8_t ALength) {
    while (ALength--) UARTSend(*(Arr++));
}

void UARTSendArrAsString (uint8_t *Arr, uint8_t ALength) {
    while (ALength--) { 
        UARTSendUint(*(Arr++));
        UARTSend (' ');
    }
    UARTNewLine();
}
// ******************** Interrupts **************************
// INT0
/*
ISR (INT0_vect) {
	uint8_t i, d=0;
	uint16_t tmp;
	// recieve byte
	delay8 (UARTOneAndHalfBit);
	for (i=0; i<8; i++) {
		d = (d>>1);
		if (bit_is_set (PINB, PB6)) d |= 0b10000000;
		delay8 (UARTRxOneBit);
	}
}
*/

