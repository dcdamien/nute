process BreathStop

//UNUSED
typedef enum _SYMPTOM {
    //�������� (�������)
    Seizure = 1,
    //������ �������� �������� (�������)
    HandShake = 3,
 } SYMPTOM;

//UNUSED
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

/*
typedef struct _CURE_SIDE_EFFECT {
	bool AntispasmodicBlockSudorogi; +Myorelaxant
	int PyrecticTemperatureDecrease; //(���������) ������� �������� � �����, ����� ������� ������.
	bool AntibioticIncreaseToxication;	//FUCK each tick remove NecroPoint and add some Toxins
	bool NanoExoFrame;
} CURE_SIDE_EFFECT;
*/

Perception depend on Temperature
				big PyrecticTemperatureDecrease => decrease pressure
					//temperature-=; pulse-; pressure-;					//15 min
					//temperature--=; pulse--; pressure--; tremorOn
				//(���������) ������� �������� � �����, ����� ������� ������.

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

Necropoints?
//when category increases we need to process trauma
//TRAUMAS:
//	common => additional necropoints			(for thermal & radiation)
//	common TROMB => just as if new shot/blow	(for rupture & blow)
//	inner bloodloss => peritonit				(for any)
//	bullet or bonebreak	=> fragment				(for rupture & blow)
// +++ tortures?

//pressure can be lower vessels are squezed (in case of bleeding) + side effects
//high temperature in case of disease/fragment (����������)

//traumas - needed for ��������
//	FRAGMENT (bullet from shot or bonebreak)
//	TROMB?
//	INTERNAL BLEEDING
//	PERITONIT
//	������ �������� ��� ��. ������ ������ (���� � ���������� �������), ������ ������ (����) � ������� ������� �������.
