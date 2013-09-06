#pragma once
#ifndef _MED_
	#error _MED_
#endif

//both rpg symptom and diag feeling
typedef enum _PAIN {
	NoPain = 0,
    //���� 1
    Pain1 = 1,
    //���� 2 (�������)
    Pain2 = 2,
    //���� 3 (�������)
    Pain3 = 3,
    //���� 4 (�������)
    Pain4 = 4,
    //������� ���
    PainShock = 5,
	//��� ��������
	PainUncon = 6,
	MaxPain = 7
} PAIN;

typedef enum _FEELING {
    //�������
    Funny = 0,
    //��������������
    HeadSpin = 1,
    //�����
    Shake = 2,
    //����� ��������
    GeneralWeak = 3,
    //���������� ��������
    ConentrationLoss = 4,
	MaxFeeling = 5
} FEELING;

typedef enum _SYMPTOM {
    //���������� ������������ (�������)
    Hallucination = 0,
    //�������� (�������)
    Seizure = 1,
    //���� ������� (�������)
    BoxerPose = 2,
    //������ �������� �������� (�������)
    HandShake = 3,
    //������� ���������� (�������)
    LimbParalyze = 4,
    //��������� ������� (�������)
    BreathStop = 5,
    //��� �������� (�������)
    Unconciuous = 6,
    //������ (�������)
    DeathTrauma = 7,
    //last
    MaxSymptom = 8
} SYMPTOM;

extern const char* PainDesc[MaxPain];
extern const char* BleedingDesc[4];
extern const char* FeelingDesc[MaxFeeling];
extern const char* SymptomDesc[MaxSymptom];