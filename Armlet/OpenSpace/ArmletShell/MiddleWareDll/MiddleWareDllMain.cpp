#include "ArmletApi.h"
#include "ArmletShell.h"
#include "MiddleInterface.h"
#include "AppMain.h"

//TODO TO BUTTONS and to app
BUTTON_HANDLER* gClickButtonHandler = NULL;
BUTTON_HANDLER* gHoldButtonHandler = NULL;
void RegisterButtonHandlers(BUTTON_HANDLER ClickButtonHandler,BUTTON_HANDLER HoldButtonHandler)
{
	gClickButtonHandler = ClickButtonHandler;
	gHoldButtonHandler = HoldButtonHandler;
}

namespace ArmletApi {
	
	bool __CALLOUT InitializeShell() {
		Clear(RED);
		//StartThread(my_thread,NULL);
		StartThread(AppMainThread,NULL);
		return true; //TODO
	}

	void __CALLOUT CriticalError(char* error)
	{
		//TODO
	}

	void __NOCALL  Log(char* fmt, ...)
	{
		//TODO
	}

	//__CALLOUT for  button
	void __CALLOUT OnButtonPress(int button_id)
	{
		; //TODO
	}

	//__CALLOUT for button
	void __CALLOUT OnButtonRelease(int button_id)
	{
		if (gClickButtonHandler)
			(*gClickButtonHandler)((ubyte_t)button_id);
	}

	//__CALLOUT cure/pill
	void __CALLOUT OnPillConnect(int cure_id, int charges)
	{
		//Log("Cure %d was connected, charges %d",cure_id, charges);
		Log("Cure was connected, with charges");
		WritePill(cure_id, charges-1);
		DoVibro(500);
		ArmletApi::SetCureName(1,"�����������");
		ArmletApi::SetCureName(9,"���������");
		ArmletApi::SetCureName(12,"����������");
		if (charges == 0) {
			; //TODO
		} else {
			; //TODO
		}
	}

	//__CALLOUT for radio transport
	void __CALLOUT OnRadioPacket(unsigned char* packet, int len)
	{
		; //TODO
	}
} //namespace

namespace LowLevel {

#ifdef _MBCS
	//internal emulation (time)
	void NextMedTick()
	{
		//TODO
	}
#endif

} //namespace