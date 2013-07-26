#include "ThreeKShell.h"

namespace ThreeKShell {

	IControl** PanelFactory::AllocControlArray( ubyte_t controlsCount )
	{
		IControl** ctrls = new IControl*[controlsCount];
		NULLIF(ctrls==NULL);

		for (ubyte_t i=0; i < controlsCount;i++)
		{
			ctrls[i] = NULL;
		}
		
		return ctrls;
	}

	Panel* PanelFactory::AllocPanel()
	{
		return new Panel();
	}

	fresult PanelFactory::GetPanel( Size sz, Position pos, ubyte_t controlsCount, Panel** o_pnl )
	{
		return GetPanel( sz, pos, controlsCount, CL_TRANSPARENT,o_pnl);
	}

	fresult PanelFactory::GetPanel(Size sz, Position pos, ubyte_t controlsCount, ColorHandle clrhandle,  Panel** o_pnl)
	{
		fresult fres;
		
		IControl** controls;
		if (controlsCount==0)
		{
			controls = NULL;
		}
		else
		{
			controls = AllocControlArray(controlsCount);
			FAILIF(controlsCount==NULL);
		}

		Panel* pnl = AllocPanel();
		FAILIF(pnl==NULL);
		
		fres = pnl->Init(sz,pos,_render, controls, controlsCount);
		ENSURESUCCESS(fres);

		Color clr;
		fres =  _repositories->Colors->GetColorById(clrhandle, &clr);
		ENSURESUCCESS(fres);

		fres = pnl->SetColor(clr);
		ENSURESUCCESS(fres);

		*o_pnl = pnl;

		return fres;
	}

	fresult PanelFactory::Init (IRender* render, Repositories* reps )
	{
		_render = render;
		_repositories = reps;

		return SUCCESS;
	}

}



