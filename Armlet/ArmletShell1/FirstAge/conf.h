#pragma once

#include "string.h"

#define MAX_ARMLET 255
// ��������� ����� ������������ - ������� ���������
//namespace configs {

	struct config {
		unsigned char userId; // �����
		unsigned char groupId; // ������ �������
		unsigned char maxForce; // ���� ����
		bool evil; // ������� ����
		unsigned char fph; // �������� �������������� ���� (force per hour)
		char name[32]; // ��� ���������
		char fname[32]; //������ ��� ���������
		signed short rights; // ����� �������� (��. AL_CAN � Osanve.h)
		/*config() {};
		config(ubyte_t u,ubyte_t g,ubyte_t m,bool e,ubyte_t f,char* na, char* fna, sword_t r):
		   userId(u), groupId(g), maxForce(m), evil(e),fph(f), rights(r)
		   {strcpy(name,na); strcpy(fname,fna);};*/
	};



//using namespace configs;

extern struct config CONF[MAX_ARMLET];
