/* 
 * File:   uartsoftware.h
 * Author: Laurelindo
 *
 * Created on 21 Октябрь 2009 г., 0:20
 */

#ifndef _UARTSOFTWARE_H
#define	_UARTSOFTWARE_H

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

// ************** Definitions **************************
#define UARTTxOneBit    1	// Bitrate 490000 @ 8 MHz; 74000 @ 1MHz

#define TxPin		PC0
//#define RxPin		PE3
#define UARTPort	PORTC
#define UARTDDR		DDRC
#define UARTPin		PINC
#define SET_TX_PIN( )	(UARTPort |=  (1<<TxPin))
#define CLEAR_TX_PIN( ) (UARTPort &= ~(1<<TxPin))
#define GET_RX_PIN( )	(UARTPin & (1<<RxPin))

// ================================ Variables ==================================

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

#endif	/* _UARTSOFTWARE_H */

