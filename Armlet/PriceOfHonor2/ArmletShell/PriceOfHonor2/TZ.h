Blood-Toxins should be >0
also there is BloodRegeneration and ToxicDecrising //on some if

				if (CureActions[Analgetic].IsUsing)
					if (Body.HaveInsidiousDamageSeverity) Body.Hallucination = true;
				//Thermal or Radiation - don't use PainReduction 1

				if (CureActions[Aspirator].IsUsing)
					//can breath

				Perception depend on Temperature

				big PyrecticTemperatureDecrease => decrease pressure
					//temperature-=; pulse-; pressure-;					//15 min
					//temperature--=; pulse--; pressure--; tremorOn
				//(���������) ������� �������� � �����, ����� ������� ������.

�������� �������� ��������
[04.09.2013 1:19:56] aleksko_sw: ��������� ��������
[04.09.2013 1:20:05] ����� ��������: ��
[04.09.2013 1:20:21] aleksko_sw: ������� ������ �������� ������ �� ��������

pain4 - unstoppable by cures
pain5 - pain shock
pain6 - uncons

show bleeding level

//17 symptoms & feelins

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

/*
������������ ���������������, �� ����� �������������� �������������, 
������������ �������� ������������, ��������, �������� ����� �����������.

� ������������� ��������, ������������ ��������� ��� ��������, ������������ ����� 
�� ���� �����������, ������ ������ ������, ������� � ������ (����� ���������, ����������� 
															 ��� ������� ������ � ��������� ���������).

������� ������������ (�������)
*/

�������� ��������. �� ���� ��������� ������� ������ �����, ������ � �������� ������� ��������.
���������� (120/80 - ��� ������ �����)
���������� (90/60 - ��������� ������ �����)
������ ���������� (75/50 - ����������� ������ �����)
��� (60/40 - ������������ ���������� �����)

�����������
���������� (36.6 0 ��� �������� ��������� ��������)
���������� (37-40 ������� ���������� � ���������� ������� ��� ������� ���������� �������� (�������)).
���������� ���������� (40-42 ������� ��� �����)

������� ������������. ������� ������������ ��������������� � ������� ��������� ������. 
���������� ������������ ����� ������� �� ���������������.
������ (1)
�������(2)
������� (3)

�����
����������� (40-59 - ������ ���������� ��������� �����������)
���������� (60-80)
���������� (81-150 - ������� ������������)

//when category increases we need to process trauma
//TRAUMAS:
//	common => additional necropoints			(for thermal & radiation)
//	common TROMB => just as if new shot/blow	(for rupture & blow)
//	inner bloodloss => peritonit				(for any)
//	bullet or bonebreak	=> fragment				(for rupture & blow)
// +++ tortures?

/*
Cough
Weakness
LimbParalyze
*/

//priority for symptoms

//pressure can be lower vessels are squezed (in case of bleeding) + side effects
//high temperature in case of disease/fragment (����������)

//symptoms - to roleplay!!
//	����, ���������� �������������, �������� � ��������������, �������, ��������, ��� ��������, 
//	���� �������/��������, ������ ��� ���������� �����������, �������, ������� ������-���� ��������

//feelings & diagnostics (take partially from symptoms)
//	�������� � ����� ������� ��������� (���� ����� ��� ������������)
//	�������, �������� � ������� ������������
//	���� � ����� ������� �����, ��� ���-�� �� ���
//	���. (� ��������...)

//traumas - needed for ��������
//	FRAGMENT (bullet from shot or bonebreak)
//	TROMB?
//	INTERNAL BLEEDING
//	PERITONIT
//	������ �������� ��� ��. ������ ������ (���� � ���������� �������), ������ ������ (����) � ������� ������� �������.

NecroPoint Reason
or Traumas have NecroPoints that initiates categorizing

//TRAUMAS