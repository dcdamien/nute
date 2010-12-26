#include "stm32f10x.h"
#include "system_kl.h"

// Clock definitions
#if defined SYS_CLK_HSI_DIRECT
uint32_t SystemCoreClock = 8000000;
#endif

/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  */
void SystemInit (void) {
    // Reset the RCC clock configuration to the default reset state(for debug purpose)
    RCC->CR |= (uint32_t)0x00000001;  // Set HSION bit
    // Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits
#ifndef STM32F10X_CL
    RCC->CFGR &= (uint32_t)0xF8FF0000;
#else
    RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif 
    RCC->CR   &= (uint32_t)0xFEF6FFFF;  // Reset HSEON, CSSON and PLLON bits
    RCC->CR   &= (uint32_t)0xFFFBFFFF;  // Reset HSEBYP bit
    RCC->CFGR &= (uint32_t)0xFF80FFFF;  // Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits
#ifdef STM32F10X_CL
    RCC->CR &= (uint32_t)0xEBFFFFFF;    // Reset PLL2ON and PLL3ON bits
    RCC->CIR = 0x00FF0000;              // Disable all interrupts and clear pending bits
    RCC->CFGR2 = 0x00000000;            // Reset CFGR2 register
#elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)
    RCC->CIR = 0x009F0000;      // Disable all interrupts and clear pending bits
    RCC->CFGR2 = 0x00000000;    // Reset CFGR2 register
#else
    RCC->CIR = 0x009F0000;      // Disable all interrupts and clear pending bits
#endif /* STM32F10X_CL */

    // ==== Setup clocks ====
#ifndef SYS_CLK_HSI_DIRECT
    // Setup sys clock
#endif
    // Setup peripheral clk
    RCC_PCLK2Config(SYS_APB2_CLK_DIVIDER);

    // ==== Setup IRQ vector table ====
    SCB->VTOR = FLASH_BASE;
}
