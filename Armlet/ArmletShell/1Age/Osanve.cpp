#include "ArmletApi.h"
#include "ArmletShell.h"
#include "AppMain.h"
#include "UserInterface.h"
#include "Osanve.h"
#include "conf.h"

extern UserInterface UI;

namespace osanve {

ArmletApi::FILE PlayerFile;
player Player; // ��������� �������� ������

// ���������� �������� ����������� ���
void SetFPH(ubyte_t newFPH)
{
	if ((newFPH<1)/*||(regenRate>3)*/) return;
	Player.fph = newFPH;
	return;
}

// ������ ��������� ���������
void PlayerInit()
{
	int sz = 0;
	bool ret = ArmletApi::OpenFile(&PlayerFile, "PState.bin",false);
	if (ret) {
		sz = ArmletApi::ReadFile(&PlayerFile,(char*)&Player,sizeof(player));
	} else {
		ArmletApi::OpenFile(&PlayerFile, "PState.bin",true);
	}
	if (sz!=sizeof(player)) { // ���� ������ ������ ���� userId
		InitPlayer( &Player); // ��. conf.cpp
	}
	memset( OSNV, 0, MAX_ARMLET*sizeof(nick));
	memset( FGHT, 0, MAX_ARMLET*sizeof(nick));

}

// ��� ������� ��������������
void OnForceTick(void)
{	
	//save
	ArmletApi::WriteFile(&PlayerFile,(char*)&Player,sizeof(player));
// ���������� ���
  if( Player.force + Player.fph > Player.forceMax)
  	Player.force = Player.forceMax;
  else
  	Player.force += Player.fph;
// ������ ������� ���������
  if( Player.status == AL_STATUS_DEFEAT) {
  	if(Player.defeatTime > 0)
  		Player.defeatTime--;
  		// ����������� ��������� �����������
  	if(Player.defeatTime <= 0)
  		Player.status = AL_STATUS_OSANVE;
  }
//	//To server
//	ubyte_t state[5];
//	state[0] = (Player.BloodCapacity);	// / 1000);
//	state[1] = (Player.ToxinsCapacity);	// / 1000);
//	ArmletApi::SendAppState(state);
}

// ������������ ������� �����
// ������ ��������� �����, �� ��������� ���� ���������
void GetAtackPacket(char* a_packet, ubyte_t a)
{
	if(!a_packet) return;
	// �������� �������
	*a_packet = Player.userId; // ��� ID
	if(Player.status!=AL_STATUS_FIGHT)
	  return;
	*(a_packet+1) = 0x80 | ((Player.cons<<4)&0x70);
	*(a_packet+1) |= Player.atackSeq++;
	Player.atackSeq %= MAX_ATACK_SEQ;
	*(a_packet+2) = Player.enemyId;
    *(a_packet+3) = a; // ���� �����, ��� ��������
}

// ������������ ������� �����
// ������ ��������� �����, �� ��������� ���� ���������
void GetHealPacket(char* h_packet, ubyte_t h)
{
	if(!h_packet) return;
	// �������� �������
	GetAtackPacket(h_packet,h);
	*(h_packet+1) |= FORCE_HEAL; // ���� �������
}

// ������������ ������� ������
void GetOsanvePacket(char* osanve_packet)
{	
	if(!osanve_packet) return;
	// �������� �������
	*osanve_packet = Player.userId; // ��� ID
	switch(Player.status) {
		case AL_STATUS_FIGHT:
		case AL_STATUS_DEFENSE:
		case AL_STATUS_PREPARE: *(osanve_packet+1) = OSANVE_FIGHT;
			break;
	    case AL_STATUS_DEFEAT: *(osanve_packet+1) = OSANVE_FEAR;
			break;
		default: *(osanve_packet+1) = Player.osanve; // ��� ������
			break;
	}
	*(osanve_packet+2) = Player.force;  // ���� ����
	*(osanve_packet+3) = (Player.status==AL_STATUS_DEFEAT)?(0):(Player.maxForce); // ��� �������� ����
	// ���� ��� �� 2 �����
	if (Player.evil) *(osanve_packet+1) |= FORCE_SIDE_EVIL;
}

// ��������� ���������� � ����� (�������� ������)
bool PreFightEnd(void)
{ // ����� ��� ����� ���� � ������, ����� ������ �� ������
	if( Player.status != AL_STATUS_PREPARE)
		return false;
	
	Player.status = AL_STATUS_FIGHT;
	
	Atacked( Player.penalty, Player.penaltyCons, Player.enemyId);
	
	Player.penalty = 0;
	
	return false;
}

// ??
//void _osanveAfterWoundUpdate(char** oSymptoms)
//{
//	GatherDescs(buf1, sizeof(buf1)-1);
//	*oSymptoms = buf1;
//}

//simple healing
ubyte_t Healed(ubyte_t h)
{ // ������� ����������� � ����� ���������, �� �� ������� �� �����������
	if( (h + Player.force) > Player.maxForce )
		Player.force = Player.maxForce;
	else
		Player.force += h;
  return Player.force;
}

// ������� ����-�� � ����� �
ubyte_t Atack(ubyte_t a)
{ // �������� ������� ������
	if( Player.status == AL_STATUS_FIGHT)
	{
		if( a > Player.force)
			a = Player.force;
		Player.force -= a;
	}
	return Player.force;
}

// �������� ���-�� enemyId � ����� � � ������������ cons
// cons � enemyId ����� ��� ����������� ��� �������� � ���������� �����
ubyte_t Atacked(ubyte_t a, ubyte_t cons, enemyId)
{
	ubyte_t atack = 0;
	if(cons>CONS_COUNT)
		cons = 0;

	Player.enemyId = enemyId; // �� ����

	switch( Player.status){
		case AL_STATUS_DEFENSE: // � ������
		{ // ���� ����� �� ����� ���� ������ 5
			atack = (a + 5) / 10;
			break;
		}
		case AL_STATUS_FIGHT: // � ���
		{ // ���� ����� �� ����� ���� ������ 5
			atack = a;
			break;
		}
		case AL_STATUS_DEFEAT: // ��� �������, � �����������
		{ // ���� ����� �� ����� ���� ������ 5
			atack = 0;
			break;
		}
		default: // ��� ��������� ���������: ������� � ���������� �����
		{ // ���� ����� �� ����� ���� ������ 5
			atack = 0; // ������ ����� �� �������� ������
			Player.penalty += a; // ����� ������� ������
			Player.penaltyCons = cons; // � �����������
			Player.status = AL_STATUS_PREFIGHT;
			//Launch PreFight Timer
	    ArmletApi::RequestTimer(_PreFightTimerCallback, PREFIGHT_TIME);
		//////////////////////////////////////////////////////////////////
		/////////////// �������� ���������� ����������� ������ ///////////
		//////////////////////////////////////////////////////////////////
			break;
		}
	}

// ����������� ������ �����
	if( Player.force < atack)
	{
		Player.force = 0;
		// ���������, ������� � �����������
		Player.status = AL_STATUS_DEFEAT;
		Player.penaltyCons = cons; // ���������� �����������
		//////////////////////////////////////////////////////////////////
		/////////////// �������� ���������� ����������� //////////////////
		//////////////////////////////////////////////////////////////////
	} else
		Player.force -= atack;
	
	return Player.force;
}

// ������ ������ ������
void DefenceON(void)
{
	Player.status = AL_STATUS_DEFENSE;
	// � ������ ��������� ���, ��� ����������
	Atacked( Player.penalty, Player.penaltyCons, Player.enemyId);
	
	Player.penalty = 0;
}

// ������ ������ ������
void DefenceOFF(void) { 
  Player.status = AL_STATUS_FIGHT;
}

// ����� ������
void SetOsanve(ubyte_t no)
{
	Player.osanve = no;
}

#pragma region forUI


//temp
//char _buf[201];

//char* _osanveOnExplosion()
//{
//	int Target = ArmletApi::GetRandom(MaxTarget);
//	int DamageSeverity = IncreaseCategory(&Player.parts[Target].CurrSeverity);
//	int ExplosionType = ArmletApi::GetRandom(2);
//	if (ExplosionType == 1)
//		ExplosionType = 2; //skip scorch
//	ApplyWound(MaxTarget+1+ExplosionType,DamageSeverity,&Player.parts[Target]);
//	const char* msg =  WoundDescs[MaxTarget+1+ExplosionType][DamageSeverity].message;
////temp
////	ArmletApi::snprintf(_buf,200,"%s-%d\n%s",
////		TargetNames[MaxTarget+1+ExplosionType],
////		DamageSeverity,
////		msg);
////	return _buf;
//	return (char*)msg;
//}


#pragma endregion

} //namespace

