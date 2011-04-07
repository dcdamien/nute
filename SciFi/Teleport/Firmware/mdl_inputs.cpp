#include "mdl_inputs.h"
#include "delay_util.h"

#include "uart.h"

Inputs_t Inputs;

void Inputs_t::Init(void) {
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    // ==== GPIO ====
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    // PortA
    GPIO_InitStructure.GPIO_Pin = M5_1 | M5_2 | M5_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // PortB
    GPIO_InitStructure.GPIO_Pin = M1_1|M1_2|M1_3|M2_1|M2_2|M2_3|M3_1|M3_2|M3_3|M4_1|M4_2|M4_3;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    
}

void Inputs_t::Check() {
    if (!Delay.Elapsed(&Timer, DELAY_CHECK)) return;
    //ChangeOccured = false;
    Inlets[0] = 0;
    if(GPIO_ReadInputDataBit(M1_GPIO, M1_1)) Inlets[0] += 0x01;
    if(GPIO_ReadInputDataBit(M1_GPIO, M1_2)) Inlets[0] += 0x02;
    if(GPIO_ReadInputDataBit(M1_GPIO, M1_3)) Inlets[0] += 0x04;
    Inlets[1] = 0;
    if(GPIO_ReadInputDataBit(M2_GPIO, M2_1)) Inlets[1] += 0x01;
    if(GPIO_ReadInputDataBit(M2_GPIO, M2_2)) Inlets[1] += 0x02;
    if(GPIO_ReadInputDataBit(M2_GPIO, M2_3)) Inlets[1] += 0x04;
    Inlets[2] = 0;
    if(GPIO_ReadInputDataBit(M3_GPIO, M3_1)) Inlets[2] += 0x01;
    if(GPIO_ReadInputDataBit(M3_GPIO, M3_2)) Inlets[2] += 0x02;
    if(GPIO_ReadInputDataBit(M3_GPIO, M3_3)) Inlets[2] += 0x04;
    Inlets[3] = 0;
    if(GPIO_ReadInputDataBit(M4_GPIO, M4_1)) Inlets[3] += 0x01;
    if(GPIO_ReadInputDataBit(M4_GPIO, M4_2)) Inlets[3] += 0x02;
    if(GPIO_ReadInputDataBit(M4_GPIO, M4_3)) Inlets[3] += 0x04;
    Inlets[4] = 0;
    if(GPIO_ReadInputDataBit(M5_GPIO, M5_1)) Inlets[4] += 0x01;
    if(GPIO_ReadInputDataBit(M5_GPIO, M5_2)) Inlets[4] += 0x02;
    if(GPIO_ReadInputDataBit(M5_GPIO, M5_3)) Inlets[4] += 0x04;
    Uart.PrintUint(Inlets[0]);
    Uart.Print(' ');
    Uart.PrintUint(Inlets[1]);
    Uart.Print(' ');
    Uart.PrintUint(Inlets[2]);
    Uart.Print(' ');
    Uart.PrintUint(Inlets[3]);
    Uart.Print(' ');
    Uart.PrintUint(Inlets[4]);
    Uart.NewLine();
}