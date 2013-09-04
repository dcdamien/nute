#include "ArmletShell.h"
#include "Med.h"

namespace medicine {

	const char* CureName[] = {			//where		//purpose-contradictions-side effects				//duration
		"����� ��������������",			//common	//EffectivePain--; if (Insidious) Hallucination		//10 min
		"�����������",					//common	//blocks symptoms from group1; HeadPain++			//10 min
		"��������������",				//common	//temperature-=; no									//10 min
		"���������",					//common	//restores breath; cough on							//10 min
		"����������",					//common	//stop bleeding & BloodCapacity+=5*(R-1); no		//10 min
		"������������� �����",			//med		//BloodCapacity+=10*R; temperature+=				//inst
		"������������� ����",			//med		//Reduce NECRO; non-usable if BoxerPose				//inst
		"������������",					//med		//blocks symptoms from group1, remove BoxerPose; BloodLoss 5
																										//inst
		"������� ��������� ������",		//med		//decrease category of Radiation/Thermal;temperature+=
																										//inst delay 20
		"������� ������",				//med		//EffectivePain-=2; ?								//10 min
		"����������",					//common	//blocks inflammation; toxinadd ?					//10 min
		"���������",					//med		//detoxing											//inst
		"��������",						//med		//blocks FRAGMENT traumas
		"��������������",				//med		//?
		"�������"						//MG		//cures everything; no								//inst
	};

	const char* CureEffect[] = {
		"���� ������� ����... ������ ����� ������.",
		"���� ������� ����... �� ���������� ���������� ����������.",
		"���� ������� ����... ���������� ��������.",
		"������ ����� ������ �����...",
		"���� ������� ����... ������� ����������.",
		"���� ������� ����... �� ���������� ������� ���.",
		"������� ��������� ������ ���� ������� �� ����� ����� �������...",
		"���� ������� ����... ��� ���� �������������.",
		"���� ������� ����... ���� ������ ����� �������� �������.",
		"���� ������� ����... ����� ����� ������ �� �����������.",
		"�� ����� ��������...",
		"�� ����� ��������� �����, �������� �������...",
		"���� ������� ����... ���� ������ ����� ������ ���������� � ����������.",
		"---",
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
		"����� ������ ���� ����� ������ �������... ����� �����."
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

} //namespace
