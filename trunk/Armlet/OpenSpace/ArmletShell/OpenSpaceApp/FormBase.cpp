#include "ThreeKShell.h"
#include "To3KShell.h"
#include "kl_allocator.h"

static Alloc_t<IMenu*, 30> SIMenuPtrArr;


fresult FormBase::BaseInit( Repositories* reps, Factories* facts, char* name, FormManager* frmmngr, ApplicationBase* app )
{
	FAILIF(reps==NULL);
	FAILIF(facts==NULL);
	FAILIF(name==NULL);
	FAILIF(frmmngr==NULL);
	FAILIF(app==NULL);

	_Repositories = reps;
	_Factories = facts;
	_FormManager = frmmngr;
	_Name = name;
	_AppBase = app;
	
	_FormPanel = NULL;
	_Menus = NULL;
	_MenusCount = 0;

	return SUCCESS;
}

char* FormBase::GetName()
{
	return _Name;
}

fresult FormBase::OnButtonEvent( ButtonState key )
{
	for (int i =0; i< _MenusCount ; i++)
	{
		if (!_Menus[i]->ProcessButton(key))
		{
			break;
		}
	}

	return SUCCESS;
}

fresult FormBase::OnBeforeShow( IForm* prevFrom, bool_t reActivation, FormShowResults results )
{
	return SUCCESS;
}

fresult FormBase::OnAfterShow( IForm* prevFrom, bool_t reActivation, FormShowResults results )
{
	return SUCCESS;
}

fresult FormBase::OnLoad()
{
	return SUCCESS;
}

fresult FormBase::Draw()
{
	fresult fres;

	if (_FormPanel!=NULL)
	{
		fres = _FormPanel->Draw();
		ENSURESUCCESS(fres);
	}

	for (int i =0; i< _MenusCount ; i++)
	{
		fres = _Menus[i]->Draw();
		ENSURESUCCESS(fres);
	}

	return SUCCESS;
}

IMenu** FormBase::AllocMenus( ubyte_t menusCount )
{
	_MenusCount = menusCount;
	return SIMenuPtrArr.Allocate(menusCount); // new IMenu*[menusCount];
}


