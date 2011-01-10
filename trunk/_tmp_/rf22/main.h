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

#define BTN_P   GPIO_Pin_1
#define BTN_IS_PRESSED() (!GPIO_ReadInputDataBit(GPIOB, BTN_P))


// ============================== Prototypes ===================================
// Tasks
void Task_Si(void);
void Task_Si2(void);

#endif	/* MAIN_H */

