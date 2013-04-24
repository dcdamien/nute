namespace price_of_honor_test {

#define COMPILE_TIME_CHECK(e) extern char _COMPILE_TIME_CHECK_[(e)?1:-1]

//CURE ids:
typedef enum _CURE_ID {
	Unknown = -1,
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

const class Cure_t {
public:
	static CURE_ID const id = Unknown;
	inline virtual const CURE_ID GetCureId(void) const {return Unknown;}	//cure id
	//members as inline methods
	inline char const*const GetCureName(void) const;				//cure name
	inline char const*const GetCurePurpose(void) const;				//cure purpose description
	inline char const*const GetCureEffect(void) const;				//cure healing effect description
	inline char const*const GetCureContraindications(void) const;	//cure contraindications description
	inline char const*const GetCureSideEffects(void) const;			//cure side effects description
	//methods
	virtual void OnUse() const;										//cure effect on first use
	virtual void OnTick() const;									//cure effect on each tick
};

#define DECLARE_CURE(x)	\
	class x##Cure_t : public Cure_t { \
		static CURE_ID const id = x; \
		inline virtual const CURE_ID GetCureId(void) const {return x;} \
	}

DECLARE_CURE(Anesthetics);
DECLARE_CURE(Antispasmodic);
DECLARE_CURE(Pyretic);
DECLARE_CURE(Aspirator);
DECLARE_CURE(CoagulationFactor);
DECLARE_CURE(SyntheticBlood);
DECLARE_CURE(Leatherette);
DECLARE_CURE(Myorelaxant);
DECLARE_CURE(VisceraNanoPack);
DECLARE_CURE(RespiratoryNanoPack);

//extern inline const Cure_t* const GetCureById(CURE_ID id);
//DBG only
extern bool CheckCures();

typedef struct _CureStrings_t {
	const CURE_ID id;			//cure id
	const char* const name;		//cure name
	const char* const purpose;	//cure purpose description
	const char* const effect;	//cure effect description
	const char* const contra;	//cure contraindications description
	const char* const side;		//cure side effects description
} CureStrings_t;

const CureStrings_t CureStrings[MaxCureId] = 
{
	{
		Anesthetics,
		"����� ��������������",
		"�������� ������� ��������",
		"�������� ������� ���� �� 1",
		"�������� �������",
		"�������, ������������ � ������� ���� 2 (�� ��������� ��������������)"
	},
	{
		Antispasmodic,
		"�����������",
		"���������� ����� �����������, �������������� �����, ����� � �������",
		"��������� ����� � �����, ������������� ������, �������� � �����."
			"����� ������������ ������ �������� � '���������' �� ���� �������", //regeneration based
		"��� ����������������",
		"�������� ����, ������� ���� 1"
	},
	{
		Pyretic,
		"��������������",
		"��������� ����, ���������� ��������",
		"������� ���, ��������� ��������, �������� ����������",
		"�������� �����, �������� ��������, ������",
		"�������� �������� ������ � ������, �������� �����, �����"
	},
	{
		Aspirator,
		"���������",
		"����������� �������",
		"������������ ������� �������� � ������� 10 �����",
		"��� ����������������",
		"������� �����, ������ ������"
	},
	{
		CoagulationFactor,
		"������ �������������� �����",
		"������������ �����������",
		"����������� ������������. ����������� ����� �����.", //regeneration based
		"��� ����������������",
		"��� �������� �������� ������ � ����� �������� ������� ���� �� 1"
		"��� ���������� �� ������ � ������������ ��������� ��������� ������� � ��������� ��������� (��������� 1 ��� �� �������)"

	},
	{
		SyntheticBlood,
		"������������� �����",
		"�������������� ������ �����",
		"����������� ����� �����. ���������� ������������� �������", //regeneration based
		"��� ����������������",
		"�����, ���"
	},
	{
		Leatherette,
		"������������� ����",
		"������� ������",
		"�������� ������� ����, ��������������� ����� �����, ��������� ����", //regeneration based
		"���� �������",
		"���"
	},
	{
		Myorelaxant,
		"������������",
		"����������� �������, ������������ ���� �������",
		"'���������' �� ���� �������, �������� � ����� ������������",
		"�����, ������������� ������� �����",
		"������ �����, ������ ��� �����������������, ��������� �� ������������� �������� �������"
	},
	{
		VisceraNanoPack,
		"��� ������������ ��� ���������� �������",
		"������� ������ � ��������",
		"",
		"",
		""
	},
	{
		RespiratoryNanoPack,
		"��� ����������� ������������",
		"������� ������� ����������� � ������������� ������� �����",
		"",
		"",
		""
	}
};
COMPILE_TIME_CHECK(sizeof(CureStrings)/sizeof(CureStrings_t)==MaxCureId);

#define DEFINE_CURE1(x)	const x##Cure_t x##Cure
#define DEFINE_CURE2(x)	&x##Cure
//#define DEFINE_CURE2(x)	(Cure_t*)&x##Cure
//#define DEFINE_CURE2(x)	dynamic_cast<Cure_t*>(&x##Cure)

DEFINE_CURE1(Anesthetics);
DEFINE_CURE1(Antispasmodic);
DEFINE_CURE1(Pyretic);
DEFINE_CURE1(Aspirator);
DEFINE_CURE1(CoagulationFactor);
DEFINE_CURE1(SyntheticBlood);
DEFINE_CURE1(Leatherette);
DEFINE_CURE1(Myorelaxant);
DEFINE_CURE1(VisceraNanoPack);
DEFINE_CURE1(RespiratoryNanoPack);

Cure_t const*const Cures[MaxCureId] = {
	DEFINE_CURE2(Anesthetics),
	DEFINE_CURE2(Antispasmodic),
	DEFINE_CURE2(Pyretic),
	DEFINE_CURE2(Aspirator),
	DEFINE_CURE2(CoagulationFactor),
	DEFINE_CURE2(SyntheticBlood),
	DEFINE_CURE2(Leatherette),
	DEFINE_CURE2(Myorelaxant),
	DEFINE_CURE2(VisceraNanoPack),
	DEFINE_CURE2(RespiratoryNanoPack)
};

inline const Cure_t* const GetCureById(CURE_ID id)
{
	return Cures[id];
}

typedef const Cure_t* const PCure_t;
//TODO DBG
bool CheckCures()
{
	for (int i=0; i<MaxCureId; i++) 
	{
		PCure_t obj = GetCureById((CURE_ID)i);
		CURE_ID j = obj->GetCureId();
		if (obj->GetCureId() != i) goto out;
	}
	return true;
out:
	return false;
}

inline const char* const Cure_t::GetCureName(void) const				{return CureStrings[GetCureId()].name;}
inline const char* const Cure_t::GetCurePurpose(void) const				{return CureStrings[GetCureId()].purpose;}
inline const char* const Cure_t::GetCureEffect(void) const				{return CureStrings[GetCureId()].effect;}
inline const char* const Cure_t::GetCureContraindications(void) const	{return CureStrings[GetCureId()].contra;}
inline const char* const Cure_t::GetCureSideEffects(void) const			{return CureStrings[GetCureId()].side;}

void Cure_t::OnUse() const
{
}

void Cure_t::OnTick() const
{
}

}//namespace
