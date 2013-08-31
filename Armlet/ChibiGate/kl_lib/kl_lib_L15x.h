/*
 * kl_lib_L15xx.h
 *
 *  Created on: 10.12.2012
 *      Author: kreyl
 */

#ifndef KL_LIB_L15xx_H_
#define KL_LIB_L15xx_H_

#include "stm32l1xx.h"
#include "ch.h"
#include "hal.h"
#include "clocking_L15x.h"

extern "C" {
void __attribute__ ((weak)) _init(void)  {}
}

// =============================== General =====================================
#define PACKED __attribute__ ((__packed__))
#ifndef countof
#define countof(A)  (sizeof(A)/sizeof(A[0]))
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// Return values
#define OK              0
#define FAILURE         1
#define TIMEOUT         2
#define BUSY            3
#define NEW             4
#define IN_PROGRESS     5
#define LAST            6
#define CMD_ERROR       7

// Binary semaphores
#define NOT_TAKEN       false
#define TAKEN           true

enum BitOrder_t {boMSB, boLSB};
enum LowHigh_t  {Low, High};
enum RiseFall_t {Rising, Falling};

typedef void (*ftVoidVoid)(void);

// Simple pseudofunctions
#define TRIM_VALUE(v, Max)  { if((v) > (Max)) (v) = (Max); }
#define IS_LIKE(v, precise, deviation)  (((precise - deviation) < v) and (v < (precise + deviation)))

#define ANY_OF_2(a, b1, b2)             (((a)==(b1)) or ((a)==(b2)))
#define ANY_OF_3(a, b1, b2, b3)         (((a)==(b1)) or ((a)==(b2)) or ((a)==(b3)))
#define ANY_OF_4(a, b1, b2, b3, b4)     (((a)==(b1)) or ((a)==(b2)) or ((a)==(b3)) or ((a)==(b4)))
#define ANY_OF_5(a, b1, b2, b3, b4, b5) (((a)==(b1)) or ((a)==(b2)) or ((a)==(b3)) or ((a)==(b4)) or ((a)==(b5)))

// IRQ priorities
#define IRQ_PRIO_LOW            15  // Minimum
#define IRQ_PRIO_MEDIUM         9
#define IRQ_PRIO_HIGH           7
#define IRQ_PRIO_VERYHIGH       4 // Higher than systick

// DMA
#define DMA_PRIORITY_LOW        STM32_DMA_CR_PL(0b00)
#define DMA_PRIORITY_MEDIUM     STM32_DMA_CR_PL(0b01)
#define DMA_PRIORITY_HIGH       STM32_DMA_CR_PL(0b10)
#define DMA_PRIORITY_VERYHIGH   STM32_DMA_CR_PL(0b11)

// ============================ Simple delay ===================================
static inline void DelayLoop(volatile uint32_t ACounter) { while(ACounter--); }
static inline void Delay_ms(uint32_t Ams) {
    volatile uint32_t __ticks = (Clk.AHBFreqHz / 4000) * Ams;
    DelayLoop(__ticks);
}

// ===================== Single pin manipulations ==============================
enum PinOutMode_t {
    omPushPull  = 0,
    omOpenDrain = 1
};
enum PinPullUpDown_t {
    pudNone = 0b00,
    pudPullUp = 0b01,
    pudPullDown = 0b10
};
enum PinSpeed_t {
    ps400kHz = 0b00,
    ps2MHz   = 0b01,
    ps10MHz  = 0b10,
    ps40MHz  = 0b11
};
enum PinAF_t {
    AF0=0, AF1=1, AF2=2, AF3=3, AF4=4, AF5=5, AF6=6, AF7=7,
    AF8=8, AF9=9,AF10=10, AF11=11, AF12=12, AF13=13, AF14=14, AF15=15
};

// Set/clear
static inline void PinSet    (GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) { PGpioPort->BSRRL = (uint16_t)(1<<APinNumber); }
static inline void PinClear  (GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) { PGpioPort->BSRRH = (uint16_t)(1<<APinNumber); }
static inline void PinToggle (GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) { PGpioPort->ODR  ^= (uint16_t)(1<<APinNumber); }
// Check state
static inline bool PinIsSet(GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) { return (PGpioPort->IDR & (uint32_t)(1<<APinNumber)); }
// Setup
static inline void PinClockEnable(GPIO_TypeDef *PGpioPort) {
    if     (PGpioPort == GPIOA) RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    else if(PGpioPort == GPIOB) RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    else if(PGpioPort == GPIOC) RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    else if(PGpioPort == GPIOD) RCC->AHBENR |= RCC_AHBENR_GPIODEN;
}
static inline void PinSetupOut(
        GPIO_TypeDef *PGpioPort,
        const uint16_t APinNumber,
        const PinOutMode_t PinOutMode,
        const PinPullUpDown_t APullUpDown = pudNone,
        const PinSpeed_t ASpeed = ps40MHz
        ) {
    // Clock
    PinClockEnable(PGpioPort);
    uint8_t Offset = APinNumber*2;
    // Setup mode
    PGpioPort->MODER &= ~(0b11 << Offset);  // clear previous bits
    PGpioPort->MODER |=   0b01 << Offset;   // Set new bits
    // Setup output type
    PGpioPort->OTYPER &= ~(1<<APinNumber);
    PGpioPort->OTYPER |= (uint32_t)PinOutMode << APinNumber;
    // Setup Pull-Up or Pull-Down
    PGpioPort->PUPDR &= ~(0b11 << Offset); // clear previous bits
    PGpioPort->PUPDR |= (uint32_t)APullUpDown << Offset;
    // Setup speed
    PGpioPort->OSPEEDR &= ~(0b11 << Offset); // clear previous bits
    PGpioPort->OSPEEDR |= (uint32_t)ASpeed << Offset;

}
static inline void PinSetupIn(
        GPIO_TypeDef *PGpioPort,
        const uint16_t APinNumber,
        const PinPullUpDown_t APullUpDown
        ) {
    // Clock
    PinClockEnable(PGpioPort);
    // Setup mode
    PGpioPort->MODER &= ~(0b11 << (APinNumber*2)); // clear previous bits
    // Setup Pull-Up or Pull-Down
    PGpioPort->PUPDR &= ~(0b11 << (APinNumber*2)); // clear previous bits
    PGpioPort->PUPDR |= (uint32_t)APullUpDown << (APinNumber*2);
}
static inline void PinSetupAnalog(GPIO_TypeDef *PGpioPort, const uint16_t APinNumber) {
    // Clock
    PinClockEnable(PGpioPort);
    // Setup mode
    PGpioPort->MODER |= 0b11 << (APinNumber*2);  // Set new bits
    // Disable pull-up/down
    PGpioPort->PUPDR &= ~(0b11 << (APinNumber*2)); // clear previous bits
}

static inline void PinSetupAlterFunc(
        GPIO_TypeDef *PGpioPort,
        const uint16_t APinNumber,
        const PinOutMode_t PinOutMode,
        const PinPullUpDown_t APullUpDown,
        const PinAF_t AAlterFunc,
        const PinSpeed_t ASpeed = ps10MHz) {
    // Clock
    PinClockEnable(PGpioPort);
    uint32_t Offset = APinNumber*2;
    // Setup mode
    PGpioPort->MODER &= ~(0b11 << Offset);  // clear previous bits
    PGpioPort->MODER |= 0b10 << Offset;     // Set new bits
    // Setup output type
    PGpioPort->OTYPER &= ~(1<<APinNumber);
    PGpioPort->OTYPER |= (uint32_t)PinOutMode << APinNumber;
    // Setup Pull-Up or Pull-Down
    PGpioPort->PUPDR &= ~(0b11 << Offset); // clear previous bits
    PGpioPort->PUPDR |= (uint32_t)APullUpDown << Offset;
    // Setup speed
    PGpioPort->OSPEEDR &= ~(0b11 << Offset); // clear previous bits
    PGpioPort->OSPEEDR |= (uint32_t)ASpeed << Offset;
    // Setup Alternate Function
    uint32_t n = (APinNumber <= 7)? 0 : 1;      // 0 if 0...7, 1 if 8..15
    Offset = 4 * ((APinNumber <= 7)? APinNumber : APinNumber - 8);
    PGpioPort->AFR[n] &= ~(0b1111 << Offset);
    PGpioPort->AFR[n] |= (uint32_t)AAlterFunc << Offset;
}

//class PwmPin_t {
//private:
//    uint32_t *PClk;
//    TIM_TypeDef* Tim;
//public:
//    __IO uint16_t *PCCR;    // Made public to allow DMA
//    void SetFreqHz(uint32_t FreqHz);
//    void Init(GPIO_TypeDef *GPIO, uint16_t N, uint8_t TimN, uint8_t Chnl, uint16_t TopValue, bool Inverted=false);
//    void Set(uint16_t Value) { *PCCR = Value; }
//    void Off() { *PCCR = 0; }
//};

// ==== External IRQ ====
//enum ExtiTrigType_t {
//static inline void PinIrqSetup(GPIO_TypeDef *PGpioPort, const uint8_t APinNumber, EXTITrigger_TypeDef ATriggerType) {
//    // Get IRQ channel
//    uint8_t IChannel;
//    if      ((APinNumber >= 0)  and (APinNumber <= 4))  IChannel = EXTI0_IRQn + APinNumber;
//    else if ((APinNumber >= 5)  and (APinNumber <= 9))  IChannel = EXTI9_5_IRQn;
//    else if ((APinNumber >= 10) and (APinNumber <= 15)) IChannel = EXTI15_10_IRQn;
//
//}
//
//
//uint8_t N = APinNumber / 4;    // Indx of EXTICR register
//uint8_t Shift = (APinNumber & 0x03) * 4;
//AFIO->EXTICR[N] &= ~((uint32_t)0b1111 << Shift);    // Clear bits

// ================================= Timers ====================================
enum TmrTrigInput_t {tiITR0=0x00, tiITR1=0x10, tiITR2=0x20, tiITR3=0x30, tiTIED=0x40, tiTI1FP1=0x50, tiTI2FP2=0x60, tiETRF=0x70};
enum TmrMasterMode_t {mmReset=0x00, mmEnable=0x10, mmUpdate=0x20, mmComparePulse=0x30, mmCompare1=0x40, mmCompare2=0x50, mmCompare3=0x60, mmCompare4=0x70};
enum TmrSlaveMode_t {smDisable=0, smEncoder1=1, smEncoder2=2, smEncoder3=3, smReset=4, smGated=5, smTrigger=6, smExternal=7};
enum Inverted_t {invNotInverted, invInverted};

class Timer_t {
private:
    TIM_TypeDef* ITmr;
    uint32_t *PClk;
public:
    __IO uint32_t *PCCR;    // Made public to allow DMA
    // Common
    void Init(TIM_TypeDef* Tmr);
    void Deinit();
    inline void Enable()  { ITmr->CR1 |=  TIM_CR1_CEN; }
    inline void Disable() { ITmr->CR1 &= ~TIM_CR1_CEN; }
    inline void SetUpdateFrequency(uint32_t FreqHz) { SetTopValue(*PClk / FreqHz); }
    inline void SetTopValue(uint16_t Value) { ITmr->ARR = Value; }
    inline uint16_t GetTopValue() { return ITmr->ARR; }
    inline void SetupPrescaler(uint32_t PrescaledFreqHz) { ITmr->PSC = (*PClk / PrescaledFreqHz) - 1; }
    inline void SetCounter(uint16_t Value) { ITmr->CNT = Value; }
    inline uint16_t GetCounter() { return ITmr->CNT; }
    // Master/Slave
    inline void SetTriggerInput(TmrTrigInput_t TrgInput) {
        uint16_t tmp = ITmr->SMCR;
        tmp &= ~TIM_SMCR_TS;   // Clear bits
        tmp |= (uint16_t)TrgInput;
        ITmr->SMCR = tmp;
    }
    inline void MasterModeSelect(TmrMasterMode_t MasterMode) {
        uint16_t tmp = ITmr->CR2;
        tmp &= ~TIM_CR2_MMS;
        tmp |= (uint16_t)MasterMode;
        ITmr->CR2 = tmp;
    }
    inline void SlaveModeSelect(TmrSlaveMode_t SlaveMode) {
        uint16_t tmp = ITmr->SMCR;
        tmp &= ~TIM_SMCR_SMS;
        tmp |= (uint16_t)SlaveMode;
        ITmr->SMCR = tmp;
    }
    // DMA, Irq, Evt
    inline void DmaOnTriggerEnable() { ITmr->DIER |= TIM_DIER_TDE; }
    inline void GenerateUpdateEvt()  { ITmr->EGR = TIM_EGR_UG; }
    // PWM
    void PwmInit(GPIO_TypeDef *GPIO, uint16_t N, uint8_t Chnl, Inverted_t Inverted, const PinSpeed_t ASpeed = ps10MHz);
    void PwmSet(uint16_t Value) { *PCCR = Value; }
};


// ================================= IWDG ======================================
enum IwdgPre_t {
    iwdgPre4 = 0x00,
    iwdgPre8 = 0x01,
    iwdgPre16 = 0x02,
    iwdgPre32 = 0x03,
    iwdgPre64 = 0x04,
    iwdgPre128 = 0x05,
    iwdgPre256 = 0x06
};

class IWDG_t {
private:
    void EnableAccess() { IWDG->KR = 0x5555; }
    void SetPrescaler(IwdgPre_t Prescaler) { IWDG->PR = (uint32_t)Prescaler; }
    void SetReload(uint16_t Reload) { IWDG->RLR = Reload; }
public:
    void Reload() { IWDG->KR = 0xAAAA; }
    void Enable() { IWDG->KR = 0xCCCC; }
    void SetTimeout(uint32_t ms) {
        EnableAccess();
        SetPrescaler(iwdgPre256);
        uint32_t Count = (ms * (LSI_FREQ_HZ/1000)) / 256;
        TRIM_VALUE(Count, 0xFFF);
        SetReload(Count);
        Reload();
    }
    bool ResetOccured() {
        if(RCC->CSR & RCC_CSR_IWDGRSTF) {
            RCC->CSR |= RCC_CSR_RMVF;   // Clear flags
            return true;
        }
        else return false;
    }
};


// ============================== UART command =================================
//#define DBG_UART_ENABLED

#ifdef DBG_UART_ENABLED
#define UART_TXBUF_SIZE     504
#define UART_SPRINTBUF_SZ   99
#define UART                USART1
#define UART_GPIO           GPIOA
#define UART_TX_PIN         9
#define UART_AF             AF7
#define UART_DMA            STM32_DMA1_STREAM4
#define UART_RCC_ENABLE()   rccEnableUSART1(FALSE)

#define UART_DMA_MODE       DMA_PRIORITY_LOW | \
                            STM32_DMA_CR_MSIZE_BYTE | \
                            STM32_DMA_CR_PSIZE_BYTE | \
                            STM32_DMA_CR_MINC |       /* Memory pointer increase */ \
                            STM32_DMA_CR_DIR_M2P |    /* Direction is memory to peripheral */ \
                            STM32_DMA_CR_TCIE         /* Enable Transmission Complete IRQ */


class DbgUart_t {
private:
    uint8_t TXBuf[UART_TXBUF_SIZE];
    char SprintfBuf[UART_SPRINTBUF_SZ];
    uint8_t *PWrite, *PRead;
    bool IDmaIsIdle;
    uint32_t IFullSlotsCount, ITransSize;
public:
    void Printf(const char *S, ...);
    void PrintNow(const char *S) {
        while(*S != 0) {
            while(!(USART1->SR & USART_SR_TXE));
            USART1->DR = *S++;
        }
    }
    void FlushTx() { while(!IDmaIsIdle); }  // wait DMA
    void Init(uint32_t ABaudrate);
    void IRQDmaTxHandler();
};

extern DbgUart_t Uart;
#endif

// ================================= SPI =======================================
enum CPHA_t {cphaFirstEdge, cphaSecondEdge};
enum CPOL_t {cpolIdleLow, cpolIdleHigh};
enum SpiBaudrate_t {
    sbFdiv2   = 0b000,
    sbFdiv4   = 0b001,
    sbFdiv8   = 0b010,
    sbFdiv16  = 0b011,
    sbFdiv32  = 0b100,
    sbFdiv64  = 0b101,
    sbFdiv128 = 0b110,
    sbFdiv256 = 0b111,
};

static inline void SpiSetup(
        SPI_TypeDef *Spi,
        BitOrder_t BitOrder,
        CPOL_t CPOL,
        CPHA_t CPHA,
        SpiBaudrate_t Baudrate
        ) {
    // Clocking
    if      (Spi == SPI1) { rccEnableSPI1(FALSE); }
#ifndef STM32F10X_LD_VL
    else if (Spi == SPI2) { rccEnableSPI2(FALSE); }
#endif
    // Mode: Master, NSS software controlled and is 1, 8bit, NoCRC, FullDuplex
    Spi->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_MSTR;
    if(BitOrder == boLSB) Spi->CR1 |= SPI_CR1_LSBFIRST;     // MSB/LSB
    if(CPOL == cpolIdleHigh) Spi->CR1 |= SPI_CR1_CPOL;      // CPOL
    if(CPHA == cphaSecondEdge) Spi->CR1 |= SPI_CR1_CPHA;    // CPHA
    Spi->CR1 |= ((uint16_t)Baudrate) << 3;                  // Baudrate
    Spi->CR2 = 0;
}

static inline void SpiEnable (SPI_TypeDef *Spi) { Spi->CR1 |=  SPI_CR1_SPE; }
static inline void SpiDisable(SPI_TypeDef *Spi) { Spi->CR1 &= ~SPI_CR1_SPE; }


// =============================== I2C =========================================
#define I2C_DMATX_MODE  DMA_PRIORITY_LOW | \
                        STM32_DMA_CR_MSIZE_BYTE | \
                        STM32_DMA_CR_PSIZE_BYTE | \
                        STM32_DMA_CR_MINC |     /* Memory pointer increase */ \
                        STM32_DMA_CR_DIR_M2P |  /* Direction is memory to peripheral */ \
                        STM32_DMA_CR_TCIE       /* Enable Transmission Complete IRQ */

#define I2C_DMARX_MODE  DMA_PRIORITY_LOW | \
                        STM32_DMA_CR_MSIZE_BYTE | \
                        STM32_DMA_CR_PSIZE_BYTE | \
                        STM32_DMA_CR_MINC |         /* Memory pointer increase */ \
                        STM32_DMA_CR_DIR_P2M |      /* Direction is peripheral to memory */ \
                        STM32_DMA_CR_TCIE           /* Enable Transmission Complete IRQ */

class i2c_t {
private:
    I2C_TypeDef *ii2c;
    GPIO_TypeDef *IPGpio;
    uint16_t ISclPin, ISdaPin;
    uint32_t IBitrateHz;
    void SendStart()  { ii2c->CR1 |= I2C_CR1_START; }
    void SendStop()   { ii2c->CR1 |= I2C_CR1_STOP; }
    void AckEnable()  { ii2c->CR1 |= I2C_CR1_ACK; }
    void AckDisable() { ii2c->CR1 &= ~I2C_CR1_ACK; }
    bool RxIsNotEmpty()  { return (ii2c->SR1 & I2C_SR1_RXNE); }
    void ClearAddrFlag() { (void)ii2c->SR1; (void)ii2c->SR2; }
    void DmaLastTransferSet() { ii2c->CR2 |= I2C_CR2_LAST; }
    // Address and data
    void SendAddrWithWrite(uint8_t Addr) { ii2c->DR = (uint8_t)(Addr<<1); }
    void SendAddrWithRead (uint8_t Addr) { ii2c->DR = ((uint8_t)(Addr<<1)) | 0x01; }
    void SendData(uint8_t b) { ii2c->DR = b; }
    uint8_t ReceiveData() { return ii2c->DR; }
    // Flags operations
    uint8_t IBusyWait();
    uint8_t WaitEv5();
    uint8_t WaitEv6();
    uint8_t WaitEv8();
    uint8_t WaitAck();
    uint8_t WaitRx();
    uint8_t WaitStop();
public:
    bool Error;
    Thread *PRequestingThread;
    const stm32_dma_stream_t *PDmaTx, *PDmaRx;
    void Init(I2C_TypeDef *pi2c, GPIO_TypeDef *PGpio, uint16_t SclPin, uint16_t SdaPin, uint32_t BitrateHz,
            const stm32_dma_stream_t *APDmaTx, const stm32_dma_stream_t *APDmaRx);
    void Standby();
    void Resume();
    void Reset();
    uint8_t CmdWriteRead(uint8_t Addr, uint8_t *WPtr, uint8_t WLength, uint8_t *RPtr, uint8_t RLength);
    uint8_t CmdWriteWrite(uint8_t Addr, uint8_t *WPtr1, uint8_t WLength1, uint8_t *WPtr2, uint8_t WLength2);
};

#endif
