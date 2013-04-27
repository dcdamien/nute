#pragma once
#ifndef _MED_
	#error _MED_
#endif

//WOUND types:
typedef enum _WOUND_TYPE {
	UnknownWound = -1,
	//SHOTS:
		//LIMBS:
		LeftArmShot = 0,	//"��������� � ����������, ����� ����"
		RightArmShot,		//"��������� � ����������, ������ ����"
		LeftLegShot,		//"��������� � ����������, ����� ����"
		RightLegShot,		//"��������� � ����������, ������ ����"
		//TORSO:
		ChestShot,			//"��������� � �����"
		AbdomenShot,		//"��������� � �����"
		//HEAD:
		HeadShot,			//"��������� � ������"
	//KNOCKOUT:
	KnockOut,				//"������"
	//EXPLOSIONS:
	ExplosionBlast,			//"���������� ������ ������, ������� �����"
	ExplosionScorch,		//"���������� ������ ������, ����"
	ExplosionRadiation,		//"���������� ������ ������, ��������"
	MaxType
} WOUND_TYPE;

//WOUND severity:
typedef enum _WOUND_SEVERITY {
	NoWound = -1,		//"��� �������"
	Light = 0,		//"��������"
	Medium,		//"���������"
	Serious,		//"�������"
	Insidious,		//"��������"
	Critical,		//"�����������"
	MaxSeverity
} WOUND_SEVERITY;

class Wound_t {
public:
	//static members
	static WOUND_TYPE const id = UnknownWound;
	static WOUND_SEVERITY const type = NoWound;
	//static members as inline getters
	static inline char const*const CureName(void);					//cure name
	static inline char const*const CurePurpose(void);				//cure purpose description
	static inline char const*const CureEffect(void);				//cure healing effect description
	static inline char const*const CureContraindications(void);		//cure contraindications description
	static inline char const*const CureSideEffects(void);			//cure side effects description
	//methods
	virtual void OnUse(void) const {};								//cure effect on first use
	virtual void OnTick(void) const {};								//cure effect on each tick
	virtual ~Wound_t(void) {return;}								//empty virtual destructor is required
};

/*class WOUND {
	virtual OnFirst();
	virtual OnUse();
}*/

typedef struct _WOUND {
	unsigned short type;			//wound subtype
	unsigned short severity;		//wound severity
	char* message;
	char intial_blood_loss;
	char tick_blood_loss;
} WOUND;

#define DEF_WOUND(x,y)	x,y
	//OnStart##x##y,OnTick##x##y		//helper
extern WOUND Wounds[MaxType][MaxSeverity];

extern bool CheckWounds();
