/* 
 * File:   main.h
 * Author: Kreyl Laurelindo
 *
 * Created on 4 январь 2011 г., 16:10
 */

#ifndef MAIN_H
#define	MAIN_H

// Defines

#define LED_PIN         GPIO_Pin_0
#define LED_GPIO_PORT   GPIOB
#define LED_GPIO_CLK    RCC_APB2Periph_GPIOB
/*#define LED_PIN         GPIO_Pin_9
#define LED_GPIO_PORT   GPIOC
#define LED_GPIO_CLK    RCC_APB2Periph_GPIOC
*/

#define LED_ON()        LED_GPIO_PORT->BSRR = LED_PIN
#define LED_OFF()       LED_GPIO_PORT->BRR  = LED_PIN
#define LED_TOGGLE()    LED_GPIO_PORT->ODR ^= LED_PIN



// ============================== Prototypes ===================================
// Tasks



#endif	/* MAIN_H */

