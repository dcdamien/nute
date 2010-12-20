/* 
 * File:   uartsoftware.h
 * Author: Laurelindo
 *
 * Created on 21 Октябрь 2009 г., 0:20
 */

#ifndef _UART_H
#define	_UART_H

#include <inttypes.h>
#include <avr/io.h>
//#include <avr/interrupt.h>
#include <stdbool.h>

// Software or hardware uart
#define UART_HARDWARE

// ************** Definitions **************************
#define UARTTxOneBit    1	// for BaudRate = 490000, sysClock = 8 MHz

#define TxPin		PD1
//#define RxPin		PE3
#define UARTPort	PORTD
#define UARTDDR		DDRD
#define UARTPin		PIND
#define SET_TX_PIN( )	(UARTPort |=  (1<<TxPin))
#define CLEAR_TX_PIN( ) (UARTPort &= ~(1<<TxPin))
#define GET_RX_PIN( )	(UARTPin & (1<<RxPin))

// ============================ Prototypes =====================================
void UARTInit (void);
void UARTSend (uint8_t AByte);
void UARTSendAsHex (uint8_t AByte);
void UARTNewLine (void);
void UARTSendUint (uint16_t);
void UARTSendInt (int16_t);
void UARTSendString (const char *S);
void UARTSendStringLen (const char *S, const uint8_t ALength);
void UARTSendString_P (const char *S);
void UARTSendArr (uint8_t *Arr, uint8_t ALength);
void UARTSendArrAsString (uint8_t *Arr, uint8_t ALength);

char UintToHexChar (uint8_t b);

#endif	

