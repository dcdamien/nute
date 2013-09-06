#pragma once
#ifndef _MED_
	#error _MED_
#endif

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
#pragma endregion
#pragma region damage_effect
//������������ �����������
typedef enum _DAMAGE_EFFECT {
	RuptureLimb = 0,	//��������� ����������� � ����������
	Rupture = 1,		//��������� �����������
	Blow = 2,			//������� �����������
	Thermal = 3,		//����������� �����������
	Radiation = 4,		//������������ �����������
	MaxDamageEffect = 5
} DAMAGE_EFFECT;
#pragma endregion

//�����������
typedef enum _REGENERATION_LEVEL {
	NoRegen = 0,
	RegenLow = 1,
	RegenMed = 2,
	RegenHigh = 3
} REGENERATION_LEVEL;
