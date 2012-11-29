/*
 * ModBusRTU.cpp
 *
 *  Created on: 25.11.2012
 *      Author: Stefan
 */
#include "ModBusRTU.h"
#include "crc_8_16_32.h"
#include <string.h>
void ModBusRTU_Class :: Init(void)
{
	Rs485.Init();
	chModBusRxState=MODBUS_RX_IDLE;
	chModBusTxState=MODBUS_TX_IDLE;
	chSendReq=0;
	chTxBufSize=0;

}
void ModBusRTU_Class :: Task(void)
{
	uint8_t chByte;
	switch (chModBusRxState)
	{
	case MODBUS_RX_IDLE:
		if (Rs485.ReadByte(&chByte)==1) // ������ ������ ����
		{
			chModBusRxState=MODBUS_RX_WAITE_NEXT_BYTE;
			chRxBuf[0]=chByte;
			chRxBufSize=1;
		}
		break;
	case MODBUS_RX_WAITE_NEXT_BYTE:
		// ���� �������� �������, �� �������� ����������� MODBUS_RX_END
		if (Rs485.ReadByte(&chByte)==1)
		{
			chRxBuf[chRxBufSize]=chByte;
			chRxBufSize++;
		}
			break;
	case MODBUS_RX_END:
		/* ���������� CRC16, ���� ������� - �������� CALLBACK, ���� ��� - �� ���������� �����.
		 * ����� �������� ������ CRC ERROR */
			break;
	}

	switch (chModBusTxState)
	{
	case MODBUS_TX_IDLE:
		if (chSendReq==1)
		{
			Rs485.GetBus();
			chSendReq=0;
			chModBusTxState=MODBUS_TX_GET_BUS;
		}
		break;
	case MODBUS_TX_GET_BUS:
		if (Rs485.BusIsReady())// �������� ����� �� ��������
		{
			Rs485.SendData(chTxBufSize,chTxBuf);
			chModBusTxState=MODBUS_WAIT_TX_END;
		}
		break;
	case MODBUS_WAIT_TX_END:
		if (Rs485.BusIsReady())// �������� ����� �� ��������
		{
			chModBusTxState=MODBUS_TX_END_TIMEOUT;
		}
		break;
	case MODBUS_TX_END_TIMEOUT:// ������� ������� ����� ��������
		chModBusTxState=MODBUS_TX_IDLE;
		Rs485.FreeBus();
		break;
	}
}
void ModBusRTU_Class :: SendComand(ModBusPacket_t* pModBusPacket)
{
	//memcpy(&TxPacket,pModBusPacket,sizeof (ModBusPacket_t)) ;
	ModBusCrc16Calc(pModBusPacket);
	chTxBuf[0]=pModBusPacket->chAddr;
	chTxBuf[1]=pModBusPacket->chFunc;
	memcpy((chTxBuf+2),pModBusPacket->chDataBuf,pModBusPacket->chDataSize); // �������� ������, chDataSize
	memcpy((chTxBuf+2+pModBusPacket->chDataSize),&(pModBusPacket->iCrc16),2); // �������� CRC16, ��� �����
	chTxBufSize=2+pModBusPacket->chDataSize+2;
	chSendReq=1;
}
void ModBusRTU_Class :: GetData(void)
{

}
void ModBusCrc16Calc(ModBusPacket_t* pModBusPacket)
{
	/* ��� ����� ���������� CRC16 � �������� ��� ���� � ������.*/
	pModBusPacket->iCrc16=crc16_tbl_buf(pModBusPacket->chDataBuf,MODBUS_CRC16_INIT,pModBusPacket->chDataSize);
}
bool ModBusCrc16Check(ModBusPacket_t* pModBusPacket)
{
	/* ��� ����� ��������� CRC16 */
	if (pModBusPacket->iCrc16==crc16_tbl_buf(pModBusPacket->chDataBuf,MODBUS_CRC16_INIT,pModBusPacket->chDataSize)) return true;
	return false;
}
