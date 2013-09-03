#pragma once
#ifndef _MED_
	#error _MED_
#endif

typedef enum _SYMPTOM {
	NoSymptom = -1,
    //���� 1
    Pain1 = 0,
    //���� 2
    Pain2 = 1,
    //���� 3
    Pain3 = 2,
    //���� 4
    Pain4 = 3,
    //������� ���
    PainShock = 4,
    //�������
    HalfHeadAke = 5,
    //���������� ������������ 
    Hallucination = 6,
    //�������
    Funny = 7,
    //������ ������
    CoughLight = 8,
    //������ �������
    CoughStrong = 9,
    //�������� ������
    SeizureLight = 10,
    //�������� �������
    SeizureStrong = 11,
    //��� ��������
    Unconciuous = 12,
    //��������������
    HeadSpin = 13,
    //����
    Delusions = 14,
    //���� �������
    BoxerPose = 15,
    //��������� �������
    PreathStop = 16,
    //�����
    Shake = 17,
    //������������
    Bloodloss = 18,
    //�������� �������
    ConcinuousMess = 19,
    //���������� ��������
    ConentrationLoss = 20,
    //������ �������� ��������
    HandShake = 21,
    //�������� ��� 1
    HandWeak1 = 22,
    //�������� ��� 2
    HandWeak2 = 23,
    //�������� ��� 1
    LegWeak1 = 24,
    //�������� ��� 2
    LegWeak2 = 25,
    //������� ���������� 
    LimbParalyze = 26,
    //���� ���e���� �����
    BoneBreak = 27,
    //���� ������� �����
    BoneCrack = 28,
    //���� ������� ����� ��� ���� (�������� ����������� ��������)   
    BonePartPain = 29,
    //����� ����
    SharpPain = 30,
    //��������� ���� � ������� ������
    PulsePain = 31,
    //������
    HardBreathe = 32,
    //������ �������
    FunnyLight = 33,
    //������� �������
    FunnyStrong = 34,
    //����� ������ 
    BlodThroat = 35,
    //����� ������ � �����
    BloodPuke = 36,
    //������ � ����� (������)
    Puke = 37,
    //������� ����� 1 (�����-������)
    BackPain1 = 38,
    //������ ����� 2 (�����)
    BackPain2 = 39,
    //�����������/������� �������
    TorsoParalyze = 40,
    //�����������/������� ���
    NeckParalyze = 41,
    //���
    ItchLight = 42,
    //������� 
    ItchStrong = 43,
    //����� ������
    FireLight = 44,
    //����� �������
    FireHard1 = 45,
    //�������� ������� (����� 3)
    FireHard2 = 46,
    //������� ������������ 
    BloodLossStrong1 = 47,
    //�������� ����������� ������������ � ������� (��������� �������� � ������, �����, ������)
    BloodLossInner = 48,
    //������� ������� (������� ��� ��������)
    Seizure = 49,
    //������� ������� (������� ��� ��������) 
    Spasm = 50,
    //����� ��������
    GeneralWeak = 51,
    //������� �������� (�������)
    Faint = 52,
    //�������� �� ������ ������ �����
    BloodLossLight = 53,
    //�������� �� ������� ������ ����� 
    BloodLossMed = 54,
    //�������� �� ������� ������ �����
    BloodLossStrong = 55,
    //�������� �� ����� ������� ������ �����
    BloodLossCritical = 56,
    //����������� ���������
    OxygenStarve1 = 57,
    //����� ���������� ��������� 
    Toxication = 58,
    //������� (�������) 
    Insult = 59,
    //������� (�������)
    Infarct = 60,
    //����������� ������������
    SlowHeartBite = 61,
    //��������� � ������ = ������ �������
    HalfHeadAke2 = 62,
    //����������� ���������� ����� (�������)
    HeadShake1 = 63,
    //����������� ���������� ����� (��������)
    HeadShake2 = 64,
    //����� ������ *������) 
    LiverFail = 65,
    //����� �����
    ButtonFail = 66,
    //�������� ����
    Hot = 67,
    //�������� ������ (�����)
    Cold = 68,
    //����� (���� ���� - �������� � ��������)
    Thirst = 69,
    //��������� (�������)
    Fever = 70,
    //��������� ���� / ����������
    FeveredWound = 71,
    //���������� ��������� 
    OxygenStarve2 = 72,
    //������������
    Intoxication = 73,
    //������
    DeathTrauma = 74,
    //last
    MaxSymptom = 75,
} SYMPTOM;

extern const char* SymptomEffects[MaxSymptom];