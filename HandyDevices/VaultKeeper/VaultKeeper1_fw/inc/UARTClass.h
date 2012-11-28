/* ����� ��� ������ � UART-��
  �������� ��� ����������� ������� */


#ifndef UARTCLASS_H
#define UARTCLASS_H


// Library configuration file.
#include "stm32f10x_conf.h"
#include "FIFOClass.h"
#include <string.h>
#include <stdint.h>



#define USART2_CLK      	RCC_APB1Periph_USART2
#define USART2_TxPin   		GPIO_Pin_2
#define USART2_RxPin   		GPIO_Pin_3
#define USART2_GPIO     	GPIOA
#define USART2_GPIO_CLK 	RCC_APB2Periph_GPIOA


#define UART2_BUF_SIZE 				256
#define UART2_BAUD_RATE             115200
#define UART2_PARITY                USART_Parity_No
#define UART2_BITS                  USART_StopBits_2

//
//typedef struct
//{
//    signed portCHAR* pData;
//    portBASE_TYPE   iSize;
//} MessageBuf_t;

class UART_Class {
private:
    USART_TypeDef* pUART;
    uint8_t cChar;

public:
    uint16_t        eco_in_flag; // ���� ���������� ��� (�� ��� ������ - �������� �� �����)
    uint16_t        eco_out_flag;// ���� ���������� ��� (�� ��� ������� - �������� �� ����)
    FIFO_Class FIFO_TxData;
    FIFO_Class FIFO_RxData;
    uint16_t TxCompleteFlag;
    void UART_Init(USART_TypeDef* UART);
    void UART_StartTx(void);
    void UART_StartRx(void);
    void UART_StopTx(void);
    void UART_StopRx(void);
    void UART_Enable(void);
    void UART_Disable(void);
    //void SendPrintF(const char *fmt, ...);
    void SendByte(char chData);
    uint16_t SendDataBuf(uint16_t iDataSize,uint8_t* pchDataBuf);

    void UART_InterruptHandler(void);
    void UART_DeInit();
    // ~UART_Class(void); // ����������
};

extern UART_Class* pUART1;
extern UART_Class* pUART2;
extern UART_Class* pUART3;
extern UART_Class* pUART4;
extern UART_Class* pUART5;

// Declare IRQ. Use externC to make it visible from asm file.
extern "C" {
//void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
//void USART3_IRQHandler(void);
//void USART4_IRQHandler(void);
//void USART5_IRQHandler(void);
}

#endif /* UARTCLASS_H */
