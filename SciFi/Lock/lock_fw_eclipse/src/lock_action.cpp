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
#include "uart.h"

#include "ff.h"
#include "diskio.h"
//#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Lock_t ELock;

void Lock_t::Init()
{
	chLockState=LOCK_NORMAL;
	chNormState=NORMAL_START;
	ReadSettingsFromSD();
}

void Lock_t::Task()
{
  if (bNewCommandFlag)  //������ ����� ������� �� UART-�
    {
      if (chLockState==LOCK_NORMAL) UART_PrintString("SERV MODE  \r");
      chLockState=LOCK_HACKED; // ����� ������
      chNormState=NORMAL_START; // ���������� ������� ���������� ������
      Delay.Reset(&wHackTimer);
    }

  switch (chLockState)
    {
      case LOCK_NORMAL:
	  NormalTask();
	  break;
      case LOCK_HACKED:
          if (Delay.Elapsed(&wHackTimer, HACK_DELAY_TIME)) // ������� ����� ������ ������
          {
            chLockState=LOCK_NORMAL;
            UART_PrintString("NORMAL MODE  \r");
          }
          HackedTask();
          break;

      case LOCK_BREAKED:
          //BreakedTask();
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
      if (ESnd.State==sndPlaying) bKeyFlag=false; // �������� ������, ���� ������������� ����
      if (bKeyFlag) // ���� ������ ������
      {
          bKeyFlag=false;
          if (chNewKey==chPassword[chKeyCount]) // ���������� ������
            {
              ESnd.Play(SOUND_BEEP_PASS);
              chKeyCount++;
              chErrorCount=0;
            }
          else                                  // ������������ ������
            {
              ESnd.Play(SOUND_BEEP_FAIL);
              chKeyCount=0;
              chErrorCount++;
            }
      }
      if ((chKeyCount==(chPasswordLength-1)) & (ESnd.State!=sndPlaying))
        {
          ESnd.Play(SOUND_LOCK_OPEN);
          chNormState=NORMAL_OPEN;
          Open();
          Delay.Reset(&wOpenTimer);
        }

      if ((chErrorCount>=chMaxCodeError) & (ESnd.State!=sndPlaying)) // ������� ����� ������ ��� ������ ����
      {
          chNormState=NORMAL_BLOCK;
          ESnd.Play(SOUND_LOCK_BLOCK_LONG);
          Delay.Reset(&wBlockTimer);
      }

      break;
    case NORMAL_OPEN:  // ����� ������ ��������� �����
      if (ESnd.State==sndPlaying) break;
      if (Delay.Elapsed(&wOpenTimer, wTimeToOpen))
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
      if (ESnd.State==sndPlaying)
        {
          bKeyFlag=false; // �������� ������
          break;    // �� ����� �������, �� ��������.
        }
      if (bKeyFlag) // ���� ������ ������
      {
          ESnd.Play(SOUND_LOCK_BLOCK_SHORT);
          bKeyFlag=false; // ����, ��� ���������� ������ �����, ��� �� ����� �����.
      }
      if (Delay.Elapsed(&wBlockTimer, wTimeToBlock)) // ������ ����� �������������� �����
      {
          ESnd.Play(SOUND_LOCK_UNBOCK);
          chNormState=NORMAL_START;
      }
      break;

  }
}

void Lock_t::Close()
{
  UART_PrintString("Lock Close \r");
}
void Lock_t::Open()
{
  UART_PrintString("Lock Open \r");
}

/*************** UsartRxEvent *************************
 * ��� ������� ���������� � ���������� UART-�
 * � ��������� ���� �� UART-�
 * ��������, � ��� ������ �������� UART_Print
 *****************************************************/
void Lock_t::UsartRxEvent(uint8_t chByte)
{
  //UART_Print(chByte);

  *(strRxBuf+iRxCounter)=chByte;
  if ((chByte=='\r') | (chByte=='\n') | (chByte=='\0')) // ����� ������
    {
      *(strRxBuf+iRxCounter+1)=0;
      ParsCommand();                      // ����� �������
      iRxCounter=0;
    }
  else
    {
        iRxCounter++;
        if (iRxCounter==(MAX_HACK_RX_BUF_SIZE-1)) iRxCounter=0;  // ���� �� �������������
    }
}


void Lock_t::ParsCommand(void)
{
  char *pchPrefix, *pchPostfix, *pch;
  pchPrefix = strstr (strRxBuf,HACK_COMMAND_PREFIX);
  pchPostfix = strstr (strRxBuf,HACK_COMMAND_POSTFIX);
  if (pchPrefix==NULL) return;
  if (pchPostfix==NULL) return;
  uint8_t iCommandLen=pchPostfix-pchPrefix;
  if (iCommandLen>0)
    {
      strncpy(strCommand,pchPrefix+HACK_COMMAND_PREFIX_LEN,iCommandLen);
      strCommand[iCommandLen]='\0';
      bNewCommandFlag=true;
      iNewCommandCode=HACK_COMMAND_CODE_BLANK;
      //UART_PrintString(strCommand);
      pch=strstr(strCommand,HACK_COMMAND_TEST);
      //UART_PrintString(pch);
      if (pch==strCommand) iNewCommandCode=HACK_COMMAND_CODE_TEST;
    }
}

/*
 * ������� ������ ����� � ������ ������
 * ��������� �������, ��������� ��������
 */
void Lock_t::HackedTask()
{
  if (bNewCommandFlag==false) return; // ��� ����� ������
  bNewCommandFlag=false;

  switch (iNewCommandCode)
    {
      case HACK_COMMAND_CODE_TEST:
        UART_PrintString("get HACK_COMMAND_TEST \r");
        break;
    }
  iNewCommandCode=HACK_COMMAND_CODE_BLANK;
 }

/*****  UsbRecData *******************/
/* ���������� �����, ��������� ���������� �����
   �������, ����������� �� USB */
/*************************************/
//void Lock_t::UsbRecData(uint8_t* pData, uint8_t iSize)
//{
//  if (pData==NULL) return;
//  uint8_t i=0;
//  while (i<iSize)
//    {
//     if (chUsbRxCounter==USB_RX_BUF_SIZE) return; // ����� ����� �� ������������
//     chUsbRxBuf[chUsbRxCounter]=*pData;
//     pData++;
//     chUsbRxCounter++;
//     i++;
//    }
//  return;
//}



void Lock_t::ReadSettingsFromSD()
{
 // �������� ������ ������
  if (ParamIsExists("PASSWORD", "PASSLENGTH","lock.ini"))
    {
      chPasswordLength = ReadInt32("PASSWORD", "PASSLENGTH","lock.ini");
      if (chPasswordLength>MAX_PASS_LEN)  chPasswordLength=MAX_PASS_LEN;
    }
  else chPasswordLength=4;// �� ����� MAX_PASS_LEN

// �������� ������
  if (ParamIsExists("PASSWORD", "PASS", "lock.ini"))
    {
      ReadString("PASSWORD", "PASS", chPassword, chPasswordLength , "lock.ini");
    }
  else
    {
      uint16_t i=0;
      while (i<MAX_PASS_LEN)
        {
          chPassword[i]='0'; // �� ��������� 4 ����
          i++;
        }
    }
   chPassword[chPasswordLength]=0; // ����� ������

   // �������� ������������ ���������� ���������� ������
   if (ParamIsExists("SECURITY", "MAXERROR", "lock.ini"))
     {
       chMaxCodeError = ReadInt32("SECURITY", "MAXERROR","lock.ini");
     }
   else  chMaxCodeError=5; // �� ���������

   // �������� �����, ������� ����� ����� ������
   if (ParamIsExists("SECURITY", "OPEN_TIME", "lock.ini"))
     {
       wTimeToOpen = ReadInt32("SECURITY", "OPEN_TIME","lock.ini");
     }
   else  wTimeToOpen=5000; // �� ���������
   // �������� �����, �� ������� ����� ����� �������������
   if (ParamIsExists("SECURITY", "BLOCK_TIME", "lock.ini"))
     {
       wTimeToBlock = ReadInt32("SECURITY", "BLOCK_TIME","lock.ini");
     }
   else  wTimeToBlock=20000; // �� ��������� 10000=�������� 15 ���
}
