#include "UART1_to_SPI.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/wdt.h>
#include <util/delay.h>


unsigned char curent_ind=0;
unsigned char display_LED [4];

void UART1_to_SPI_init(void)
{

// USART1 initialization
// Communication Parameters: LSB first
// USART1 Receiver: OFF
// USART1 Transmitter: On
// USART1 Mode: SPI UCPOL=0
// USART1 Baud Rate: 9600

UCSR1A=0x00;
UCSR1B=0;
UCSR1B |= (1<<UDRIE1); // включаем прерывание  USART1 Data Register Empty
UCSR1B |= (1<<TXEN1); // включаем передачу

UCSR1C=0;
UCSR1C|=(1<<UMSEL11); // включаем режим SPI
UCSR1C|=(1<<UMSEL10); // .....SPI.....

UCSR1C|=(1<<UCSZ11); //LSB first
//UCSR1C|=(1<<UCPHA1);

//USART1 Baud Rate: 9600
UBRR1H=0x00;
UBRR1L=0x33;
}

/*
// USART1 Receiver interrupt service routine
// может использоваться для контроля целостности цепи и
//подсчета количества индикаторов в системе
ISR(USART1_RX_vect)
{

}
*/

// USART1 Data Register Empty interrupt service routine
ISR(USART1_UDRE_vect)
{
    unsigned char data=display_LED[curent_ind];
    UDR1= data;
    curent_ind++;
    if (curent_ind>4) curent_ind=1;
}