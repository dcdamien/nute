#pragma once

#include "Osanve.h"
#include "string.h"

// ��������� ����� ������������ - ������� ���������
//namespace configs {

	struct config {
		ubyte_t userId; // �����
		ubyte_t groupId; // ������ �������
		ubyte_t maxForce; // ���� ����
		bool evil; // ������� ����
		ubyte_t fph; // �������� �������������� ���� (force per hour)
		char name[32]; // ��� ���������
		char fname[32]; //������ ��� ���������
		sword_t rights; // ����� �������� (��. AL_CAN � Osanve.h)
		/*config() {};
		config(ubyte_t u,ubyte_t g,ubyte_t m,bool e,ubyte_t f,char* na, char* fna, sword_t r):
		   userId(u), groupId(g), maxForce(m), evil(e),fph(f), rights(r)
		   {strcpy(name,na); strcpy(fname,fna);};*/
	};

/// ���������� ��������� ������ �� ID ����� �� �������
/// false - ������ (�������� ID)
bool InitPlayer(struct player* p);
//}

//using namespace configs;

extern struct config CONF[MAX_ARMLET];
