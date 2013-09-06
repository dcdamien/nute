#include "ArmletShell.h"
#include "Med.h"

namespace medicine {

	const char* CureName[] = {			//where		//duration
		"����� ��������������",			//common	//15 min
		"�����������",					//common	//15 min
		"��������������",				//common	//15 min
		"���������",					//common	//15 min
		"����������",					//common	//inst/15 min
		"������������� �����",			//med		//inst/15 min

		"������������� ����",			//med		//inst
		"������������",					//med		//inst
		"������� ��������� ������",		//med		//inst with delay
		"������� ������",				//med		//15 min
		"����������",					//common	//inst with delay
		"���������",					//med		//inst/15min
		"��������",						//med		//inst with delay
		"��������������",				//med		//15 min
		"�������"						//MG		//inst
	};

	const char* CureEffect[] = {
		"���� ������� ����... ������ ����� ������.",
		"���� ������� ����... �������� ����� ������� � ��������.",
		"���� ������� ����... ���������� ������ �����.",
		"������ ����� ������ �����...",
		"���� ������� ����... ������� ����������.",
		"���� ������� ����... �� ���������� ������� ���.",
		"������� ��������� ������ ���� ������� �� ����� ����� �������...",
		"���� ������� ����... ��� ���� �������������, �������� ����� '������'.",
		"���� ������� ����... ���� ������ ����� �������� �������.",
		"���� ������� ����... ����� ����� ������ �� �����������.",
		"�� ����� ��������...",
		"�� ����� ��������� �����, �������� �������...",
		"���� ������� ����... ���� ������ ����� ������ ���������� � ����������.",
		"� ���� ���� ��������� ������ ��������. �� ���� ��������� �������. ���� �������� '����������'.",
		"���� ������� ����...�� ������� � ������������, ��� ������� ������."
	};

	COMPILE_TIME_CHECK(sizeof(CureName)/sizeof(char*)==MaxCureId);
	COMPILE_TIME_CHECK(sizeof(CureEffect)/sizeof(char*)==MaxCureId);

	const char* TortureName[] = {
		"����� �������",					//no charges
		"����� ������������� ����������",	//no charges
		"����� �������������� �����",		//no charges
		"����� �������",					//no charges
		"���� ������������ ���",			//charges
		"����� ����������",					//no charges
		"����� �����"						//no charges
	};

	const char* TortureEffect[] = {
		"�� ������� �� ���� ������ ����� ������� �����... ����� ������!",
		"���� ���� ������� � ������, ����� �����... �� ������� �������� �� ����!",
		"�������� ����, � ���� ���� ����� ������� ������... ���� ������!",
		"������ ��������� �����, �� ��������� ������� ���� � �� ������!..",
		"���� ������� ����. �� �������� � �������� ��������...",
		"���� ������� � ����, �� ���������� ������� ������� ���... ���� � ������ ��������� ����������� ����!",
		"����� ������ ���� ����� ������ �������... ����� ������!"
	};

	const char* TortureEffectNoPain[] = {
		"�� ������� �� ���� ������ ����� ������� �����... ��������� �������� ��� ��� ����������.",
		"���� ���� ������� � ������, ������ ����� ������... ��������, ��� ��� ���� �������.",
		"�������� ����, � ���� ���� ����� ������� ������... ������ ����� � ������ �����.",
		"������ ��������� �����, �� ��������� ������� ���� � �� ������!..",
		"���� ������� ����. �� �������� � ������� �� �����...",
		"���� ������� � ����, �� ���������� ������� ������� ���... ���� � ������ ��������� ����! �������� �������.",
		"����� ������ ���� ����� ������ �������... ����� ������� ������."
	};

	COMPILE_TIME_CHECK(sizeof(TortureName)/sizeof(char*)==MaxTortureId);
	COMPILE_TIME_CHECK(sizeof(TortureEffect)/sizeof(char*)==MaxTortureId);
	COMPILE_TIME_CHECK(sizeof(TortureEffectNoPain)/sizeof(char*)==MaxTortureId);

	CURE_DESC CureDesc[MaxCureId];
	TORTURE_DESC TortureDesc[MaxTortureId];

	void InitCureAndTortureDescs()
	{
		for (int i=0;i<MaxCureId;i++) {
			CureDesc[i].id = (CURE_ID)i;
			CureDesc[i].Name = CureName[i];
			CureDesc[i].Effect = CureEffect[i];
		}
		for (int i=0;i<MaxTortureId;i++) {
			TortureDesc[i].id = (TORTURE_ID)i;
			TortureDesc[i].Name = TortureName[i];
			TortureDesc[i].Effect = TortureEffect[i];
			TortureDesc[i].EffectNoPain = TortureEffectNoPain[i];
		}
	}

	CURE_ACTION CureAction [MaxCureId];
	int TortureSecondUsage[MaxTortureId];
	CURE_SIDE_EFFECT CureSideEffect;

	void InitCureActions()
	{
		for (int i=0; i<MaxCureId; i++) {
			CureAction[i].RemainingTicks = 0;
			CureAction[i].IsUsing = false;
		}
		for (int i=0; i<MaxTortureId; i++) {
			TortureSecondUsage[i] = 0;
		}
		for (int i=0; i<sizeof(CureSideEffect); i++)
			((char*)&CureSideEffect)[i] = 0;
	}

	void ProcessCureUsage(CURE_ID cure_id, bool bStarting)
	{
		CureAction[cure_id].IsUsing = bStarting;
		CureAction[cure_id].RemainingTicks = bStarting ? 15 : 0; //minutes

		switch (cure_id) {
			case Analgetic:
				//����� ��������������
				//������� ������ � ��������� ����. 
				//�� ��������� �� ����� � ������������ ���������.
				//������� - ����� �������� ������������.
				CureSideEffect.AnalgeticPainReduction = bStarting;
				break;
			case Antispasmodic:
				//�����������
				//���������� �������� � ����� �����������.
				//������� - �������� �������� ����.
				//���� ��������� ��� ���� �������� => �� �������� ����� ��� => ��������� ����� �������������
//FUCK			if (bStarting)
//						if (Body.HaveBoxerPose) IncreaseScorches();
				CureSideEffect.AntispasmodicBlockSudorogi = bStarting;
				CureSideEffect.AntispasmodicHeadPain = bStarting;
				CureSideEffect.AntispasmodicBleedingIncrease = bStarting;
				break;
			case Pyretic:
				//��������������
				//�������� ����������� ��������.
				//(���������) ������� �������� � �����, ����� ������� ������.
				if (bStarting) 
					CureSideEffect.PyrecticTemperatureDecrease += 1;
				else {
					if (CureSideEffect.PyrecticTemperatureDecrease != 0)
						CureSideEffect.PyrecticTemperatureDecrease -= 1;
				}
				break;
			case Aspirator:
				//���������
				//��������� ������� �������� (��� ����� �������� �������������� �������)
				CureSideEffect.AspiratorBreath = bStarting;
				break;
			case CoagulationFactor:
				//����������
				//������������� ������������, ��� �������, ��� � ��������. �������� �������� �������.
				CureSideEffect.CoagulationFactorBleedingBlocked = bStarting;
				if (bStarting) {
					IncreaseBloodCapacity(
						5*(Body.RegenerationLevel-1),false); //leave same ToxinsCapacity
				}
				break;
			case SyntheticBlood:
				//������������� �����
				//������ ���������� ����������� ��������. ������� - �������� �����������.
				if (bStarting) { //inst
					IncreaseBloodCapacity(
						20+10*Body.RegenerationLevel,true); //reduce ToxinsCapacity by value
				}
				if (bStarting) 
					CureSideEffect.SyntheticBloodTemperature += 1;
				else {
					if (CureSideEffect.SyntheticBloodTemperature != 0)
						CureSideEffect.SyntheticBloodTemperature -= 1;
				}
				break;
//HERE
			case Leatherette:
				//������������� ����
				//��������������� ������������ ������ ������� - ����� �����. 
				//�� ����������� � ���������, ����������� � ������ ������ � ����� ���������. 
				//������� - �������� ��������� �������������� ������ �����.
			//CureActions[cure_id].RemainingTicks = 0; //inst
			//if (bStarting)
			//		if (Body.HaveBoxerPose) In�reaseCategoryForScorches();
			//DecreaseCategoryForScorches();
			//BloodLoss(?);
				break;
			case Myorelaxant:
				//������������
				//���������� ��������, ����� �����������, ��������� ����� ���������. 
				//�������� �������� �������.
			//CureActions[cure_id].RemainingTicks = 0; //inst
			//Body.HaveBoxerPose = false;
			//CureEffects.MyorelaxantBlockSudorogi //remove sudorogi & tremor
			//if (Body.HaveSeriousDamageSeverity)
			//	Body.BreathStopped = true;
				break;
			case VisceraNanoPack:
				//������� ��������� ������
				//���������� ����� � ����� ����������� ��������, ��������� ���������������� 
				//���������� �����������. ������� - �������� �����������.
			//decrease category of Radiation/Thermal;temperature+=
			//inst delay 15
			//	if (...)
			//		BodyDecreaseCategory();
				break;
			case Anesthetics:
				//������� ������
				//������� ��������������, ��������� ����� ������ ������� ������� 
				//(� ��� �����, ������� ����������� �����). ������� - ��������� ������� �� �������� ��������.
				CureSideEffect.AnestheticsPainReduction = bStarting;
				CureSideEffect.AnestheticsPressure = bStarting;
				break;
			case Antibiotic:
				//����������
				//����� �������������� ��������. ���������� ����� �������������. 
				//������� - ����������� ����� ������������.
				CureSideEffect.AntibioticBlockNecroPoints = bStarting;
//FUCK each tick remove NecroPoint and add some Toxins
				break;
			case Absorber:
				//���������
				//�������� ������������, ������������ ��������� �������� �� ���������.
				//������� - �������� �������� ��������.
				if (bStarting) 
					CureSideEffect.AbsorberLowPressure += 1;
				else {
					if (CureSideEffect.AbsorberLowPressure != 0)
						CureSideEffect.AbsorberLowPressure -= 1;
				}
//FUCK			DecreaseToxinsCapacity(50);
				break;
			case PlasterNanoPack:
				//��������
				//���������� ��������, ������������ � ���������� ����������� ������ � 
				//���������� �������, � ��� ����� ���������� �/��� ������� ��������� ���� (�������). 
				//������� - �������� �������� ��������.
				if (bStarting) 
					CureSideEffect.PlasterNanoPackHigPressure += 1;
				else {
					if (CureSideEffect.PlasterNanoPackHigPressure != 0)
						CureSideEffect.PlasterNanoPackHigPressure -= 1;
				}
//FUCK each tick remove NecroPoint for FRAGMENT
				break;
			case NanoExoFrame:
				//��������������
				//��������� � ������ ������������� ������������ � ����������� �������� �� ������� 
				//� ������� ��������� ������� �����������. ��� ���� �������� ����������� ����������� ��������������. 
				//������������ ����������� �� ������ ������������� � �����.
				CureSideEffect.NanoExoFrame = true;
				CureAction[cure_id].RemainingTicks = 0;
				Body.RegenerationLevel = NoRegen;
				break;
			case MagicCure:
				InitBody();
				break;
			default:
				break;
		}
	}

	void ProcessTortureUsage(TORTURE_ID torture_id)
	{
		bool bNonFirstUsage = false;
		if (TortureSecondUsage[torture_id]!=0) {
			bNonFirstUsage = true;
		}
		TortureSecondUsage[torture_id] = 15;

		switch  (torture_id) {
			case ColdTorture:		//"����� �������"
				//Scorch
				break;
			case CrumblingTorture:	//"����� ������������� ����������"
				//LimbParalyze & Blow(Serious)
				break;
			case EyeSqueezingTorture://"����� �������������� �����"
				//HeadShot(Serious)
				break;
			case SuffocationTorture://"����� �������"
				//Blow(Insideous) ;BreathStop on repeat
				break;
			case PoisonTorture:		//"���� ������������ ���"
				//Death
				break;
			case DrowingTorture:	//"����� ����������"
				//Blow(Insideous); BreathStop on repeat
				break;
			case FireTorture:		//"����� �����"
				//Scorh
				break;
			default:
				break;
		}
	}

} //namespace
