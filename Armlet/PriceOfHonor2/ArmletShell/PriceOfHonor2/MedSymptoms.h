#pragma once
#ifndef _MED_
	#error _MED_
#endif

typedef enum _SYMPTOM {
	NoSymptom = -1,
    //���� 1
    Pain1 = 0,
    //���� 2 (�������)
    Pain2 = 1,
    //���� 3 (�������)
    Pain3 = 2,
    //���� 4 (�������)
    Pain4 = 3,
    //������� ���
    PainShock = 4,
    //���������� ������������ (�������)
    Hallucination = 5,
    //�������
    Funny = 6,
    //�������� (�������)
    Seizure = 7,
    //��� �������� (�������)
    Unconciuous = 8,
    //��������������
    HeadSpin = 9,
    //���� ������� (�������)
    BoxerPose = 10,
    //��������� ������� (�������)
    BreathStop = 11,
    //�����
    Shake = 12,
    //���������� ��������
    ConentrationLoss = 13,
    //������ �������� �������� (�������)
    HandShake = 14,
    //������� ���������� (�������)
    LimbParalyze = 15,
    //����� ��������
    GeneralWeak = 16,
    //������ (�������)
    DeathTrauma = 17,
    //last
    MaxSymptom = 18,
} SYMPTOM;

extern const char* SymptomEffects[MaxSymptom];