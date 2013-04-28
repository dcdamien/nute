#include "UserInterface.h"
#include "Icons.h"

fresult UserInterface::Init()
{
	fresult fres;
	fres = UIDesigner::Init();
	if (fres!= SUCCESS)
		return fres;

	//Setting texts
	fres = txtUserName.SetText("����\n������");
	if (fres!= SUCCESS)
		return fres;

	fres = txtBatteryStatus.SetText("99%\nr10");
	if (fres!= SUCCESS)
		return fres;

	fres = txtStatus.SetText("� �����. � ���, ��� �� ����������� � ��������� �����. � ���, ��� �� ������, �� �� ���������. � ���, ��� �� ������� ������� ���� ����� ������.\n"
		"� �����. � ������� �������, � ����� � ����� ������, � ������� ������ � �������� ��������.\n"
		"� �������, ����� �� ������� �� ���������� ���� �� ����.\n"
		"� �������, ����� �� ��������� ������.");
	if (fres!= SUCCESS)
		return fres;


	return SUCCESS;
}

fresult UserInterface::OnMainMnuHelp(IMenuItem* sender)
{
	txtStatus.SetText("OnMainMnuHelp");
	return SUCCESS;
}

fresult UserInterface::OnMainMnuScrollUp(IMenuItem* sender)
{
	return txtStatus.ScrollUp();
}

fresult	UserInterface::OnMainMnuScrollDown(IMenuItem* sender)
{
	return txtStatus.ScrollDown();
}

fresult UserInterface::OnMainMnuCycleLeft(IMenuItem* sender)
{
	txtStatus.SetText("OnMainMnuCycleLeft");
	return SUCCESS;
}

fresult UserInterface::OnMainMnuShot(IMenuItem* sender)
{
	return ShowForm(&_frmWoundForm);
}

fresult UserInterface::OnMainMnuKnockout(IMenuItem* sender)
{
	txtStatus.SetText("OnMainMnuKnockout");
	return SUCCESS;
}

fresult UserInterface::OnMainMnuOpenLock(IMenuItem* sender)
{
	MessageBoxShow("��������� �����!", "��� ���! � ����� ����� ����� �������, ��� ����� ������ ������� �������. � ����� ���� ������ � �������� ��������� NFC? ����! ����� �� �� �� ��������, � ��� �� ��������������!"
		"��� ���! � ����� ����� ����� �������, ��� ����� ������ ������� �������. � ����� ���� ������ � �������� ��������� NFC? ����! ����� �� �� �� ��������, � ��� �� ��������������!"
		"��� ���! � ����� ����� ����� �������, ��� ����� ������ ������� �������. � ����� ���� ������ � �������� ��������� NFC? ����! ����� �� �� �� ��������, � ��� �� ��������������!"
		"��� ���! � ����� ����� ����� �������, ��� ����� ������ ������� �������. � ����� ���� ������ � �������� ��������� NFC? ����! ����� �� �� �� ��������, � ��� �� ��������������!"
		"��� ���! � ����� ����� ����� �������, ��� ����� ������ ������� �������. � ����� ���� ������ � �������� ��������� NFC? ����! ����� �� �� �� ��������, � ��� �� ��������������!"
		"��� ���! � ����� ����� ����� �������, ��� ����� ������ ������� �������. � ����� ���� ������ � �������� ��������� NFC? ����! ����� �� �� �� ��������, � ��� �� ��������������!"
		"��� ���! � ����� ����� ����� �������, ��� ����� ������ ������� �������. � ����� ���� ������ � �������� ��������� NFC? ����! ����� �� �� �� ��������, � ��� �� ��������������!"
		, ORANGE_ARROW_DOWN);
	return SUCCESS;
}

fresult UserInterface::OnMainMnuCycleRight(IMenuItem* sender)
{
	txtStatus.SetText("OnMainMnuCycleRight");
	return SUCCESS;
}

fresult UserInterface::OnButtonPressed( ButtonState button )
{
	txtStatus.SetText("Menu not bound!");
	return SUCCESS;
}

fresult UserInterface::OnWoundMnuHead( IMenuItem* sender )
{
	return txtWoundResult.AppendText("��! ���-�� �������� �� ������! �����!\n");;
}

fresult UserInterface::OnWoundMnuStomach( IMenuItem* sender )
{
	return txtWoundResult.AppendText("����� ���-�� ���-�� �������� ������..\n");;
}

fresult UserInterface::OnWoundMnuLeftArm( IMenuItem* sender )
{
	return txtWoundResult.AppendText("������ �� ����� ���� �������� �����. �����, ����.\n");
}

fresult UserInterface::OnWoundMnuRightArm( IMenuItem* sender )
{
	return txtWoundResult.AppendText("������ ���� ��� ������. �������...\n");
}

fresult UserInterface::OnWoundMnuChest( IMenuItem* sender )
{
	return txtWoundResult.AppendText("�������� ������� ������� ���� � �����. ������� ������ �����???\n");
}

fresult UserInterface::OnWoundMnuBack( IMenuItem* sender )
{
	return txtWoundResult.AppendText("����� �����. ������������ ���-�� �����? \n");
}

fresult UserInterface::OnWoundMnuLeftLeg( IMenuItem* sender )
{
	return txtWoundResult.AppendText("�� ���! ������ � ������ �� ����� ����. ��������!\n");
}

fresult UserInterface::OnWoundMnuRightLeg( IMenuItem* sender )
{
	return txtWoundResult.AppendText("�� ������ ���� ������ �� ���������! ������ ����!\n");
}
