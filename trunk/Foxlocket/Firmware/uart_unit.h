#ifndef _UART_UNIT_H_
#define _UART_UNIT_H_

#include <inttypes.h>
#include <stdbool.h>
#include <avr/pgmspace.h>

// ============================ Prototypes =====================================
void UARTInit (void);
void UARTSendByte (uint8_t AByte);

void UARTSendAsHex (uint8_t AByte, bool ASend0x);
void UARTNewLine (void);
void UARTSendUint (uint16_t);
void UARTSendLongHex (uint32_t, bool);
void UARTSendInt (int16_t);
void UARTSendString (const char *S);
void UARTSendString_P (const char *S);
void UARTSendArr (uint8_t *Arr, uint8_t ALength);
void UARTSendArrAsString (uint8_t *Arr, uint8_t ALength);

// Inner use
char UintToHexChar (uint8_t b);


#endif
