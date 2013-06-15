#pragma once

#define PACKET_LEN	4
#define PACKET_TYPE_ATACK	0x80
#define OSANVE_MASK 0x0F
#define CONS_MASK 0x70
#define FORCE_SIDE_GOOD 0x00
#define FORCE_SIDE_EVIL 0x10
#define FORCE_HEAL 0x08
#define GET_CONS(b) ((b&CONS_MASK)>>4)
#define IS_ATACK_PACKET(p)	(*(p+1)&PACKET_TYPE_ATACK)
#define IS_ATACKHEAL_PACKET(p)	((*(p+1)&PACKET_TYPE_ATACK)&&(*(p+1)&FORCE_HEAL))

namespace OsanveProtocol {

#pragma pack(push,1)

// ����� ������ (�����������������)
struct OSANVE_PACKET {
	unsigned char src; // ID �����������
	unsigned char flags; // ���������� ������ � ���� ���� ������
	unsigned char force; // ���� �����������
	unsigned char maxForce; // ������ ���� �����������
};

// ����� ����� (��������)
struct ATACK_PACKET {
	unsigned char src; // ID �����������
	unsigned char flags; // ���� ���� ������, ���� ������� � ��� �����������
	unsigned char dst; // ID ����������
	unsigned char atack; // ����, ��������� � ����� (����� ���� 0)
};

#pragma pack(pop)

} //namespace

using namespace OsanveProtocol;