#include "OpenSpace.h"




fresult OSBehaviourLogic::Init()
{
	fresult fres;
	
	fres = InitBehaviours();
	ENSURESUCCESS(fres);

//DEBUG;
	Patterns[bhpWoundHead].IsActive = TRUE;
	Patterns[bhpFuckingIllness].IsActive = TRUE;
	Patterns[bhpFuckingIllness].IsNew = TRUE;
	Patterns[bhpEgoCritical].IsActive = TRUE;


	return SUCCESS;
}

fresult OSBehaviourLogic::InitBehaviours()
{

	Patterns[bhpWoundHead].Text = "����� ����� ������� ����. �� �� ������ �� ������ ������";
	Patterns[bhpWoundHead].Title = "���� ����������";
	Patterns[bhpWoundHead].IsCritical = FALSE;
	Patterns[bhpWoundHead].CritText = NULL;

	Patterns[bhpWoundTorso].Text = "���� ��� ��� ���� � ���� �����. ������������� ������ ������ � ���������. ����� �� ��� �������?";
	Patterns[bhpWoundTorso].Title = "���� ���� �������";
	Patterns[bhpWoundTorso].IsCritical = FALSE;
	Patterns[bhpWoundTorso].CritText = NULL;

	Patterns[bhpFuckingIllness].Text = "������ �������. ������� � ������ � ������ ����. �� ������ ������ ������ � ������";
	Patterns[bhpFuckingIllness].Title = "�����";
	Patterns[bhpFuckingIllness].IsCritical = TRUE;
	Patterns[bhpFuckingIllness].CritText = "��������!\n����������� ������� ������� ����������� ���������. \n���������� �������?";

	Patterns[bhpEgoCritical].Text = "� ���� ���������� �������������, � ��� ����������. ��� �� ������ � ���� � ����? � ���� ���� ������� �������� ������ ��������.";
	Patterns[bhpEgoCritical].Title = "������ ���";
	Patterns[bhpEgoCritical].IsCritical = FALSE;
	Patterns[bhpEgoCritical].CritText = NULL;

	for (ubyte_t i =0; i< bhpLast; i++)
	{
		Patterns[i].IsActive = FALSE;
	}

	return SUCCESS;
}
