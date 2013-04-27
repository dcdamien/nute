#pragma once
#ifndef _MED_
	#error _MED_
#endif

//CURE ids:
typedef enum _CURE_ID {
	UnknownCure = -1,
	Anesthetics = 0,		//"����� ��������������"
	Antispasmodic,			//"�����������"
	Pyretic,				//"��������������"
	Aspirator,				//"���������"
	CoagulationFactor,		//"������ �������������� �����"
	SyntheticBlood,			//"������������� �����"
	Leatherette,			//"������������� ����"
	Myorelaxant,			//"������������"
	VisceraNanoPack,		//"��� ������������ ��� ���������� �������"
	RespiratoryNanoPack,	//"��� ����������� ������������"
	MaxCureId
} CURE_ID;

class Cure_t {
public:
	//static members
	static CURE_ID const id = UnknownCure;
	//static members as inline getters
	static inline char const*const CureName(void);					//cure name
	static inline char const*const CurePurpose(void);				//cure purpose description
	static inline char const*const CureEffect(void);				//cure healing effect description
	static inline char const*const CureContraindications(void);		//cure contraindications description
	static inline char const*const CureSideEffects(void);			//cure side effects description
	//methods
	virtual void OnUse(void) const {};								//cure effect on first use
	virtual void OnTick(void) const {};								//cure effect on each tick
	virtual ~Cure_t(void) {return;}									//empty virtual destructor is required
};

extern inline Cure_t const*const GetCureById(CURE_ID id);
//DBG only
extern bool CheckCures();
