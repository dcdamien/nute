#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"

// Initialization
void GeneralInit(void);

void UART_Task(void);

void LEDInit(void) {
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = LEDG_PIN | LEDB_PIN;

  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}
void BtnInit (void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = BTN_P;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


int main(void) {
    GeneralInit();
    while (1) {
        //LEDG_TOGGLE();
        //Delay.ms(100);
        //UART_Send('a');
        UART_Task();
    }
}

void GeneralInit(void) {
    LEDInit();
    //BtnInit();
    Delay.Init();
    UART_Init();
}


void UART_Task(void) {
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) return;
    LEDG_TOGGLE();
    uint8_t b = USART_ReceiveData(USART1);
    UART_Send(b);
}

void UART_Init(void) {
    // ==== Clocks init ====
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    // ==== GPIO init ====
    GPIO_InitTypeDef GPIO_InitStructure;
    // Configure USART Tx as alternate function push-pull
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // Configure USART Rx as input floating
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ==== USART configuration ====
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    // Enable USART
    USART_Cmd(USART1, ENABLE);

}
void UART_Send(uint8_t b) {
    USART_SendData(USART1, b);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}
