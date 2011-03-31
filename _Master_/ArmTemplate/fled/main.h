/* 
 * File:   main.h
 * Author: Kreyl Laurelindo
 *
 * Created on 4 январь 2011 г., 16:10
 */

#ifndef MAIN_H
#define	MAIN_H

// Defines

#define LEDG_PIN        GPIO_Pin_9
#define LEDB_PIN        GPIO_Pin_8
#define LED_GPIO_PORT   GPIOC
#define LED_GPIO_CLK    RCC_APB2Periph_GPIOC

#define LEDG_ON()   LED_GPIO_PORT->BSRR = LEDG_PIN
#define LEDB_ON()   LED_GPIO_PORT->BSRR = LEDB_PIN
#define LEDG_OFF()  LED_GPIO_PORT->BRR  = LEDG_PIN
#define LEDB_OFF()  LED_GPIO_PORT->BRR  = LEDB_PIN
#define LEDG_TOGGLE()   LED_GPIO_PORT->ODR ^= LEDG_PIN
#define LEDB_TOGGLE()   LED_GPIO_PORT->ODR ^= LEDB_PIN

#define BTN_P   GPIO_Pin_0
#define BTN1_IS_PRESSED() (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
#define BTN2_IS_PRESSED() (GPIO_ReadInputDataBit(GPIOA, BTN_P))
#define BTN3_IS_PRESSED() (GPIO_ReadInputDataBit(GPIOA, BTN_P))


#endif	/* MAIN_H */

