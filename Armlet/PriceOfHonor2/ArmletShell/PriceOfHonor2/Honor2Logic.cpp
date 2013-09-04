#include "Honor2.h"
#include "ArmletApi.h"
#include "AppMain.h"


#ifdef _MSC_VER
#define ZERO_ROOM_LUSTRAS_COUNT 2
static const int _gZeroRoomLustras[ZERO_ROOM_LUSTRAS_COUNT] = {12,15};
#else
#define ZERO_ROOM_LUSTRAS_COUNT 1
static const int _gZeroRoomLustras[ZERO_ROOM_LUSTRAS_COUNT] = {72};
#endif

fresult Honor2Logic::Init( Honor2App* app )
{
	_medInit();
	
	_App = app;

	_mainForm = (Honor2MainForm*)_App->GetFormManager()->GetForm(_App->Forms->Honor2MainFormName);
	FAILIF(_mainForm==NULL);

	_logForm = (LogForm*)_App->GetFormManager()->GetForm(_App->Forms->LogFormName);
	FAILIF(_logForm==NULL);

	//init lustra
	_lastKnownDiscoveryTime = ArmletApi::GetUpTime();
	_lastKnownRoomId =0;
	_lastKnownLustraId = UNKNOWN_ID;
	//Launch lustra query Timer
	ArmletApi::RequestTimer(_QueryLustraTimerCallback, LUSTRA_POLL_TIME);

	//launch medicine
	ArmletApi::RequestTimer(_MedicineTimerTickCallback, MED_TICK_TIME);

	return SUCCESS;
}

char* Honor2Logic::OnNewWound( TARGET trg )
{
	return _medNewWound(trg);
}


fresult Honor2Logic::OnKnockout()
{
	fresult fres;

	char* knockoutResult = _medOnKnockout();

	char* medstatus;
	_medAfterWoundUpdate(&medstatus);
	fres = SetMainStatus(medstatus);
	ENSURESUCCESS(fres);

	fres = _App->MsgBoxShow(BlueHealth, "������!", knockoutResult);
	ENSURESUCCESS(fres);

	fres = _App->RedrawCurrentForm();
	ENSURESUCCESS(fres);

	return SUCCESS;
}

void Honor2Logic::OnPillConnected(sword_t cure_id, sword_t charges)
{
	fresult fres;

	//Check if there are charges
	if (charges==0)
	{
		fres=ShowMessage("�� �������!", BlueWarning, "������� � ���������� �����!", FALSE);
		if (fres!=SUCCESS)	
		{
			ReportError("Cant't show msgbox!");
			return;
		}
	}
	else
	{
		//Call medicine
		char* str = _medOnPillConnected((CURE_ID)cure_id);

		fres=ShowMessage("�������� ��������!" , BlueHealth, str , FALSE);
		if (fres!=SUCCESS)	
		{
			ReportError("Cant't show msgbox!");
			return;
		}

		if(!ArmletApi::WritePill(cure_id, charges-1))
		{
			ReportError("Cant't write pill!");
			return;
		}
	}	
}

void Honor2Logic::OnExposion(sword_t roomId)
{
	fresult fres;
	if (roomId==_lastKnownRoomId)
	{
		char* explosionResult = _medOnExplosion();
		char* medstatus;
		_medAfterWoundUpdate(&medstatus);
		fres = SetMainStatus(medstatus);
		if (fres!=SUCCESS)	
		{
			ReportError("Cant't set status!");
			return;
		}


		fres = ShowMessage("� ������ �����!", BlueHealth, explosionResult, TRUE);
		if (fres!=SUCCESS)	
		{
			ReportError("Cant't show msgbox!");
			return;
		}
	}
}

void Honor2Logic::SetRegenRate( ubyte_t regenRate )
{
	_medSetRegenerationRate(regenRate);
}

void Honor2Logic::SetPlayerName( char* playerName )
{
	fresult fres;

	fres = _App->AppStatusBar->SetPlayerName(playerName);
	if (fres!=SUCCESS)
	{
		ReportError("Can't set text to txtUserName!");
		return;
	}

	fres= _App->RedrawCurrentForm();
	if (fres!=SUCCESS)
	{
		ReportError("Can't redraw _frmMainForm");
		return;
	}

	return;
}

fresult Honor2Logic::ShowMessage( char* title, ImageHandle iconHandle, char* text, bool_t wakeUp)
{
	fresult fres;

	fres = _App->MsgBoxShow(iconHandle, title, text);
	ENSURESUCCESS(fres);
	
	return SUCCESS;
}

fresult Honor2Logic::AppendLog( LogKinds log, char* message )
{
	fresult fres;
	fres = _logForm->LogRecord(log, "\n");
	ENSURESUCCESS(fres);
	fres = _logForm->LogRecord(log, message);
	ENSURESUCCESS(fres);

	return SUCCESS;
}

fresult Honor2Logic::ResetLog( LogKinds log, char* message )
{
	fresult fres;
	fres = _logForm->CleanLog(log);
	ENSURESUCCESS(fres);
	fres = _logForm->LogRecord(log, message);
	ENSURESUCCESS(fres);

	return SUCCESS;
}


fresult Honor2Logic::SetMainStatus( char* mainStatus )
{
	fresult fres;

	if (_mainForm!=NULL)
	{
		fres = _mainForm->SetStatus(mainStatus);
		ENSURESUCCESS(fres);
	}

	return SUCCESS;
}

void Honor2Logic::OnLustraTimer()
{
	
	//Query current lustraid
	ubyte_t currLustraId = ArmletApi::GetLustraId();
	sword_t currRoomId = GetRoomIdFromLustraId(currLustraId); 
	int currTime = ArmletApi::GetUpTime();


	//char strBuff[40];
	//ArmletApi::snprintf(strBuff, 40, "t:%d, r:%d", currTime,currLustraId);
	//AppendLog(LOG_EVENT, strBuff);

	if(currLustraId == UNKNOWN_ID)
	{
		if (_lastKnownRoomId == 0)
		{
			//zero room, all is ok
			//		AppendLog(LOG_EVENT, "���������� ���� � 0 �������");
		}
		else
		{
			//check if we had a good room no longer that specified time
			if (currTime - _lastKnownDiscoveryTime > MAX_LUSTRA_WAIT_TIME)
			{
				_App->DoVibroAndBeep();
				ShowMessage("������ �����!", BlueExclamation, "������ ������ ������� ������� ������������ ������!", TRUE);

				if(_lastLoggedTime ==-1 || currTime - _lastKnownRoomId)
				{
					//AppendLog(LOG_EVENT, "\n ��� ��������� ������!");
					_lastLoggedTime = currTime;
				}
				SetRoom(currRoomId);
				//AppendLog(LOG_EVENT, "���������� �� ������");
			}
		}
	}
	else
	{
		//good lustra
		_lastLoggedTime = -1;
		_lastKnownDiscoveryTime = currTime;
		if ((currRoomId!= _lastKnownRoomId)||(currLustraId != _lastKnownLustraId))
		{
			SetRoom(currRoomId);
		}
		_lastKnownRoomId = currRoomId;
		_lastKnownLustraId = currLustraId;
	}
	return;
}

fresult Honor2Logic::SetRoom( sword_t room )
{
	fresult fres;

	fres = _App->AppStatusBar->SetRoom(room);
	ENSURESUCCESS(fres);

	fres = _App->RedrawCurrentForm();
	ENSURESUCCESS(fres);

	return SUCCESS;
}

void Honor2Logic::OnMedTick()
{
	fresult fres;

	char* symptoms;
	char* medLog;

	_medOnMedTick(&medLog);
	fres = SetMainStatus(medLog);

	fres = _App->RedrawCurrentForm();
}

fresult Honor2Logic::ReportError( char* errorText )
{
	_App->LogError(errorText);
	return SUCCESS;
}

void Honor2Logic::OnNewMessage( char* messageText )
{
	
}

sword_t Honor2Logic::GetRoomIdFromLustraId( sword_t lustraId )
{
	sword_t roomId=lustraId;

	for(ubyte_t i=0; i< ZERO_ROOM_LUSTRAS_COUNT; i++)
	{
		if(lustraId == _gZeroRoomLustras[i])
		{
			roomId = 0;
			break;
		}
	}

	return roomId;
}
