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
#pragma endregion
#pragma region damage_severity
//��������� �����������
typedef enum _DAMAGE_SEVERITY {
	//RandomSelect = -3,
	//Death = -2,
	None = -1,
	Graze = 0,				//��������
	Light = 1,				//���������
	Insidious = 2,			//��������
	Serious = 3,			//�������
	Critical =4,			//�����������
	MaxDamageSeverity = 5
} DAMAGE_SEVERITY;
#pragma endregion
#pragma region damage_source
//�������� �����������
typedef enum _DAMAGE_SOURCE {
	Shot = 0,			//"������������� �������"
	KnockOut = 1,		//"���������"
	Explosion = 2		//"����� � ������"
} DAMAGE_SOURCE;
#pragma endregion
#pragma region explosion_effect
//������� �������
typedef enum _EXPLOSION_EFFECT {
	ExplosionBlastWave = 0,			//"������� �����"
	ExplosionFireCloud = 1,			//"������������ ������"
	ExplosionRadDoze = 2,			//"��������"
	MaxExplosionEffect = 3
} EXPLOSION_EFFECT;
#pragma endregion
#pragma region organ
//���� �������
typedef enum _ORGAN_TYPE {
	Cover = 0,		//"��������"
	Surface = 1,	//"�������������"
	Visceral = 2,	//"����������"
	Visceral2 = 3,	//"����������"
	MaxOrganType = 4
} ORGAN_TYPE;

//������
typedef enum _BODY_ORGAN {
	Skin = 0,		//"����"
	Muscle = 1,		//"�����"
	Bone = 2,		//"�����"
	Brains = 3,		//"����"
	Lungs = 4,		//"������"
	Heart = 5,		//"������"
	SBT	= 6,		//"���"
	Liver = 7,		//"������"
	Spleen = 8,		//"���������"
	Kidney = 9,		//"�����"
} BODY_ORGAN;
#pragma endregion
#pragma region body
//����� ����
typedef enum _BODY_PART {
	Limb = 0,			//����������
	Torso = 1,			//������
	Head = 2			//������
} BODY_PART;

//��� ����������
typedef enum _LIMB_TYPE {
	LeftArm = 0,		//"����� ����"
	RightArm = 1,		//"������ ����"
	LeftLeg = 2,		//"����� ����"
	RightLeg = 3		//"������ ����"
} _LIMB_TYPE;

//"����� �������"
typedef enum _TORSO_PART {
	Chest = 0,			//"�����"
	Abdomen = 1,		//"�����"
	Back = 2			//"�����"
} TORSO_PART;
#pragma endregion
#pragma region target
//����� �����������
typedef enum _TARGET {
	UnknownTarget = -1,
		//LIMBS:
	LimbTarget = 0,
		LeftArmTarget = 0,	//"��������� � ����������, ����� ����"
		RightArmTarget = 1,	//"��������� � ����������, ������ ����"
		LeftLegTarget = 2,	//"��������� � ����������, ����� ����"
		RightLegTarget = 3,	//"��������� � ����������, ������ ����"
		//TORSO:
	TorsoTarget = 4,
		ChestTarget = 4,		//"��������� � �����"
		AbdomenTarget = 5,	//"��������� � �����"
		BackTarget = 6,		//"��������� � �����"
		//HEAD:
	HeadTarget = 7,			//"��������� � ������"
	MaxTarget = 8
} TARGET;
COMPILE_TIME_CHECK(LeftArmTarget == (LimbTarget + LeftArm));
COMPILE_TIME_CHECK(RightArmTarget == (LimbTarget + RightArm));
COMPILE_TIME_CHECK(LeftLegTarget == (LimbTarget + LeftLeg));
COMPILE_TIME_CHECK(RightLegTarget == (LimbTarget + RightLeg));
COMPILE_TIME_CHECK(ChestTarget == (TorsoTarget + Chest));
COMPILE_TIME_CHECK(AbdomenTarget == (TorsoTarget + Abdomen));
COMPILE_TIME_CHECK(BackTarget == (TorsoTarget + Back));
#pragma endregion
#pragma region damage_effect
//������������ �����������
typedef enum _DAMAGE_EFFECT {
	Rupture = 0,		//��������� �����������
	Blow = 1,			//������� �����������
	Radiation = 2,		//������������ �����������
	Thermal = 3,		//����������� �����������
	MaxDamageEffect = 4
} DAMAGE_EFFECT;
#pragma endregion

//�����������
typedef enum _REGENERATION_LEVEL {
	NoRegen = 0,
	RegenLow = 1,
	RegenMed = 2,
	RegenHigh = 3
} REGENERATION_LEVEL;

//������ ����������
typedef enum _DISFUNCTION_LEVEL {
	NoDisfn = 0,
	DisfnLow = 1,
	DisfnMed = 2,
	DisfnHigh = 3
} DISFUNCTION_LEVEL;

//����� ������/�������
typedef enum _TRAUMA_FORM {
	Hidden = 0,		//"������� �����"
	Simple = 1,		//"������� �����"
	Hard = 2,		//"������� �����"
} TRAUMA_FORM;

typedef enum _PAIN_LEVEL {
	NoPain = 0,
	PainMild = 1,
	PainAverage = 2,
	PainStrong = 3,
	PainIntense = 4,
	PainUnbearable = 5,
	PainUnconciuous = 6
} PAIN_LEVEL;
