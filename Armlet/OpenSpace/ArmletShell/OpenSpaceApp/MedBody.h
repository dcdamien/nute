#pragma once
#ifndef _MED_
	#error _MED_
#endif

extern const char* TargetNames[MaxWoundType];

/*
typedef struct _ORGAN {
	//From damage effect
	PAIN_LEVEL PainLevel;
	DISFUNCTION_LEVEL DisfnLevel;		//D
	int Bleeding;						//B-=X, per tick		//������������
	int Toxinating;						//T+=X, per tick		//����������

	//From organ initializer
	int DefOxygenUse;					//O-=X, per tick		//����������
	int DefDetox;						//T-=X, per tick		//������������
	int DefBloodRegen;					//B+=X, per tick		//����������� �����
	int DefRestore;						//P-=X, per tick		//��������������

	//Local toxin capacity
	int PoisonCapacity;					//P

	//Traumas[]
	int TraumaPainLevel;
	bool OrganSymptoms[MaxSymptom];
} ORGAN, *PORGAN;
*/

typedef struct _PART {
	//From damage effect
	PAIN_LEVEL PainLevel;
	DAMAGE_SEVERITY CurrSeverity;
	int RemainingTicks;
	DISFUNCTION_LEVEL DisfnLevel;		//D
	int Bleeding;						//B-=X, per tick		//������������
} PART, *PPART;

typedef struct _BODY {
	REGENERATION_LEVEL RegenerationLevel;	//R
	int BloodCapacity;						//B
	int ToxinsCapacity;						//T
	//int ToxinsDelivered;					//TT = min(B/2,T)
	//int OxygenDelivered;					//OO = min(B-TT,O)
	//int CO2_Delivered;						//CC
	int PainReduction;
	//bool BodySymptoms[MaxSymptom];
	//Factors
	int BleedingFactor;
	//int BloodRegenFactor;
	//int ToxinatingFactor;
	PART parts[MaxTarget];
} BODY, *PBODY; //TODO MOVE

//Target by severity/damage
//	int BloodLoss;						//B-=X, once			//�����������
//	int Toxins;							//T-=X, once			//������	

extern BODY Body;

void InitBody();
void BodyCycle(char* buf, int len);
void BodyDecreaseCategory();
void GatherDescs(char* buf, int len);
