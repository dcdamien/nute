/* 
 * File:   UART1_to_SPI.h
 * Author: ?????????????
 *
 * Created on 27 јпрель 2010 г., 19:19
 */

#ifndef _UART1_TO_SPI_H
#define	_UART1_TO_SPI_H

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
    // пин OE. ¬ключает-выключает семисигментники
#define DISPLAY_OE_DDR      DDRD
#define DISPLAY_OE_PORT     PORTD
#define DISPLAY_OE_PIN      PD5

    // CLK от UART1. на драйверы семисигментников
#define DISPLAY_CLK_DDR     DDRD
#define DISPLAY_CLK_PORT    PORTD
#define DISPLAY_CLK_PIN     PD4





void UART1_to_SPI_init(void);
extern unsigned char display_LED [4];



#ifdef	__cplusplus
}
#endif

#endif	/* _UART1_TO_SPI_H */

