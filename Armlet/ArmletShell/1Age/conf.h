#pragma once

#include "Osanve.h"

// ��������� ����� ������������ - ������� ���������
namespace config {
#define MAX_ARMLET 255
	struct config {
		ubyte_t userId; // �����
		ubyte_t groupId; // ������ �������
		ubyte_t maxForce; // ���� ����
		bool evil; // ������� ����
		ubyte_t fph; // �������� �������������� ���� (force per hour)
		char name[16]; // ��� ���������
		char fname[16]; //������ ��� ���������
		sword_t rights; // ����� �������� (��. AL_CAN � Osanve.h)
	};

/// ���������� ��������� ������ �� ID ����� �� �������
/// false - ������ (�������� ID)
bool InitPlayer(struct player* p);
}

using namespace config;

extern struct config CONF[MAX_ARMLET];
