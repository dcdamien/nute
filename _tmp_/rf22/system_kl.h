/* 
 * File:   system_kl.h
 * Author: Kreyl Laurelindo
 *
 * Created on 25 Декабрь 2010 г., 15:58
 */

// Here lies SystemInit routines

#ifndef SYSTEM_KL_H
#define	SYSTEM_KL_H

// Clocks
#define SYS_CLK_HSI_DIRECT  // Use HSI as system clock without PLL

// Memory
// Uncomment the following line if you need to relocate your vector Table in Internal SRAM.
// #define VECT_TAB_SRAM
#define VECT_TAB_OFFSET  0x0 //Vector Table base offset field. This value must be a multiple of 0x100.

// ============================== Variables ====================================
extern uint32_t SystemCoreClock;

// ============================== Prototypes ===================================
extern void SystemInit(void);
#ifndef SYS_CLK_HSI_DIRECT
static void SetSysClock(void);
#endif

#endif	/* SYSTEM_KL_H */

