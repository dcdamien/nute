/*
 * lock_action.cpp
 *
 *  Created on: 06.11.2011
 *      Author: Stefan
 */
#include "lock_action.h"
#include "delay_util.h"
//#include "lcd110x.h"
#include "media.h"
//#include "sensors.h"
#include "kl_ini.h"
//#include "lca.h"

#include "ff.h"
#include "diskio.h"
//#include "uart.h"
#include <stdio.h>

Lock_t ELock;

void Lock_t::Init()
{
	chLockState=LOCK_NORMAL;
	chNormState=NORMAL_START;
	ReadPasswordFromSD();
}

void Lock_t::Task()
{
    switch (chLockState)
    {
	case LOCK_NORMAL:
	  NormalTask();
	  break;
	case LOCK_BREAKED:
	  //BreakedTask();
      break;
    case LOCK_HACKED:
      //HackedTask();
       break;
    case LOCK_RESTART:
      //RestartTask();
      break;
	}
}
/*
��������� ��� ������� ������, ���������� 0-������� 1- ������������
 */
uint8_t Lock_t::KeyPressed(uint8_t chKey)
{
  if (bKeyFlag) return 1;
    else bKeyFlag=true;
  chNewKey=chKey;
  return 0;
}
/*
 * ������� ������ ����� � ���������� ������
 * ��������� ������� ������ ���������/��������� �����
 */
void Lock_t::NormalTask()
{
  switch (chNormState)
  {
    case NORMAL_START:
      chKeyCount=0;
      chErrorCount=0;
      if (ESnd.State!=sndPlaying) chNormState=NORMAL_ON; //����������� ��� ���������
      break;
    case NORMAL_ON: // �������� ���������, ����� ������
      if (bKeyFlag) // ���� ������ ������
      {
          bKeyFlag=false;
          if (chNewKey==chPassword[chKeyCount]) // ���������� ������
            {
              ESnd.Play(SOUND_BEEP_PASS);
              chKeyCount++;
            }
          else                                  // ������������ ������
            {
              ESnd.Play(SOUND_BEEP_FAIL);
              //if (chKeyCount>1)  ESnd.Play(SOUND_CODE_RESET);
              chKeyCount=0;
              chErrorCount++;
            }
          if (chKeyCount==chPasswordLength)
            {
              ESnd.Play(SOUND_LOCK_OPEN);
              chNormState=NORMAL_OPEN;
              Open();
              Delay.Reset(&wOpenTimer);
            }
          if (chErrorCount==chMaxCodeError) // ������� ����� ������ ��� ������ ����
            {
              chNormState=NORMAL_BLOCK;
              ESnd.Play(SOUND_LOCK_BLOCK_LONG);
            }
      }
      break;
    case NORMAL_OPEN:  // ����� ������ ��������� �����
      if (Delay.Elapsed(&wOpenTimer, LOCK_OPEN_TIME))
        {
          ESnd.Play(SOUND_LOCK_CLOSE);
          chNormState=NORMAL_CLOSE;
        }
      break;
    case NORMAL_CLOSE: // ����� ����������� ����� ��������������
      if (ESnd.State!=sndPlaying)
        {
          Close();
          chNormState=NORMAL_START;
        }
      break;
    case NORMAL_BLOCK:           // ����� ������������
      if (ESnd.State==sndPlaying) bKeyFlag=false; // �������� ������
      if (bKeyFlag) // ���� ������ ������
      {
          ESnd.Play(SOUND_LOCK_BLOCK_SHORT);
          bKeyFlag=false; // ����, ��� ���������� ������ �����, ��� �� ����� �����.
      }
      if (Delay.Elapsed(&wBlockTimer, LOCK_BLOCK_TIME)) // ������ ����� �������������� �����
      {
          ESnd.Play(SOUND_LOCK_UNBOCK);
          chNormState=NORMAL_START;
      }
      break;

  }
}

void Lock_t::Close()
{
}
void Lock_t::Open()
{
}

/*****  UsbRecData *******************/
/* ���������� �����, ��������� ���������� �����
   �������, ����������� �� USB */
/*************************************/
void Lock_t::UsbRecData(uint8_t* pData, uint8_t iSize)
{
  if (pData==NULL) return;
  uint8_t i=0;
  while (i<iSize)
    {
     if (chUsbRxCounter==USB_RX_BUF_SIZE) return; // ����� ����� �� ������������
     chUsbRxBuf[chUsbRxCounter]=*pData;
     pData++;
     chUsbRxCounter++;
     i++;
    }
  return;
}



void Lock_t::ReadPasswordFromSD()
{
  chPassword[0]=0;
  chPassword[1]=0;
  chPassword[2]=0;
  chPassword[3]=0;
  //chPasswordLength=4;// �� �� ����� MAX_PASS_LEN
  chPasswordLength = ReadInt32("PASSWORD", "PASSLENGTH","lock.ini");
  if (chPasswordLength>MAX_PASS_LEN)  chPasswordLength=MAX_PASS_LEN;
  ReadString("PASSWORD", "PASS", chPassword, chPasswordLength , "lock.ini");

  chMaxCodeError=5;
}
