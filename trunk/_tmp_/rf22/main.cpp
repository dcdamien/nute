#include "stm32f10x.h"
#include "main.h"
#include "delay_util.h"
#include "uart.h"
#include "si4432.h"

#include "stm32f10x_tim.h"

void Si_Prepare2RX (void);

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
    Si.IRQsRead();
    Uart.PrintAsHex(Si.IRQ1);
    Uart.Print(' ');
    Uart.PrintAsHex(Si.IRQ2);
    Uart.NewLine();
}
void ReadIRQs2(void) {
    Si2.IRQsRead();
    Uart.PrintAsHex(Si2.IRQ1);
    Uart.Print(' ');
    Uart.PrintAsHex(Si2.IRQ2);
    Uart.NewLine();
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
    while (1) {
        Task_Si();
        Task_Si2();
    }
}

void GeneralInit(void) {
    LEDInit();
    Uart.Init();
    Si.Init(SPI1, br10000, bnd868);
    Si2.Init(SPI2, br10000, bnd868);
    Si_Prepare2RX();
    BtnInit();
    Delay.Init();
}

void Task_Si(void) {
    if (Delay.Elapsed(&SiSvc1.Timer, 200)) {
        LEDB_ON();
        // Prepare IRQs
        Si.IRQsSet(SI_IRQ1_PKT_SENT, SI_IRQ2_NONE);
        // Prepare TX packet
        Si.PktLengthSet(6);
        Si.TX_Pkt.PacketID++;
        Si.TX_Pkt.CommandID = 0x01;
        Si.TX_Pkt.Data[0] = 'A';
        Si.TX_Pkt.Data[1] = 'i';
        Si.TX_Pkt.Data[2] = 'y';
        Si.TX_Pkt.Data[3] = 'a';
        Si.TransmitPkt();
        Si.IRQWait();
        //Si.FlushIRQs();
        Si.IRQsRead();
        LEDB_OFF();
    }
}



void Task_Si2(void) {
    // Check IRQ
    if (!Si2.NIRQ_Is_Hi()) {    // Some IRQ fired
        LEDG_ON();
        Si2.IRQsRead();
        // Check if CRC
        if (Si2.IRQ1 & SI_IRQ1_CRC_ERR) {
            Si2.SetMode(SI_MODE_READY); // Disable RX
            Si2.FIFOReset();
            Uart.Print('c');
            Si2.SetMode(SI_MODE_RX);
        }
        else if (Si2.IRQ2 & SI_IRQ1_PKT_RCVD) {
            Si2.SetMode(SI_MODE_READY); // Disable RX
            Si2.PktLengthGet();
            Si2.FIFORead();

            Uart.PrintAsHex(Si2.RX_Pkt.CommandID);
            Uart.NewLine();
            Uart.PrintAsHex(Si2.RX_Pkt.PacketID);
            Uart.NewLine();
            for (uint8_t i=0; i<Si2.PktLength-2; i++) Uart.Print(Si2.RX_Pkt.Data[i]);
            Uart.NewLine();
            Si2.FIFOReset();
            Si2.SetMode(SI_MODE_RX);
        }
        LEDG_OFF();
    }

}

void Si_Prepare2RX (void) {
    Si2.SetMode(SI_MODE_RX);
    // Prepare IRQs
    Si2.IRQsSet(SI_IRQ1_PKT_RCVD | SI_IRQ1_CRC_ERR, SI_IRQ2_NONE);

}