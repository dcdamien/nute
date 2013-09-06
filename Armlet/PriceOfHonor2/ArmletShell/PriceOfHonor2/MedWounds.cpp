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
    "���� ������� ����� ���� ��� �����. ������, ������� ���������, ����� ��� � �����",
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
    "���� ������� ������ ���� ��� �����. ������, ������� ���������, ����� ��� � �����",
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
    "���� ������� ����� ���� ��� �����. ������, ������� ���������, ����� ��� � �����",
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
    "���� ������� ������ ���� ��� �����. ������, ������� ���������, ����� ��� � �����",
    //    �����������
    "���� �������� ������ � ������ ����. ����� �����! ����� ������!",
},

{ //������� � ������
    //��������
    "������� ����� ���� ��������, ����� �� ������",
    //    ��������� 
    "������, ���� �����������! ������ ���� � �����",
    //    �������� 
    "������, ���� �����������! ������ ���� � �����",
    //    �������
    "������� ����� ���� ��������, ����� �� ������",
    //    �����������
    "������, ���� �����������! ������ ���� � ����� ������� �����!",
},
{ //������� � �����
    //��������
    "������� ����� ���� ��������, ����� �� ������",
    //    ��������� 
    "������, ���� �����������! ������ ���� � ������",
    //    �������� 
    "������� ����� ���� ��������, ����� �� ������",
    //    �������
    "������, ���� �����������! ������ ���� � ������",
    //    �����������
    "������, ���� �����������! ������ ���� � ������ ������� �����!",
},
{ //������� � �����
    //��������
    "������� ����� ���� ��������, ����� �� ������",
    //    ��������� 
    "������, ���� �����������! ������ ���� � �����",
    //    �������� 
    "������� ����� ���� ��������, ����� �� ������",
    //    �������
    "������, ���� �����������! ������ ���� � �����",
    //    �����������
    "������, ���� �����������! ������ ���� � ����� ������� �����!",
},

{ //������� � ������
    //��������
    "������� ����� ���� ��������, ����� �� ������",
    //    ���������
    "������, ���� �����������!  � ���� ����������� ����. �����.",
    //    ��������
    "������, ���� �������� �����������!  � ���� ����������� ����. ����� ��������� ����� � ����� ������ �� �����. ��� ������� - ������� ���� �� ��� �����!",
    //    �������
    "���� ����� � ���! ������ ������ �����",
    //    �����������
    "��� ����� ��������. ���� �����, ��� ������� ��������. ����� ������.  ���� �� ������, ������� �� �������������.",
},
{ //����������� �������
    //��������
    "���� ����� � ���! ������  �����",
    //    ���������
    "���� ����� � ���! ������  �����.",
    //    ��������
    "���� ����� � ���! ������ ����� �����",
    //    �������
    "���� ����� � ���! ������ ������ �����",
    //    �����������
    "���� ����� � ���! ������ ������ �����",
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
{ //����������� �������
    //��������
    "����-0",
    //    ���������
    "����-1",
    //    ��������
    "����-2",
    //    �������
    "����-1",
    //    �����������
    "����-4",
},
{ //����������� �������
    //��������
    "�� ������� ������� ������. �� ����� ������ ��������� ���������� �����, ������� ����� �������.,",
    //    ���������
    "�� ������� ������� ������. �� ����� ������ ��������� ���������� �����, ������� ����� �������.,",
    //    ��������
    "�� ������� ������� ������. �� ����� ������ ��������� ���������� �����, ������� ����� �������.,",
    //    �������
    "�� ������� ������� ������. �� ����� ������ ��������� ���������� �����, ������� ����� �� ���������.,",
    //    �����������
    "�� ������� ������� ������. �� ����� ������ ��������� ���������� �����, ������� ����� �� ���������.",
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

DAMAGE_EFFECT WoundToDamageEffect[MaxWoundType] =
{ 
	Rupture, Rupture, Rupture, Rupture,	//LimbShot
	Rupture, Rupture, Rupture, Rupture,	//other shots
	Blow,								//KnockOut
	Blow, Thermal, Radiation			//Explosion
};

int sdeToPain[MaxDamageEffect][MaxDamageSeverity] = {
	{1,1,1,2,3}, //Rupture
	{0,0,0,1,2}, //Blow
	{1,2,2,3,3}, //Thermal
	{0,0,0,0,0}, //Radiation
};
int sdeToBloodLoss[MaxDamageEffect][MaxDamageSeverity] = {
	{5/*000*/,10/*000*/,10/*000*/,30/*000*/,50/*000*/}, //Rupture
	{0/*000*/, 5/*000*/, 5/*000*/,15/*000*/,30/*000*/}, //Blow
	{0,0,0,0,0},		//Thermal
	{0,0,0,0,0},		//Radiation
};
int sdeToBleeding[MaxDamageEffect][MaxDamageSeverity] = {
	{0,1/*000*/,1/*000*/,5/*000*/,10/*000*/},	//Rupture
	{0,0/*000*/,1/*000*/,5/*000*/,10/*000*/},	//Blow
	{0,0,0,0,0},	//Thermal
	{0,0,0,0,0},	//Radiation
};
int sdeToToxinsAdd[MaxDamageEffect][MaxDamageSeverity] = {
	{0,0,0,0,0},	//Rupture
	{0,0,0,0,0},	//Blow
	{0,0,0,0,0},	//Thermal
	{2/*000*/,5/*000*/,10/*000*/,15/*000*/,25/*000*/},	//Radiation
};
int sdeToToxinating[MaxDamageEffect][MaxDamageSeverity] = {
	{0,0,0,0,0},	//Rupture
	{0,0,0,0,0},	//Blow
	{0,0,0,0,0},	//Thermal
	{0,1/*000*/,1/*000*/,5/*000*/,10/*000*/},	//Radiation
};
int sdeToNecroPoints[MaxDamageEffect][MaxDamageSeverity] = {
	{0,1,10,10,20},	//Rupture
	{0,1,10,10,20},	//Blow
	{1,10,20,30,40},//Thermal
	{1,1,10,50,60},	//Radiation
};

WOUND_DESC WoundDescs[MaxWoundType][MaxDamageSeverity];

void InitWounds()
{
	for (int i=0;i<MaxWoundType;i++)
		for(int j=0;j<MaxDamageSeverity;j++)
	{
		WoundDescs[i][j].target = (TARGET)i;
		WoundDescs[i][j].severity = (DAMAGE_SEVERITY)j;
		WoundDescs[i][j].message = WoundEffects[i][j];
		
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

DAMAGE_SEVERITY NextCategory(DAMAGE_SEVERITY* curr) {*curr = NextCategory(*curr); return *curr;}
DAMAGE_SEVERITY DecreaseCategory(DAMAGE_SEVERITY* curr) {*curr = DecreaseCategory(*curr); return *curr;}
DAMAGE_SEVERITY IncreaseCategory(DAMAGE_SEVERITY* curr) {*curr = IncreaseCategory(*curr); return *curr;}

void ApplyWound(int wound,int ds, PPART part)
{
	DAMAGE_EFFECT de = WoundDescs[wound][ds].de;
	part->CurrSeverity/*[de]*/ = (DAMAGE_SEVERITY)ds; //TODO FIX
	part->PainLevel = WoundDescs[wound][ds].PainLevel;
	Body.BloodCapacity -= WoundDescs[wound][ds].BloodLoss;
	part->Bleeding = WoundDescs[wound][ds].Bleeding;
	Body.ToxinsCapacity += WoundDescs[wound][ds].ToxinsAdd;
	part->Toxinating = WoundDescs[wound][ds].Toxinating;
	part->NecroPoints += WoundDescs[wound][ds].NecroPoints;
	part->RemainingTicks = MED_MEGA_TICK;
}

}//namespace