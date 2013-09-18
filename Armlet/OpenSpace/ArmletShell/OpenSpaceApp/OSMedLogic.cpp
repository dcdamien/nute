#include "OpenSpace.h"

char* OSMedLogic::GetWoundTargetText( MedWoundTarget target )
{
	char* result;
	switch (target)
	{
		case mwtLimbTarget:
			result = "� ���� (����) ������ ����! ��� ����� ���������?";
		break;
		case mwtUpTorso:
			result = "� ����� ������ ����! ��� ����� ���������?";
			break;
		case mwtDownTorso:
			result = "� ����� ������ ����! ��� ����� ���������?";
			break;
		case mwtHeadTarget:
			result = "� ������ ������ ����! ��� ����� ���������?";
			break;
		case mwtBeatenTarget:
			result = "����������� ���������� ����� ������...";
			break;
		case mwtStunnedTarget:
			result = "�� ��������! ��� ����� ���������?";
			break;
		case mwtDyingTarget:
			result = "�� ���������! ��� ����� ���������?";
			break;
		default:
			result = "������� ����, �� ��";
	}

	return result;
}

fresult OSMedLogic::AddNewWound( MedWoundTarget target )
{
	_wounds[target].Active = TRUE;
	return SUCCESS;
}

fresult OSMedLogic::Init()
{
	
	_wounds[mwtDyingTarget].WoundText = "��� ������";
	_wounds[mwtStunnedTarget].WoundText = "�������"; 
	_wounds[mwtBeatenTarget].WoundText = "�����";
	_wounds[mwtLimbTarget].WoundText = "���������� ����������"; 
	_wounds[mwtUpTorso].WoundText = "������� �������(����)";
	_wounds[mwtDownTorso].WoundText = "������� �������(���)";
	_wounds[mwtHeadTarget].WoundText = "������ ������";
	
	InitBody();

	return SUCCESS;
}

void OSMedLogic::InitBody()
{
	for (ubyte_t i=0; i< MedWoundTargetLast; i++)
	{
		_wounds[i].Active = FALSE;
	}
}

fresult OSMedLogic::CreateMedStatus( TextField* tf )
{
	fresult fres;

	fres = tf->Clear();
	ENSURESUCCESS(fres);

	for (ubyte_t i=0; i< MedWoundTargetLast; i++)
	{

		if (_wounds[i].Active == TRUE)
		{
			fres = tf->AppendText(_wounds[i].WoundText);
			ENSURESUCCESS(fres);
			fres = tf->AppendText("\n");
			ENSURESUCCESS(fres);

		}
	}

	return SUCCESS;
}
