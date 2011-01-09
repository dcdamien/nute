#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"
#include "uart.h"
//#include "si4432.h"

#include "stm32f10x_tim.h"


// Types
struct SiSvc_t {
    uint32_t Timer;
};

// Variables
struct SiSvc_t SiSvc1;

// Initialization
void GeneralInit(void);
void LEDInit(void) {
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = LEDG_PIN | LEDB_PIN;

  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}
void BtnInit (void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = BTN_P;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void ReadIRQs(void) {
 //   uint8_t R;
//    R = SiReadRegister(0x03);
//    UARTSendAsHex(R);
//    UARTSend(' ');
 //   R = SiReadRegister(0x04);
  //  UARTSendAsHex(R);
  //  UARTNewLine();
}

//void SysTick_Handler (void) {
//  static uint32_t ticks;
//
//  if (ticks++ >= 72) {
//    ticks = 0;
//    LED_GPIO_PORT->ODR ^= LEDG_PIN;
//    //ReadIRQs();
//
//    //SI_WriteRegister(0x25, 0x55);
//    //SI_ReadRegister(1);
//
//    //UARTSend('a');
//  }
//}

int main(void) {
    GeneralInit();
    
    Uart.PrintString("\rrf22\r");

    uint32_t tmr;
    //LEDB_ON();

    while (1) {
        if (Delay.Elapsed(&tmr, 500)) Uart.Print('a');

        //Task_Si();
//        if (BTN_IS_PRESSED()) LEDB_ON();
//        else
        //LEDB_ON();
    }
}

void GeneralInit(void) {
    LEDInit();
    Uart.Init();
    //SiInit();
    BtnInit();
    Delay.Init();
}

void Task_Si(void) {
//    if (DelayElapsed(&SiSvc1.Timer, 200)) {
//        LEDB_ON();
//        // Prepare IRQs
//        SiSetIRQs(SI_IRQ1_PKT_SENT, SI_IRQ2_NONE);
//        // Prepare TX packet
//        SiSetPktTotalLength(6);
//        Si.TX_Pkt.PacketID++;
//        Si.TX_Pkt.CommandID = 0x01;
//        Si.TX_Pkt.Data[0] = 'A';
//        Si.TX_Pkt.Data[1] = 'i';
//        Si.TX_Pkt.Data[2] = 'y';
//        Si.TX_Pkt.Data[3] = 'a';
//        SiTransmitPkt();
//        SI_WAIT_IRQ();
//        SiFlushIRQs();
//        //ReadIRQs();
   //     LEDB_OFF();
   // }
}