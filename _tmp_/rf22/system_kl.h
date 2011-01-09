/* 
 * File:   system_kl.h
 * Author: Kreyl Laurelindo
 *
 * Created on 25 Декабрь 2010 г., 15:58
 */

// Here lies SystemInit routines

#ifndef SYSTEM_KL_H
#define	SYSTEM_KL_H

#ifdef __cplusplus
 extern "C" {
#endif

// Clocks
#define SYS_CLK_HSI_DIRECT  // Use HSI as system clock without PLL
// APB2 divider
#define SYS_APB2_CLK_DIVIDER    RCC_HCLK_Div2

// ============================== Variables ====================================
extern uint32_t SystemCoreClock;

// ============================== Prototypes ===================================
extern void SystemInit(void);

#ifdef __cplusplus
}
#endif

#endif	/* SYSTEM_KL_H */

