//benchmarks.caxapa.ru/source?test=20

/*
	����������:
		���������� CRC8, CRC16 � CRC32.

        �����������:
		��� ��������� ����������� � 32������� ������ char � short 
		(��������, Sharc) ��������� ������������� ����������� ����� 
		�� ��������� ���������� CRC	(��. ����������� ����).
*/


#ifndef CRC_8_16_32_H
#define CRC_8_16_32_H

/************************************ CRC8 ************************************/
/* Direct */
unsigned char crc8_sft_buf(unsigned char * buf, unsigned char crc,unsigned long len);
/* Table driven */
unsigned char crc8_tbl_buf(unsigned char * buf, unsigned char crc,unsigned long len);

/************************************ CRC16 ************************************/
/* Direct */
unsigned short crc16_sft_buf(unsigned char * buf, unsigned short crc,unsigned long len);
/* Table driven*/
unsigned short crc16_tbl_buf(unsigned char * buf, unsigned short crc,unsigned long len);
/************************************ CRC32 ************************************/
/* Direct */
unsigned long crc32_sft_buf(unsigned char * buf, unsigned long crc,unsigned long len);
/* Table driven*/
unsigned long crc32_tbl_buf(unsigned char * buf, unsigned long crc,unsigned long len);

#endif                /* CRC_8_16_32_H */
