#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"
#include "uart.h"
#include "si4432.h"

#define LEDG_PIN        GPIO_Pin_9
#define LEDB_PIN        GPIO_Pin_8
#define LED_GPIO_PORT   GPIOC
#define LED_GPIO_CLK    RCC_APB2Periph_GPIOC

void GeneralInit(void);

void LEDInit(void) {
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = LEDG_PIN | LEDB_PIN;

  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}

#define LEDG_ON()   LED_GPIO_PORT->BSRR = LEDG_PIN
#define LEDB_ON()   LED_GPIO_PORT->BSRR = LEDB_PIN
#define LEDG_OFF()  LED_GPIO_PORT->BRR  = LEDG_PIN
#define LEDB_OFF()  LED_GPIO_PORT->BRR  = LEDB_PIN
//#define LEDB_TOGGLE()   LED_GPIO_PORT->BSRR = LEDB_PIN


#define BTN_P   GPIO_Pin_1
void BtnInit (void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = BTN_P;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
#define BTN_IS_PRESSED() (!GPIO_ReadInputDataBit(GPIOB, BTN_P))


void ReadIRQs(void) {
    uint8_t R;
    R = SiReadRegister(0x03);
    UARTSendAsHex(R);
    UARTSend(' ');
    R = SiReadRegister(0x04);
    UARTSendAsHex(R);
    UARTNewLine();
}

void SysTick_Handler (void) {
  static uint32_t ticks;

  if (ticks++ >= 45) {
    ticks = 0;
    LED_GPIO_PORT->ODR ^= LEDG_PIN;
    ReadIRQs();

    //SI_WriteRegister(0x25, 0x55);
    //SI_ReadRegister(1);

    //UARTSend('a');
  }
}

int main(void) {
    GeneralInit();
LEDG_ON();
    UARTSendString("\rrf22\r");
    Task_Si(); 
    while (1) {
        //UARTSend('a');
       // Delay_ms(100);
        
        //LEDB_TOGGLE();

//        if (BTN_IS_PRESSED()) LEDB_ON();
//        else LEDB_OFF();
    }
}

void GeneralInit(void) {
    LEDInit();
    UARTInit();
    SiInit();
    BtnInit();
    DelayInit();

    SysTick_Config(SystemCoreClock / 100);

}

void Task_Si(void) {
    LEDB_ON();
    // Prepare IRQs
    //SiSetIRQs(SI_IRQ1_PKT_SENT, SI_IRQ2_NONE);
    SiSetReady();
    UARTSend('r');
    //SiWriteRegister(0x05, 0x00);
    //SiWriteRegister(0x06, SI_IRQ2_CHIP_READY);

    // Prepare TX packet
    SiSetPktTotalLength(4);
    Si.TX_Pkt.PacketID++;
    Si.TX_Pkt.CommandID = 0x01;
    Si.TX_Pkt.Data[0] = 'A';
    Si.TX_Pkt.Data[1] = 'i';
//    Si.TX_Pkt.Data[2] = 'y';
//    Si.TX_Pkt.Data[3] = 'a';
//    //SiTransmitPkt();
    SiFIFOWrite(Si.TX_PktArray, Si.DataLength);    // Place TX packet to FIFO

//    SiWriteRegister(0x7F, 'a');
//    SiWriteRegister(0x7F, 'i');
//    SiWriteRegister(0x7F, 'y');
//    SiWriteRegister(0x7F, 'a');

    UARTSend('w');

    ReadIRQs();
    SiWriteRegister(0x05, 0x04);
    SiWriteRegister(0x06, 0x00);
    SiFlushIRQs();
    ReadIRQs();
   
    SiWriteRegister(0x07, 0x09);
//    SI_WAIT_IRQ();
    UARTSend('i');
    //SiWaitIRQ1(SI_IRQ1_PKT_SENT);
    LEDB_OFF();
}