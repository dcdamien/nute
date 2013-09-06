/*
typedef struct _CURE_SIDE_EFFECT {
	bool AntispasmodicBlockSudorogi; +Myorelaxant
	bool AntispasmodicHeadPain;
	bool AntispasmodicBleedingIncrease;
	int PyrecticTemperatureDecrease; //(���������) ������� �������� � �����, ����� ������� ������.
	int VisceraNanoPackTemperatureIncrease;
	bool AspiratorBreath; 
	bool CoagulationFactorBleedingBlocked;
	int SyntheticBloodTemperature;
	bool AntibioticIncreaseToxication;	//FUCK each tick remove NecroPoint and add some Toxins
	int AbsorberLowPressure; (cumulative)
	bool AnestheticsPressure;

	int PlasterNanoPackHigPressure;
	bool NanoExoFrame;
} CURE_SIDE_EFFECT;
*/

typedef struct _WOUND_DESC {
	unsigned short target;			//wound subtype
	unsigned short severity;		//wound severity
	DAMAGE_EFFECT de;				//damage effect 
	int PainLevel;				//pain from wound
	int BloodLoss;				//instant bloodloss
	int Bleeding;				//bloodloos per tick
	int ToxinsAdd;				//instant intoxication
	int Toxinating;				//intoxication per tick
	int NecroPoints;			//Amount of "DEAD" flesh
	const char* message;
} WOUND_DESC;

pain4 - unstoppable by cures
pain5 - pain shock
pain6 - uncons

show bleeding level

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
	NoFeeling = -1,
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
	NoSymptom = -1,
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

Blood-Toxins should be >0
also there is BloodRegeneration and ToxicDecrising //on some if


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
//	����, ���������� �������������,  ��� ��������, 
//	���� �������/��������, ������ ��� ���������� �����������, �������, ������� ������-���� ��������

//	�������, �������� � ������� ������������
//	��������, �������������� � ����� ������� ��������� (���� ����� ��� ������������)

//traumas - needed for ��������
//	FRAGMENT (bullet from shot or bonebreak)
//	TROMB?
//	INTERNAL BLEEDING
//	PERITONIT
//	������ �������� ��� ��. ������ ������ (���� � ���������� �������), ������ ������ (����) � ������� ������� �������.

NecroPoint Reason
or Traumas have NecroPoints that initiates categorizing

//TRAUMAS