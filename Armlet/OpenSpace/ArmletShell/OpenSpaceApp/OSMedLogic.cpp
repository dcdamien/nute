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
	return SUCCESS;
}

fresult OSMedLogic::Init()
{
	return SUCCESS;
}
