#include "ArmletApi.h"
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
		"������������",					//med		//inst/15 min
		"������� ��������� ������",		//med		//inst with delay
		"������� ������",				//med		//15 min
		"����������",					//common	//inst with delay
		"���������",					//med		//15min/inst/inst with delay
		"��������",						//med		//inst
		"��������������",				//med		//inst
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

	CURE_ACTION CureAction[MaxCureId];
	int TortureSecondUsage[MaxTortureId];

	void InitCureActions()
	{
		for (int i=0; i<MaxCureId; i++) {
			CureAction[i].RemainingTicks = 0;
			CureAction[i].IsUsing = false;
		}
		for (int i=0; i<MaxTortureId; i++) {
			TortureSecondUsage[i] = 0;
		}
	}

	void ProcessCureUsage(CURE_ID cure_id, bool bStarting)
	{
		CureAction[cure_id].IsUsing = bStarting;
		CureAction[cure_id].RemainingTicks = bStarting ? 15 : 0; //minutes
		if (bStarting) 
			CureAction[cure_id].CumulativeValue += 1;
		else {
			if (CureAction[cure_id].CumulativeValue != 0)
				CureAction[cure_id].CumulativeValue -= 1;
		}

		switch (cure_id) {
			case Analgetic:
				//����� ��������������
				//������� ������ � ��������� ����. 
				//�� ��������� �� ����� � ������������ ���������.
				//������� - ����� �������� ������������.
				break;
			case Antispasmodic:
				//�����������
				//���������� �������� � ����� �����������.
				//���� ��������� ��� ���� �������� => �� �������� ����� ��� => ��������� ����� �������������
				if (bStarting)
					if (Body.Symptom[BoxerPose]) IncreaseThermal();
				break;
			case Pyretic:
				//��������������
				//�������� ����������� �������� (�����������)
				//(���������) ������� �������� � �����, ����� ������� ������.
				break;
			case Aspirator:
				//���������
				//��������� ������� �������� (��� ����� �������� �������������� �������)
				break;
			case CoagulationFactor:
				//����������
				//������������� ������������, ��� �������, ��� � ��������. �������� �������� �������.
				if (bStarting) {
					IncreaseBloodCapacity(
						5*(Body.RegenerationLevel-1),false); //leave same ToxinsCapacity
				}
				break;
			case SyntheticBlood:
				//������������� �����
				//������ ���������� ����������� ��������. ������� - �������� ����������� (�����������).
				if (bStarting) { //inst
					IncreaseBloodCapacity(
						20+10*Body.RegenerationLevel,true); //reduce ToxinsCapacity by value
					StopRupturesAndBlows();
				}
				break;
			case Leatherette:
				//������������� ����
				//��������������� ������������ ������ ������� - ����� �����. 
				//�� ����������� � ���������, ����������� � ������ ������ � ����� ���������. 
				//������� - �������� ��������� �������������� ������ �����.
				CureAction[cure_id].IsUsing = false;
				CureAction[cure_id].RemainingTicks = 0; //inst
				if (Body.Symptom[BoxerPose]) 
					IncreaseThermal();
				else 
					DecreaseThermal();
				DecreaseBloodCapacity(25,true);
				break;
			case Myorelaxant:
				//������������
				//���������� ��������, ����� �����������, ��������� ����� ���������. 
				//�������� �������� �������.
				if (bStarting) { //inst effect
					if ((Body.HasSerious)||(Body.HasCritical))
						Body.Symptom[BreathStop] = true;
				}
				break;
			case VisceraNanoPack:
				//������� ��������� ������
				//���������� ����� � ����� ����������� ��������, ��������� ���������������� 
				//���������� �����������. ������� - �������� �����������.
				if (!bStarting) {//inst delay
					DecreaseNecropoints(VisceraNanoPack);
					if (!Body.Symptom[BoxerPose])
						DecreaseThermal();
					DecreaseRadiation();
					Body.Symptom[LimbParalyze] = false;
				}
				break;
			case Anesthetics:
				//������� ������
				//������� ��������������, ��������� ����� ������ ������� ������� 
				//(� ��� �����, ������� ����������� �����). ������� - ��������� ������� �� �������� ��������.
				break;
			case Antibiotic:
				//����������
				//����� �������������� ��������. ���������� ����� �������������. 
				//������� - ����������� ����� ������������.
				if (!bStarting) {//inst delay effect
					DecreaseNecropoints(Antibiotic);
				}
				break;
			case Absorber:
				//���������
				//�������� ������������, ������������ ��������� �������� �� ���������.
				//������� - �������� �������� ��������.
				DecreaseToxinsCapacity(25); //inst and delay inst effect
				break;
			case PlasterNanoPack:
				//��������
				//���������� ��������, ������������ � ���������� ����������� ������ � 
				//���������� �������, � ��� ����� ���������� �/��� ������� ��������� ���� (�������). 
				//������� - �������� �������� ��������.
				DecreaseNecropoints(PlasterNanoPack); //inst/inst with delay
				break;
			case NanoExoFrame:
				//��������������
				//��������� � ������ ������������� ������������ � ����������� �������� �� ������� 
				//� ������� ��������� ������� �����������. ��� ���� �������� ����������� ����������� ��������������. 
				//������������ ����������� �� ������ ������������� � �����.
				CureAction[cure_id].RemainingTicks = 0; //inst
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
				_medOnExplosion(100,2);
				break;
			case CrumblingTorture:	//"����� ������������� ����������"
				{
					int Target = ArmletApi::GetRandom(RightLegTarget);
					Body.Symptom[LimbParalyze] = true;
					ApplyWound(Target,Serious,&Body.Part[Target][Blow]);
				}
				break;
			case EyeSqueezingTorture://"����� �������������� �����"
				ApplyWound(HeadTarget,Serious,&Body.Part[HeadTarget][Blow]);
				break;
			case SuffocationTorture://"����� �������"
				if (bNonFirstUsage)
					Body.Symptom[BreathStop] = true;
				break;
			case PoisonTorture:		//"���� ������������ ���"
				Body.Symptom[DeathTrauma] = true;
				break;
			case DrowingTorture:	//"����� ����������"
				if (bNonFirstUsage)
					Body.Symptom[BreathStop] = true;
				break;
			case FireTorture:		//"����� �����"
				_medOnExplosion(100,2);
				break;
			default:
				break;
		}
	}

} //namespace
