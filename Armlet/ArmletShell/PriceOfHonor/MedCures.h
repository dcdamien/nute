#pragma once
#ifndef _MED_
	#error _MED_
#endif

#pragma region cure_id
// When this list updated, update server list 
// /Armlet/Armlet3/BastiliaGate_sw/Server/HonorLogic/Pills.cs
//���������
typedef enum _CURE_ID {
	UnknownCure = -1,
	Analgetic = 0,			//"����� ��������������" 
	Antispasmodic = 1,		//"�����������"
	Pyretic = 2,			//"��������������"
	Aspirator =3,			//"���������"
	CoagulationFactor =4,	//"����������"
	SyntheticBlood =5,		//"������������� �����"
	Leatherette =6,			//"������������� ����"
	Myorelaxant =7,			//"������������"
	VisceraNanoPack =8,		//"������� ��������� ������"
	Anesthetics =9,			//"������� ������"
	Antibiotic =10,			//"����������"
	Absorber =11,			//"���������"
	PlasterNanoPack =12,	//"��������"
	NanoExoFrame =13,		//"��������������"
	MagicCure =14,			//"�������"
	MaxCureId = 15
} CURE_ID;
//�����
typedef enum _TORTURE_ID {
	UnknownTorture = -1,
	ColdTorture = 0,			//"����� �������"						//pill 20
	CrumblingTorture = 1,		//"����� ������������� ����������"		//pill 21
	EyeSqueezingTorture = 2,	//"����� �������������� �����"			//pill 22
	SuffocationTorture = 3,		//"����� �������"						//pill 23
	PoisonTorture = 4,			//"���� ������������ ���"				//pill 24
	DrowingTorture = 5,			//"����� ����������"					//pill 25
	FireTorture = 6,			//"����� �����"							//pill 26
	MaxTortureId =  7
} TORTURE_ID;
#pragma endregion

typedef struct _CURE_DESC {					
	CURE_ID id;						//cure id
	const char* Name;				//cure name
	const char* Effect;				//cure effect description
//	const char* Purpose;			//cure purpose description
//	const char* Contraindications;	//cure contraindications description
//	const char* SideEffects;		//cure side effects description
} CURE_DESC;

typedef struct _TORTURE_DESC {
	TORTURE_ID id;					//torture id
	const char* Name;				//torture name
	const char* Effect;				//torture effect description
	const char* EffectNoPain;		//torture effect description under anesthetics
} TORTURE_DESC;

extern const char* CureName[];
extern CURE_DESC CureDesc[MaxCureId];

extern const char* TortureName[];
extern TORTURE_DESC TortureDesc[MaxTortureId];

void InitCureAndTortureDescs();
