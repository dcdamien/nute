#pragma once
#ifndef _MED_
	#error _MED_
#endif

typedef enum _REGENERATION_LEVEL {
} REGENERATION_LEVEL;

typedef struct _BODY {
	//RegenerationLevel


	unsigned char PainReduction;

	unsigned char BloodLevel;
	unsigned char RegenerationLevel;
	//unsigned char Wounds[MAX_DAMAGE_FACTOR]; //store wounds

	//Symptoms:

} BODY, *PBODY; //TODO MOVE

extern BODY Body;

#if 0
/*
0 "���"
1 "���� 1"
2 "���� 2"
3 "���� 3"
4 "������� ����"
5 "��������� ����"
6 "�������"
7 "���������� ������������"
8 "���"
9 "�������"
10 "�����"
11 "������"
12 "������� ������"
13 "������ ��������"
14 "������� ��������"
15 "������ ����"
16 "������� ����"
17 "������ �������� ��������"
18 "���� �������"
19 "������� �� ����� ������"
20 "���������� ��������"
21 "�������� �������"
22 "��� ��������"
23 "����"
24 "��������������"
*/

#define CURE_TICK	60000		//1 minute in msecs



//�������
//����������
#define LEFT_ARM	0	//"����� ����"
#define RIGHT_ARM	1	//"������ ����"
#define LEFT_LEG	2	//"����� ����"
#define RIGHT_LEG	3	//"������ ����"
//������
#define	HEAD		4	//"� ������"
#define	TORSO_1		5	//"� �����"
#define	TORSO_2		6	//"� �����"
//������
#define	NOCKOUT		7	//"������"
//�����
#define EXPLOSION_1	8	//"������� ������� ������"
#define EXPLOSION_2	9	//"������� ���������"
#define EXPLOSION_3	10	//"����"

//���� �������			//random
#define DAMAGE_0	0
#define DAMAGE_1	1	//"��������" 40%
#define DAMAGE_2	2	//"��������� �������" 30%
#define DAMAGE_3	3	//�������� ������� (20%),
#define DAMAGE_4	4	//��������� ������� (10%),
#define DAMAGE_5	5	//������������ ������� (0%)
#define DAMAGE_6	6	//"������"

DAMAGE_BETTER[] = {0,-1,-2,-1,-2,-2}
DAMAGE_WORSE[] =  {!,+2,+1,+2,+1, 0} //random
//Same hit into same body part = DAMAGE_WORSE

damage_t
{
	char* first_message;
}
��������� ��������� (������������, ����� ������� ������ ���������)	
��������� ��������	
���������� �������� (��� � ������)	
���������� ��������� (� ������� ������ ������� ����. 
					  ���� ������� ������� ������������� >= ������ ����, ��������� �� ������������)	
��������� ������	
��� �������	
��� ���������










typedef enum _regeneration_level_t {
	reg_no = 0,
	reg_norm = 1,
	reg_high = 2
} regeneration_level_t;

/*
"161..200 ��� ���������
121..160 ������� ��������, �������� ������
81..120 �������� ��������, ������ �������
41..80 ������ ������� ��������, �� ������ ������
1..40 �������� ��������, ������������� 3
0 ����"
*/

typedef struct _med_state_t {
	regeneration_level_t regeneration_level;	//can be set from server
												//config
	uint8_t blood_level;						//0..200
	uint8_t blood_loss;							//0..10
} med_state_t

/*
������������ �������	��/���	������	������� �� ���������
�������������	0..2	��������������� ������ ���������	������� �� ���������
��� ���������	������	���������	
��������� ������ ��������	��/���	������� �� ���� �������� � ������	������� �� ���������
�����	��/���	����� ����� ����	������� �� ���������
��������	��/���	�� ���� ������ ������ ��������	������� �� ���������
� ��������	��/���	�� ��� ���������	������� �� ���������
*/













namespace PriceOfHonor {

	//SYMPTOMS
	typedef enum _SYMPTOMS {
		NO_SYMPTOM,
		PAIN_1,
		PAIN_2,
		PAIN_3,
		PAIN_4,
		PAIN_5,
	} SYMPTOMS;
};

typedef struct _SYMPTOM_DESC {
	char* SymptomName;
	char* BriefDesc;
	char* DescForPatient;
} SYMPTOM_DESC;
#endif