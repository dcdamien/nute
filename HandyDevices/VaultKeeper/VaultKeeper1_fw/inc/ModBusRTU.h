/*
 * ModBusRTU.h
 *
 *  Created on: 25.11.2012
 *      Author: Stefan
 */

#ifndef MODBUSRTU_H_
#define MODBUSRTU_H_
#include <stdint.h>
#include "RS485Class.h"
#include "kl_time.h"
#include "DBG_Unit.h"

/* ----- ���� ������ ------*/
#define MODBUS_ERROR_CODE_NO_ERROR  		0
#define MODBUS_ERROR_CODE_BUS_NOT_READY  	1 // UART �� ����� � ��������.
#define MODBUS_ERROR_CODE_TX_FAIL  			2 // �������� ������� ������� �����. �������� ������ � UART-�
#define MODBUS_ERROR_CODE_RX_CRC_ERROR		3 // ������ � CRC16 ��������� ������


#define MODBUS_DATA_BUF_SIZE 	250
#define MODBUS_CRC16_INIT		0x00
/*������� �� ���������� (���� ��� � Serial Modbus RTU): ��� �������� 9600 � 11 �����
 � ����� (��������� ��� + 8 ��� ������ + ��� �������� �������� + ����-���):
 3.5 * 11 / 9600 = 0,00401041(6), �� ���� ����� 4 ��;
 1.5 * 11 / 9600 = 0,00171875, �� ���� ����� 1 ��.*/

#define MODBUS_RTU_MIN_TIMEOUT		2  // 1.5 �������, 1��. ����������� ����� ����� �������, ����� ������� ���������� ����� ���������� ������.
#define MODBUS_RTU_MAX_TIMEOUT		(MODBUS_RTU_MIN_TIMEOUT+3)  // 3.5 �������, 4��. ������������ ����� ����� ��������, ����� ������������� ������������� ����� ��������.

#define MODBUS_BUS_WAITE_TIMEOUT    	100 // ����� �������� ������������ UART-�
#define MODBUS_TX_END_WAITE_TIMEOUT		100 // ����� �������� ����� ��������.

#define MODBUS_RX_IDLE				0
#define MODBUS_RX_WAITE_NEXT_BYTE	1
#define MODBUS_RX_END				2
#define MODBUS_TX_IDLE				3
#define MODBUS_TX_GET_BUS			4
#define MODBUS_TX_END_TIMEOUT		5
#define MODBUS_WAIT_TX_END			6




class ModBusRTU_Class {
private:
	uint8_t chTxBuf[254];
	uint8_t chRxBuf[254];
	uint8_t chTxBufSize;
	uint8_t chRxBufSize;
	uint8_t chModBusRxState;
	uint8_t chModBusTxState;
	RS485_Class Rs485;
	uint8_t chSendReq;
	uint32_t iRxTimer;
	uint32_t iTxTimer;
	void (*CallBackFunc)(uint8_t* pchBuf,uint16_t iDataSize,uint8_t chErrorCode);
	bool ModBusCrc16Check(uint8_t* pchBuf,uint16_t iDataSize);
public:
    uint16_t        i;
    void Init(void);
    void SetCallBackFunc(void (*pCallBackFunc)(uint8_t* pchBuf,uint16_t iDataSize,uint8_t chErrorCode));
    void Task(void);
    void SendData (void);
    void GetData (void);
    void SendComand(uint8_t chAddr,uint8_t chFunc,uint8_t* pchBuf,uint16_t iDataSize);
};

extern DBG_Message_Class DbgMessage;

extern "C" {
unsigned short crc16_tbl_buf(unsigned char * buf, unsigned short crc,unsigned long len);
}
#endif /* MODBUSRTU_H_ */
