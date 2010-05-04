/* 
 * File:   UART1_to_SPI.h
 * Author: ?????????????
 *
 * Created on 27 Апрель 2010 г., 19:19
 */

#ifndef _CONTROL_UNIT_H
#define	_CONTROL_UNIT_H

#ifdef	__cplusplus
extern "C" {
#endif

    // управление светодиодом LED1 на плате пульта
#define DISPLAY_LED_DDR     DDRD
#define DISPLAY_LED_PORT    PORTD
#define DISPLAY_LED_PIN     PD7
    // пин LATCH_EN на драйверах семисегментников
#define DISPLAY_LE_DDR      DDRD
#define DISPLAY_LE_PORT     PORTD
#define DISPLAY_LE_PIN      PD6
    // пин OE. Включает-выключает семисигментники
#define DISPLAY_OE_DDR      DDRD
#define DISPLAY_OE_PORT     PORTD
#define DISPLAY_OE_PIN      PD5

    // CLK от UART1. на драйверы семисигментников
#define DISPLAY_CLK_DDR     DDRD
#define DISPLAY_CLK_PORT    PORTD
#define DISPLAY_CLK_PIN     PD4


#define DISPLAY_NAMBER      4


#define a 2       // Эти макросы содержат числа, соответствующие двойке,
#define b 1       // возведенной в степень, равной номеру "ножки" того
#define c 64      // порта, к которому подключен сегмент индикатора с
#define d 32      // одноименным макросу названием. Для того, чтобы вывести
#define e 16      // какую-либо цифру на индикатор, нужно отправить в порт
#define f 4       // число 255 минус сумму соответствующих сегментам макросов.
#define g 8       // Эти числа позволяют сделать программу независимой от подключения.
#define DP 128    // Измените эти числа, если индикатор выводит букву "зю"

//unsigned char DigNumber = 0;
extern unsigned char Dig[10]; // Массив, в котором хранятся числа, которые нужно
// вывести через порт на индикатор, чтобы он показал цифру, равную номеру
// элемента массива. Числа зависят только от макросов.

void control_unit_init(void); // чтоб все тут проинициализировать
void Dig_init(void);
void UART1_init(void);

void display_on_off(char mode);
void display_LED_on_off(char mode);


extern unsigned char display_digits [DISPLAY_NAMBER];



#ifdef	__cplusplus
}
#endif

#endif	/* _CONTROL_UNIT_H */

