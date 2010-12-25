/* 
 * File:   uartsoftware.h
 * Author: Laurelindo
 *
 * Created on 21 Октябрь 2009 г., 0:20
 */

#ifndef _UART_H
#define	_UART_H

#include <inttypes.h>
#include <stdbool.h>
#include "stm32f10x.h"

// ============================ Definitions ====================================
#define UART_HARDWARE   // Software or hardware uart

#ifdef UART_HARDWARE
// USART1 definitions
#define USART1_CLK      RCC_APB2Periph_USART1
#define USART1_TX_PIN   GPIO_Pin_9
#define USART1_RX_PIN   GPIO_Pin_10
#define USART1_GPIO     GPIOA
#define USART1_GPIO_CLK RCC_APB2Periph_GPIOA




//#define TxPin
//#define RxPin		
//#define UARTPort

#else
#define UARTTxOneBit    1	// for BaudRate = 490000, sysClock = 8 MHz
#define SET_TX_PIN( )	(UARTPort |=  (1<<TxPin))
#define CLEAR_TX_PIN( ) (UARTPort &= ~(1<<TxPin))
#define GET_RX_PIN( )	(UARTPin & (1<<RxPin))
#endif

// ============================ Prototypes =====================================
void UARTInit (void);
void UARTSend (uint8_t AByte);
void UARTSendAsHex (uint8_t AByte);
void UARTNewLine (void);
void UARTSendUint (uint16_t);
void UARTSendInt (int16_t);
void UARTSendString (const char *S);
void UARTSendStringLen (const char *S, const uint8_t ALength);
void UARTSendArr (uint8_t *Arr, uint8_t ALength);
void UARTSendArrAsString (uint8_t *Arr, uint8_t ALength);

char UintToHexChar (uint8_t b);

#endif	

