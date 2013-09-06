#include "ArmletApi.h"
#include "ArmletShell.h"
#include "Med.h"

namespace medicine {

#pragma region WoundEffects
const char* WoundEffects[MaxWoundType][MaxDamageSeverity] = {
{ //����� ����
    //��������    
    "���� ������� ����� ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    ���������
    "���� ������� ����� ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    ��������
    "���� ������� ����� ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    �������
    "���� ������� ����� ���� ��� �����. ������, ������� ���������, ����� ��� � �����.",
    //    �����������
    "���� �������� ������ � ����� ����. ����� �����! ����� ������!",
},
{ //������ ����
    //��������    
    "���� ������� ������ ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    ���������
    "���� ������� ������ ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    ��������
    "���� ������� ������ ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    �������
    "���� ������� ������ ���� ��� �����. ������, ������� ���������, ����� ��� � �����.",
    //    �����������
    "���� �������� ������ � ������ ����. ����� �����! ����� ������!",
},
{ //����� ����
    //��������    
    "���� ������� ����� ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    ���������
    "���� ������� ����� ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    ��������
    "���� ������� ����� ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    �������
    "���� ������� ����� ���� ��� �����. ������, ������� ���������, ����� ��� � �����.",
    //    �����������
    "���� �������� ������ � ����� ����. ����� �����! ����� ������!",
},
{ //������ ����
    //��������    
    "���� ������� ������ ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    ���������
    "���� ������� ������ ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    ��������
    "���� ������� ������ ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
    //    �������
    "���� ������� ������ ���� ��� �����. ������, ������� ���������, ����� ��� � �����.",
    //    �����������
    "���� �������� ������ � ������ ����. ����� �����! ����� ������!",
},

{ //������� � ������
    //��������
    "������� ����� ���� ��������, ����� �� ������.",
    //    ��������� 
    "������, ���� �����������! ���� � �����.",
    //    �������� 
	"������� ����� ���� ��������. ���� � �����.",
    //    �������
    "������, ���� �����������! ������ ���� � �����.",
    //    �����������
    "������, ���� �����������! ������ ���� � �����. ������� �����!",
},
{ //������� � �����
    //��������
    "������� ����� ���� ��������, ����� �� ������.",
    //    ��������� 
    "������, ���� �����������! ���� � ������.",
    //    �������� 
    "������� ����� ���� ��������. ���� � ������.",
    //    �������
    "������, ���� �����������! ������ ���� � ������.",
    //    �����������
    "������, ���� �����������! ������ ���� � ������. ������� �����!",
},
{ //������� � �����
    //��������
    "������� ����� ���� ��������, ����� �� ������.",
    //    ��������� 
    "������, ���� �����������! ���� � �����.",
    //    �������� 
    "������� ����� ���� ��������. ���� � �����.",
    //    �������
    "������, ���� �����������! ������ ���� � �����.",
    //    �����������
    "������, ���� �����������! ������ ���� � �����. ������� �����!",
},

{ //������� � ������
    //��������
    "������� ����� ���� ��������, ����� �� ������.",
    //    ���������
    "������, ���� �����������! � ���� ����������� ����. ������ �������������.",
    //    ��������
    "������� ����� ���� ��������, ������ �������������.",
    //    �������
    "������, ���� �������� �����������! � ���� ����������� ����. ����� ������. ����� ��������� ����� � ����� ������ �� �����. ��� ������� - ������� ���� �� ��� �����!",
    //    �����������
    "��� ����� ��������. ���� �����, ��� ������� ��������. ����� ������. ���� �� ������, ������� �� �������������.",
},
{ //����������� �������
    //��������
    "���� ����� � ���! �������!..",
    //    ���������
    "���� ����� � ���! ������ �����.",
    //    ��������
    "���� ����� � ���! ������ �����.",
    //    �������
    "���� ����� � ���! ������ ������ �����.",
    //    �����������
    "���� ����� � ���! ������ ������ �����.",
},
{ //������� ����� (����� � ������)
    //��������
    "������� ��������� ����� ������ ����, ��, ����� ��, ��� � �������.",
    //    ���������
    "���� ��� ����� ������ ��������� �����. ������, �� ���� ������.",
    //    ��������
    "���� ��� ����� ������ ��������� �����. ������, �� ���� ������.",
    //    �������
    "���� ��� ����� ������ ��������� �����. �� ����� �� ������ ������ � ����. ������, ���� ���������.",
    //    �����������
    "���� ��� ����� ������ �������������� �����. ���� ����� ������, �, �������, �� ������ �� ����.",
},
{ //���� (����� � ������)
    //��������
    "����������� ����� ������� ��������� ����. ����� �����. ������ ���� ����� ������!",
    //    ���������
    "����� ��� ����������� ����� ������� ��������� ����. �����! ������ ���� ������ ������. ������!",
    //    ��������
    "����������� ����� ������� ��������� ����. ����� ����. ������ ���� ����� ������!",
    //    �������
    "���� �������� ����������� ������ ������ �������. ������ ���� ���������� �������!",
    //    �����������
    "���� ������� ����������� ������ ������ �������. �� ������ � ���� ��������. ��� - ��� ����. ���� - ��� ��!",
},
{ //���-�� ������� ��������� ������ �� �������� (����� � ������)
    //��������
    "������� �� ������� ������� ������. �� ����� ������ ��������� ���������� �����, ������� ����� �������.",
    //    ���������
    "������� �� ������� ������� ������. �� ����� ������ ��������� ���������� �����, ������� ����� �������.",
    //    ��������
    "������� �� ������� ������� ������. �� ����� ������ ��������� ���������� �����, ������� ����� �������.",
    //    �������
    "������� �� ������� ������� ������. �� ����� ������ ��������� ���������� �����, ������� ����� �� ���������.",
    //    �����������
    "������� �� ������� ������� ������. �� ����� ������ ��������� ���������� �����, ������� ����� �� ���������.",
},
};
COMPILE_TIME_CHECK(sizeof(WoundEffects)/sizeof(char*)==MaxWoundType*MaxDamageSeverity);
#pragma endregion

const DAMAGE_SEVERITY RandomSelectPerTenPercent[10] =
{ //for random number from 0..9
	Graze, Graze, Graze, Graze,		//40% ��������
	Light, Light, Light,			//30% ���������
	Insidious, Insidious,			//20% ��������
	Serious							//10% �������
};
COMPILE_TIME_CHECK(sizeof(RandomSelectPerTenPercent)/sizeof(DAMAGE_SEVERITY)==10);

const DAMAGE_EFFECT WoundToDamageEffect[MaxWoundType] =
{ 
	RuptureLimb, RuptureLimb, RuptureLimb, RuptureLimb,	//LimbShot
	Rupture, Rupture, Rupture, Rupture,					//other shots
	Blow,												//KnockOut
	Blow, Thermal, Radiation							//Explosion
};

int sdeToPain[MaxDamageEffect][MaxDamageSeverity] = {
	{1,1,1,2,3}, //RuptureLimb
	{1,2,2,3,3}, //Rupture
	{0,1,1,2,3}, //Blow
	{1,2,1,3,4}, //Thermal
	{0,0,0,0,0}, //Radiation
};
int sdeToBloodLoss[MaxDamageEffect][MaxDamageSeverity] = {
	{1/*000*/,5/*000*/,5/*000*/,10/*000*/,30/*000*/}, //RuptureLimb
	{5/*000*/,10/*000*/,10/*000*/,30/*000*/,50/*000*/}, //Rupture
	{0/*000*/, 1/*000*/, 1/*000*/,5/*000*/,15/*000*/}, //Blow
	{0,0,0,0,0},		//Thermal
	{0,0,0,0,0},		//Radiation
};
int sdeToBleeding[MaxDamageEffect][MaxDamageSeverity] = {
	{0,1/*000*/,1/*000*/,5/*000*/,10/*000*/},	//RuptureLimb
	{0,1/*000*/,1/*000*/,5/*000*/,10/*000*/},	//Rupture
	{0,0/*000*/,1/*000*/,3/*000*/,7/*000*/},	//Blow
	{0,0,0,0,0},	//Thermal
	{0,0,0,0,0},	//Radiation
};
int sdeToToxinsAdd[MaxDamageEffect][MaxDamageSeverity] = {
	{0,0,0,0,0},	//RuptureLimb
	{0,0,0,0,0},	//Rupture
	{0,0,0,0,0},	//Blow
	{0,5,5,10,15},	//Thermal
	{5/*000*/,10/*000*/,10/*000*/,20/*000*/,30/*000*/},	//Radiation
};
int sdeToToxinating[MaxDamageEffect][MaxDamageSeverity] = {
	{0,0,0,0,0},	//RuptureLimb
	{0,0,0,0,0},	//Rupture
	{0,0,0,0,0},	//Blow
	{0,1,2,3,5},	//Thermal
	{0,1/*000*/,1/*000*/,5/*000*/,10/*000*/},	//Radiation
};
int sdeToNecroPoints[MaxDamageEffect][MaxDamageSeverity] = {
	{0,5,15,15,25},		//RuptureLimb
	{0,10,25,25,40},	//Rupture
	{0,5,10,10,15},		//Blow
	{0,20,30,45,60},	//Thermal
	{0,20,30,45,60},	//Radiation
};

WOUND_DESC WoundDescs[MaxWoundType][MaxDamageSeverity];

void InitWounds()
{
	for (int i=0;i<MaxWoundType;i++)
		for(int j=0;j<MaxDamageSeverity;j++)
	{
		WoundDescs[i][j].message = WoundEffects[i][j];

		WoundDescs[i][j].target = (TARGET)i;
		WoundDescs[i][j].severity = (DAMAGE_SEVERITY)j;
		
		DAMAGE_EFFECT de = WoundToDamageEffect[i];
		WoundDescs[i][j].de = de;

		WoundDescs[i][j].PainLevel = sdeToPain[de][j];
		WoundDescs[i][j].BloodLoss = sdeToBloodLoss[de][j];
		WoundDescs[i][j].Bleeding = sdeToBleeding[de][j];
		WoundDescs[i][j].ToxinsAdd = sdeToToxinsAdd[de][j];
		WoundDescs[i][j].Toxinating = sdeToToxinating[de][j];
		WoundDescs[i][j].NecroPoints = sdeToNecroPoints[de][j];
	}
}

DAMAGE_SEVERITY NextCategory(DAMAGE_SEVERITY curr)
{
	if (curr <= None) return None;
	if (curr == Graze) return None;
	if (curr == Light) return Graze;
	if (curr == Insidious) return Serious;
	if (curr == Serious) return Critical;
	if (curr == Critical) return Critical;
	return None;
}

DAMAGE_SEVERITY DecreaseCategory(DAMAGE_SEVERITY curr)
{
	if (curr <= None) return None;
	if (curr == Graze) return None;
	if (curr == Light) return None;
	if (curr == Insidious) return Light;
	if (curr == Serious) return Light;
	if (curr == Critical) return Serious;
	return None;
}

DAMAGE_SEVERITY IncreaseCategory(DAMAGE_SEVERITY curr)
{
	if (curr <= None) return RandomSelectPerTenPercent[ArmletApi::GetRandom(10)];
	if (curr == Graze) return Serious;
	if (curr == Light) return Serious;
	if (curr == Insidious) return Critical;
	if (curr == Serious) return Critical;
	if (curr == Critical) return Critical;
	return None;
}

void ApplyWound(int wound, int ds, PPART part, bool bIncrease)
{
	if (part->CurrSeverity == None) {
		Body.BloodCapacity -= WoundDescs[wound][ds].BloodLoss;
		Body.ToxinsCapacity += WoundDescs[wound][ds].ToxinsAdd;
		part->NecroPoints += WoundDescs[wound][ds].NecroPoints;
	}

	if (bIncrease) {
		if (part->CurrSeverity < (DAMAGE_SEVERITY)ds) {
			part->wound = wound;
			part->CurrSeverity = (DAMAGE_SEVERITY)ds;			
		}
		part->Bleeding += WoundDescs[wound][ds].Bleeding;
		part->Toxinating += WoundDescs[wound][ds].Toxinating;
		part->NecroPoints += WoundDescs[wound][ds].NecroPoints;

		int pl = WoundDescs[wound][ds].PainLevel;
		if (part->PainLevel < pl)
			part->PainLevel = pl;
	} else {
		part->wound = wound;
		part->CurrSeverity = (DAMAGE_SEVERITY)ds;			
		DAMAGE_EFFECT de = WoundDescs[wound][ds].de;

		part->Bleeding = WoundDescs[wound][ds].Bleeding;
		part->Toxinating = WoundDescs[wound][ds].Toxinating;
		part->PainLevel = WoundDescs[wound][ds].PainLevel;;
	}

	part->RemainingTicks = MED_MEGA_TICK;
}

}//namespace
