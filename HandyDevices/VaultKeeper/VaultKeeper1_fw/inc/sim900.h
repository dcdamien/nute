/*
 * sim900.h
 *
 *  Created on: 01.06.2012
 *      Author: kreyl
 */

#ifndef SIM900_H_
#define SIM900_H_

#include <stdint.h>
#include "kl_lib.h"
#include "stm32f10x_usart.h"
#include "UARTClass.h"

#define MDM_LINE_LEN        54
#define MDM_DATA_LEN        540
#define MDM_BUF_LEN         504
#define MDM_RX_TIMEOUT      450   // ms
#define MDM_SIM_TIMEOUT     4005  // ms
#define MDM_NETREG_TIMEOUT  20007 // ms
#define GPRS_TIMEOUT        180000// ms
#define MDM_SMS_TIMEOUT     18000 // ms

class sim900_t {
private:
    Error_t RplKind;
    // Ring buffer
    char IBuf[MDM_BUF_LEN];
    uint32_t WriteIndx, ReadIndx;
    char BufRead(void) { char c = IBuf[ReadIndx++]; if(ReadIndx == MDM_BUF_LEN) ReadIndx = 0; return c;}
    bool BufIsEmpty(void) { return (ReadIndx == WriteIndx); }
    void BufReset(void) { ReadIndx = WriteIndx; }
    // RX
    char RxLine[MDM_LINE_LEN], TxLine[MDM_LINE_LEN];
    // Init
    void GPIOInit(void);
    void USARTInit(void);
    // Pins operations
    void PwrKeyHi(void) { klGpioSetByMsk(GPIOA, GPIO_Pin_15); }
    void PwrKeyLo(void) { klGpioClearByMsk(GPIOA, GPIO_Pin_15); }
    void PwrKeyPulse(void) { PwrKeyLo(); Delay.ms(1008); PwrKeyHi(); }
    void PowerOn(void)  { klGpioClearByMsk(GPIOB, GPIO_Pin_13); }
    void PowerOff(void) { klGpioSetByMsk  (GPIOB, GPIO_Pin_13); }
    // UART operations
    void WriteByte(uint8_t AByte) { USART1->DR = AByte; while (!(USART1->SR & USART_FLAG_TC)); }
    void IrqDisable(void) { USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); }
    void IrqEnable (void) { USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); }
    // Tx
    void SendString(const char *S);
    void MPrintString(const char *S) { char c; while ((c = *S++) != 0) WriteByte(c); }
    void MPrintUint(uint32_t ANumber);
    void MPrintf(const char *S, ...);
    // Commands
    Error_t Command(const char *ACmd, uint32_t ATimeout, const char *AReply);
    Error_t Command(const char *ACmd, uint32_t ATimeout) { return Command(ACmd, ATimeout, "OK"); }
    Error_t Command(const char *ACmd) { return Command(ACmd, MDM_RX_TIMEOUT, "OK"); }
    Error_t WaitString(const char *AString, uint32_t ATimeout);
    Error_t WaitChar(const char AChar, uint32_t ATimeout);
    Error_t WaitEmptyString(uint32_t ATimeout);
    Error_t WaitAnyString(uint32_t ATimeout);
    Error_t ReadRawData(char *Dst, uint32_t ALen, uint32_t ATimeout);
    // Inner use commands
    Error_t ProcessSim(void);
    Error_t DisableCellBrc(void);
    Error_t NetRegistration(void);
public:
    Error_t State;  // Modem state
    void Init(void);
    void On(void);
    void Off(void);
    // Hi-level
    char DataString[MDM_DATA_LEN+1];
    Error_t SendSMS(const char *ANumber, const char *AMsg);
    Error_t GprsOn(void);
    Error_t GprsOff(void);
    Error_t OpenConnection(const char *AHost);
    Error_t CloseConnection(void);
    Error_t GET(const char *AHost, const char *AUrl, char *AData, uint32_t ALen);
    Error_t POST(const char *AHost, const char *AUrl, const char *AData);
    // IRQ
    void BufWrite(char c) { IBuf[WriteIndx++] = c; if(WriteIndx == MDM_BUF_LEN) WriteIndx = 0; }
//    void IRQHandler(void);
};

extern sim900_t Mdm;
extern UART_Class DbgUART;

// USART RX IRQ
extern "C" {
void USART1_IRQHandler(void);
}


#endif /* SIM900_H_ */
