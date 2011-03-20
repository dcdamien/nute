#include "dac.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_dma.h"

#include "sound_data.h"
#include "time_domain.h"

#include "uart.h"

Dac_t Dac;

void Dac_t::Init(void) {
    // ==== Clocks ====
    RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1,   ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,   ENABLE);
    // ==== GPIO ====
    // Once the DAC channel is enabled, the corresponding GPIO pin is automatically
    // connected to the DAC converter. In order to avoid parasitic consumption,
    // the GPIO pin should be configured in analog.
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // DAC Shutdown pin
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ==== DAC channel1 Configuration ====
    DAC_InitTypeDef DAC_InitStructure;
    DAC_InitStructure.DAC_Trigger = DAC_TRIGGER;    // Defined in time_domain.h
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    // ==== NVIC configuration ====
    NVIC_InitTypeDef NVIC_InitStructure;
    // Enable DMA1 channel3 IRQ Channel
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // ==== DMA1 channel3 configuration ====
    DMA_DeInit(DMA1_Channel3);
    DMA_InitTypeDef DMA_InitStructure;
    //DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&DAC->DHR8R1;    // 8bit register
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&DAC->DHR12R1;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Snd1;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = SND1_LEN;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 8 bit
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    //DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;   // 8 bit
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel3, ENABLE);
    // Enable DMA1 Channel3 Transfer Complete interrupt
    DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
    // ==== Last settings ====
    // Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is automatically connected to the DAC converter.
    DAC_Cmd(DAC_Channel_1, ENABLE);
    // Enable DMA for DAC Channel1
    DAC_DMACmd(DAC_Channel_1, ENABLE);
    // Disable all
    AmplifierOff();
    MayPlay = false;

      TIM_PrescalerConfig(TIM6, 1, TIM_PSCReloadMode_Update);
  TIM_SetAutoreload(TIM6, 363);
  /* TIM6 TRGO selection */
  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
  TIM_Cmd(TIM6, ENABLE);
}

