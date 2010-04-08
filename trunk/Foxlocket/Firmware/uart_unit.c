#include <avr/io.h>
#include "uart_unit.h"
#include <stdbool.h>
#include <util/atomic.h>

void UARTInit (void) {
    #ifdef UBRR0H
    UBRR0H = 0;
    //UBRR0L = 12;	// 4800 at 1MHz
    UBRR0L = 0;	// 60000 at 1MHz
    // RX irq disabled, TX irq disabled, RX disabled, TX enabled
    UCSR0B = (0<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(0<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02);
    // UART, 8 bit, no parity, 1 stop
    UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0);
    #elif defined UBRRH
    UBRRH = 0;
    UBRRL = 0;	// 60000 at 1MHz
    // RX irq disabled, TX irq disabled, RX disabled, TX enabled
    UCSRB = (0<<RXCIE)|(0<<TXCIE)|(0<<UDRIE)|(0<<RXEN)|(1<<TXEN)|(0<<UCSZ2);
    // UART, 8 bit, no parity, 1 stop
    UCSRC = (1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UCPOL);
    #endif
}

// Send one byte
void UARTSendByte (uint8_t data) {
    #ifdef UDR0
    while (bit_is_clear (UCSR0A, UDRE0));
    UDR0 = data;
    #elif defined UDR
    while (bit_is_clear (UCSRA, UDRE));
    UDR = data;
    #endif
}

// ============================== High-level ===================================
void UARTNewLine (void) {
    UARTSendByte ('\r');
}

void UARTSendAsHex (uint8_t AByte, bool ASend0x){
    if (ASend0x){
        UARTSendByte('0');
        UARTSendByte('x');
    }
    UARTSendByte(UintToHexChar (AByte >> 4));
    UARTSendByte(UintToHexChar (AByte & 0x0F));
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
        UARTSendByte (digit);
        ShouldPrint = true;
    }
    digit = '0';
    // >1000
    while (ANumber >= 1000){
        digit++;
        ANumber -= 1000;
    }
    if ((digit != '0') || ShouldPrint) {
        UARTSendByte (digit);
        ShouldPrint = true;
    }
    digit = '0';

    // > 100
    while (ANumber >= 100) {		// Still larger than 100 ?
        digit++;			// Increment first digit
        ANumber -= 100;
    }
    if ((digit != '0') || ShouldPrint) {
            UARTSendByte (digit);
            ShouldPrint = true;
    }
    digit = '0';
    // > 10
    while (ANumber >= 10) {		// Still larger than 10 ?
        digit++;			// Increment second digit
        ANumber -= 10;
    }
    UARTSendByte (digit);
    UARTSendByte ('0'+ANumber);
}
void UARTSendInt (int16_t ANumber) {
    if (ANumber < 0) {
        UARTSendByte ('-');
        ANumber = -ANumber;
    }
    else UARTSendByte (' ');
    UARTSendUint (ANumber);
}

void UARTSendLongHex (uint32_t ALong, bool ASend0x){
    uint8_t FByte;
    FByte = (uint8_t)((ALong >> 24) & 0x000000FF);
    UARTSendAsHex(FByte, ASend0x);
    FByte = (uint8_t)((ALong >> 16) & 0x000000FF);
    UARTSendAsHex(FByte, 0);
    FByte = (uint8_t)((ALong >> 8 ) & 0x000000FF);
    UARTSendAsHex(FByte, 0);
    FByte = (uint8_t)(ALong & 0x000000FF);
    UARTSendAsHex(FByte, 0);
}

void UARTSendString (const char *S) {
    while (*S != '\0') UARTSendByte (*S++);
}
void UARTSendString_P (const char *S) {
    uint8_t FChar;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
        while ((FChar = pgm_read_byte(S++)) != '\0') UARTSendByte (FChar);
    }
}

void UARTSendArr (uint8_t *Arr, uint8_t ALength) {
    while (ALength--) UARTSendByte(*(Arr++));
}

void UARTSendArrAsString (uint8_t *Arr, uint8_t ALength) {
    while (ALength--) {
        UARTSendUint(*(Arr++));
        UARTSendByte (' ');
    }
    UARTNewLine();
}

// ============================ Inner use ======================================
char UintToHexChar (uint8_t b) {
    return ((b<=0x09) ? (b+'0') : (b+'A'-10));
}



// ******************** Interrupts **************************
// rx complete irq
/*
ISR (USART_RX_vect) {
	UART_RXByte = UDR0;
	CNTR_NewCommand=1;
}
*/

