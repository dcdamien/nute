#pragma once
#ifndef _MED_
	#error _MED_
#endif

typedef enum _EXPLOSION_EFFECT {
	BlastWave = 0,
	FireCloud = 1,
	Radiation = 2,
	MaxExplosionEffect = 3
} EXPLOSION_EFFECT;

typedef enum _DAMAGE_SEVERITY {
	RandomSelect = -3,
	Death = -2,
	None = -1,
	Graze = 0,				//��������
	Light = 1,				//���������
	Insidious = 2,			//��������
	Serious = 3,			//�������
	Critical =4,			//�����������
	MaxDamageSeverity = 5
} DAMAGE_SEVERITY;

extern const DAMAGE_SEVERITY	RandomSelectPerTenPercent[10];
extern const char* ExplosionDesc[MaxExplosionEffect][MaxDamageSeverity];

//CURE ids:
typedef enum _CURE_ID {
	UnknownCure = -1,
	Analgetic = 0,			//"����� �������������� - ����������" 
	Antispasmodic = 1,		//"�����������"
	Pyretic = 2,			//"��������������"
	Aspirator =3,			//"���������"
	CoagulationFactor =4,	//"������ �������������� ����� - ����������"
	SyntheticBlood =5,		//"������������� �����"
	Leatherette =6,			//"������������� ����"
	Myorelaxant =7,			//"������������"
	VisceraNanoPack =8,		//"��� ������������ ��� ���������� ������� => ������� ��������� ������"
//	RespiratoryNanoPack,	//"��� ����������� ������������"
//more
	Anesthetics =9,			//"������� ������"		?
	Antibiotic =10,			//"����������"			���. �����
	Absorber =11,			//"���������"			���. �����
	PlasterNanoPack =12,	//"��������"			���. �����
	NanoExoFrame =13,		//"��������������"		1-2 �����������. �������
	MagicCure =14,			//"��������� ��������"	����������
	MaxCureId = 15
} CURE_ID;

extern const char* CureNames[];