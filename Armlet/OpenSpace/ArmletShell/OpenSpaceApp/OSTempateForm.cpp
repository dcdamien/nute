#include "OpenSpace.h"

fresult OSTemplateForm::Init( Repositories* reps, Factories* facts, char* name, FormManager* frmmngr, OpenSpaceApp* app, OpenSpaceLogic* logic )
{
	fresult fres;
	_TitleText = "title/";
	_SubtitleText = "Subtitle";

	fres = BaseInit(sbdmTitles, reps,facts, name, frmmngr, app, logic);
	ENSURESUCCESS(fres);

	return SUCCESS;
}

fresult OSTemplateForm::DoLayout()
{
	fresult fres;

	ubyte_t controlsCount = 1;

	Size caSz = _App->GetClientAreaSize();
	Position caPos = _App->GetClientAreaPos();

	fres = _Factories->GetPanelFactory()->GetPanel(caSz, caPos, controlsCount, CL_TRANSPARENT, &_FormPanel);
	ENSURESUCCESS(fres);


	TextField* tf;
	Position pos;
	pos.Left =5;
	pos.Top = 50;
	//URGENTTODO: ������ �����
	char* caption;
	caption = "�������� �����";
	TextFieldFactory* tff = _Factories->GetTextFieldFactory();
	tff->CurrentTextFormatHandle=TF_PARROT;
	uword_t captionLen = Length(caption);

	Size tftxSize;
	tftxSize.Width = 14;
	tftxSize.Height = 6;

	fres = tff->GetTextBox(pos, tftxSize, 1, &tf);
	ENSURESUCCESS(fres);
	tf->AppendText(caption);
	ENSURESUCCESS(fres);
	fres = _FormPanel->AppendControl(tf);
	ENSURESUCCESS(fres);

	//get stipes
/*	Panel* stripes = NULL;
	fres = GetStripesPanel(frmStripeMessageYNDialog, &stripes);
	ENSURESUCCESS(fres);
	if (stripes!=NULL)
	{
		fres = _FormPanel->AppendControl(stripes);
		ENSURESUCCESS(fres);
	}


	//get menu
	fres = CreateMenu(&_Menu);
	ENSURESUCCESS(fres);
*/
	return SUCCESS;
}


fresult OSTemplateForm::CreateMenu( IMenu** o_mnu )
{
	fresult fres;
	MenuFactory* mf = _Factories->GetMenuFactory();

	//ready factory
	mf->CurrentInterlaced = true;
	mf->CurrentTextFormatHandle = TF_MENU;
	mf->CurrentEvenTextFormatHandle = TF_MENUEVEN;
	mf->ClearSettings();

	//Set up menu
	MenuItemSettings* mis;


	//ItemOriginE
	mis = &mf->Settings[ItemOriginE];
	mis->ImgHandle = small_arrow_bottom;
	mis->Text = "�����";
	fres = _FormManager->GetCloseFormHandler(&mis->Handler, fsrCancel);
	ENSURESUCCESS(fres);
	mis->Empty = FALSE;

	//create mnu
	IMenu* mnu = NULL;
	fres = mf->GetMenu(ABCXYZLER, &mnu);
	ENSURESUCCESS(fres);

	//Clean up
	mf->ClearSettings();
	mf->DefaultInterlaced=mf->CurrentInterlaced;
	mf->DefaultTextFormatHandle=mf->CurrentTextFormatHandle;
	mf->DefaultEvenTextFormatHandle=mf->CurrentEvenTextFormatHandle;

	//Get menu Items

	*o_mnu = mnu;
	return SUCCESS;
}

