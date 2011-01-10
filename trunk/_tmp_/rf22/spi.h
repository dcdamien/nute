/* 
 * File:   spi.h
 * Author: Kreyl Laurelindo
 *
 * Created on 9 январь 2011 г., 18:18
 */

#ifndef SPI_H
#define	SPI_H

#include "stm32f10x.h"

void SPI_Setup(SPI_TypeDef* ASPI);
uint8_t SPI_ReadWriteByte (SPI_TypeDef* ASPI, uint8_t AByte);
void SPI_BusyWait(const SPI_TypeDef* ASPI);

#endif	/* SPI_H */

