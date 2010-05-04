#include "control_unit.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/wdt.h>
#include <util/delay.h>


unsigned char curent_ind=0;
unsigned char display_digits [DISPLAY_NAMBER];

void control_unit_init(void)
{
    DISPLAY_LED_PORT &=~(1<<DISPLAY_LED_PIN); // светодиод зажигаетс€ нулем
    DISPLAY_LED_DDR &=~(1<<DISPLAY_LED_PIN); // выход в Z - пока светодиод не горит

    DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); //пин LE - прием данных
    DISPLAY_LE_DDR |=(1<<DISPLAY_LE_PIN);  // LE - выход

    DISPLAY_OE_PORT &=~(1<<DISPLAY_OE_PIN); //OE- инверсный включаетс€ нулем
    DISPLAY_OE_DDR &=~(1<<DISPLAY_OE_PIN);  // OE в Z-состо€ние. “ам подт€г сам выключит индикатор

   // DISPLAY_CLK_PORT &=~(1<<DISPLAY_CLK_PIN); //пока не имеет значени€
    DISPLAY_CLK_DDR |=(1<<DISPLAY_CLK_PIN);  // CLK - выход

    UART1_init();
    Dig_init();

}

unsigned char Dig[10];
void Dig_init(void)
{
  Dig[0] = (a+b+c+d+e+f);   // ≈сли индикатор с общим анодом,
  Dig[1] = (b+c);           // нужно сумму макросов отн€ть от
  Dig[2] =  (a+b+g+e+d);     // 255. ≈сли с общим катодом, то
  Dig[3] =  (a+b+g+c+d);     // отнимать не нужно.
  Dig[4] =  (f+g+b+c);       // »мена макросов соответствуют
  Dig[5] =  (a+f+g+c+d);     // именам сегментов индикатора
  Dig[6] =  (a+f+g+c+d+e);
  Dig[7] =  (a+b+c);
  Dig[8] =  (a+b+c+d+e+f+g);
  Dig[9] = (a+b+c+d+f+g);
}

void UART1_init(void)
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
// может использоватьс€ дл€ контрол€ целостности цепи и
//подсчета количества индикаторов в системе
ISR(USART1_RX_vect)
{

}
*/

// USART1 Data Register Empty interrupt service routine
ISR(USART1_UDRE_vect)
{
    unsigned char data=display_digits[curent_ind];
    UDR1= data;
    curent_ind++;
    if (curent_ind>DISPLAY_NAMBER)
    {
        DISPLAY_LE_PORT |=(1<<DISPLAY_LE_PIN); //принимаем текущие данные
        curent_ind=1;
        DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); //выключаем LE
    }
}

inline void display_on_off(char mode)
{
    if (mode)  DISPLAY_OE_DDR |=(1<<DISPLAY_OE_PIN);  // зажечь
    else DISPLAY_OE_DDR &=~(1<<DISPLAY_OE_PIN);  // потушить
}

inline void display_LED_on_off(char mode)
{
    if (mode)  DISPLAY_LED_DDR &=~(1<<DISPLAY_LED_PIN);  // зажечь
    else DISPLAY_LED_DDR |=(1<<DISPLAY_LED_PIN);  // потушить
}