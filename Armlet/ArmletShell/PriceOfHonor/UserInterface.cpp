#include "ArmletShell.h"
#include "UserInterface.h"
#include "Images.h"

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

	fres = txtBatteryStatus.SetText("99%");
	if (fres!= SUCCESS)
		return fres;

	fres = txtRoomId.SetText("r13");
	if (fres!= SUCCESS)
		return fres;

	fres = txtMainLog.SetText("� �����. � ���, ��� �� ����������� � ��������� �����. � ���, ��� �� ������, �� �� ���������. � ���, ��� �� ������� ������� ���� ����� ������.\n"
		"� �����. � ������� �������, � ����� � ����� ������, � ������� ������ � �������� ��������.\n"
		"� �������, ����� �� ������� �� ���������� ���� �� ����.\n"
		"� �������, ����� �� ��������� ������.");
	if (fres!= SUCCESS)
		return fres;


	return SUCCESS;
}

fresult UserInterface::OnMainMnuHelp(IMenuItem* sender)
{
	return SUCCESS;
}

fresult UserInterface::OnMainMnuScrollUp(IMenuItem* sender)
{
	return txtMainLog.ScrollUp();
}

fresult	UserInterface::OnMainMnuScrollDown(IMenuItem* sender)
{
	return txtMainLog.ScrollDown();
}

fresult UserInterface::OnMainMnuCycleLeft(IMenuItem* sender)
{
	return SUCCESS;
}

fresult UserInterface::OnMainMnuShot(IMenuItem* sender)
{
	return ShowForm(&_frmWoundForm);
}

fresult UserInterface::OnMainMnuKnockout(IMenuItem* sender)
{
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
		, BlueInfo2);
	return SUCCESS;
}

fresult UserInterface::OnMainMnuCycleRight(IMenuItem* sender)
{
	return SUCCESS;
}

fresult UserInterface::OnButtonPressed( ButtonState button )
{
	txtMainLog.SetText("Menu not bound!");
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
