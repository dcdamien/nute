#pragma once
#ifndef _MED_
	#error _MED_
#endif

// When this list updated, update server list 
// /Armlet/Armlet3/BastiliaGate_sw/Server/HonorLogic/Pills.cs

//CURE ids:
typedef enum _CURE_ID {
	UnknownCure = -1,
	Analgetic = 0,			//"����� �������������� - ����������" 
	Antispasmodic = 1,		//"�����������"
	Pyretic = 2,			//"��������������"
	Aspirator =3,			//"���������"
	CoagulationFactor =4,	//"������ �������������� �����"
	SyntheticBlood =5,		//"������������� �����"
	Leatherette =6,			//"������������� ����"
	Myorelaxant =7,			//"������������"
	VisceraNanoPack =8,		//"��� ������������ ��� ���������� �������" => "������� ��������� ������"
//	RespiratoryNanoPack,	//"��� ����������� ������������"
//more
	Anesthetics =9,			//"������� ������"		?
	Antibiotic =10,			//"����������"			���. �����
	Absorber =11,			//"���������"			���. �����
	PlasterNanoPack =12,	//"��������"			���. �����
	NanoExoFrame =13,		//"��������������"		1-2 �����������. �������
	MagicCure =14,			//"��������� ��������"	����������
	MaxCureId = 15
} CURE_ID;

class Cure_t {
public:
	//static members
	static CURE_ID const id = UnknownCure;
	//static members as inline getters
	static inline const char* CureName(void);					//cure name
	static inline const char* CurePurpose(void);				//cure purpose description
	static inline const char* CureEffect(void);				//cure healing effect description
	static inline const char* CureContraindications(void);		//cure contraindications description
	static inline const char* CureSideEffects(void);			//cure side effects description
	//methods
	virtual void OnUse(void) const {};								//cure effect on first use
	virtual void OnTick(void) const {};								//cure effect on each tick
	virtual ~Cure_t(void) {return;}									//empty virtual destructor is required
};

extern inline const Cure_t* GetCureById(CURE_ID id);
//DBG only
extern bool CheckCures();

typedef struct _CURE_DESC {
	//CURE_ID const id;					//cure id
	const int id;
	const char* Name;				//cure name
	const char* Purpose;			//cure purpose description
	const char* Effect;			//cure effect description
	const char* Contraindications;	//cure contraindications description
	const char* SideEffects;		//cure side effects description
} CURE_DESC;

extern const CURE_DESC CureDesc[MaxCureId];
