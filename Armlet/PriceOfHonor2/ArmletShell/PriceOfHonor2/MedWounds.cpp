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
COMPILE_TIME_CHECK(sizeof(sdeToPain)/sizeof(int)==MaxDamageEffect*MaxDamageSeverity);

int sdeToBloodLoss[MaxDamageEffect][MaxDamageSeverity] = {
	{10, 15, 20, 25, 40},	//RuptureLimb
	{20, 25, 30, 35, 50},	//Rupture
	{0, 1, 1, 5, 15},		//Blow
	{10, 15, 20, 25, 40},		//Thermal
	{20, 25, 30, 35, 50},		//Radiation
};
int sdeToBleeding[MaxDamageEffect][MaxDamageSeverity] = {
	{0,1,5,7,10},	//RuptureLimb
	{0,1,5,7,10},	//Rupture
	{0,0,3,5,7},	//Blow
	{0,0,3,5,7},	//Thermal
	{0,1,5,7,10},	//Radiation
};
int sdeToToxinsAdd[MaxDamageEffect][MaxDamageSeverity] = {
	{0,0,0,0,0},	//RuptureLimb
	{0,0,0,0,0},	//Rupture
	{0,0,0,0,0},	//Blow
	{0,5,5,10,15},	//Thermal
	{5,10,10,20,30},//Radiation
};
int sdeToToxinating[MaxDamageEffect][MaxDamageSeverity] = {
	{0,0,0,0,0},	//RuptureLimb
	{0,0,0,0,0},	//Rupture
	{0,0,0,0,0},	//Blow
	{0,1,2,3,5},	//Thermal
	{0,1,1,5,10},	//Radiation
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

void ApplyWound(int wound, int ds, PPART part)
{
	if (ds==None) {
		part->wound = UnknownTarget;
		part->CurrSeverity = None;
		part->RemainingTicks = 0;
		part->PainLevel = 0;
		part->Bleeding = 0;
		part->Toxinating = 0;
		return;
	}

	part->wound = wound;
	part->CurrSeverity = (DAMAGE_SEVERITY)ds;			

	Body.BloodCapacity -= WoundDescs[wound][ds].BloodLoss;
	Body.ToxinsCapacity += WoundDescs[wound][ds].ToxinsAdd;
	part->NecroPoints += WoundDescs[wound][ds].NecroPoints;

	part->Bleeding = WoundDescs[wound][ds].Bleeding;
	part->Toxinating = WoundDescs[wound][ds].Toxinating;
	part->PainLevel = WoundDescs[wound][ds].PainLevel;

	part->RemainingTicks = MED_MEGA_TICK;
}

}//namespace
