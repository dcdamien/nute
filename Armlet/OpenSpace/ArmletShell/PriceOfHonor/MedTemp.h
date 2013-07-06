//WOUND severity:
typedef enum _WOUND_SEVERITY {
	NoWound = -1,		//"��� �������"
	GrazeWound = 0,		//"��������"
	LightWound,			//"���������"
	SeriousWoundWound,		//"�������"
	InsidiousWoundWound,		//"��������"
	CriticalWoundWound,		//"�����������"
	MaxSeverity
} WOUND_SEVERITY;

//DAMAGE types:DAMAGE_TYPE {
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
} DAMAGE_TYPE;



typedef struct _WOUND {
	DAMAGE_TYPE type;			//damage type
	WOUND_SEVERITY severity;	//wound severity
	char* message1;
	char* message2;
	char intial_blood_loss;
	char tick_blood_loss;
	char duration;
	char severity_after_duration;
	char severity_on_next_hit;
	char severity_on_healing; //����������
} WOUND;

#define DEF_WOUND(x,y)	x,y

WOUND Wounds[MaxType][MaxSeverity] = 
{
	{//LeftArmShot
		{
			DEF_WOUND(LeftArmShot,NoWound),
			"",
			0,0,INFINITE,NoWound,RandomSelect,NoWound
		},
		{
			DEF_WOUND(LeftArmShot,GrazeWound),
			"���� ������� ����� ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
			"(�������� ����������) �����. [1]",
			5,0,25-Reg*5,NoWound,SeriousWound,NoWound
		},
		{
			DEF_WOUND(LeftArmShot,LightWound),
			"���� ������� ����� ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������.",
			"(�������� ����������) �����. [1]",
			8,1
		},
		{
			DEF_WOUND(LeftArmShot,SeriousWound),
			"���� ������� ����� ���� ��� �����. ������, ������� ���������, ����� ��� � �����",
			"(�������� ����������) ������ ����� [2]. �� ������ ������������ (�������� ����������)",
			20,5
		},
		{
			DEF_WOUND(LeftArmShot,InsidiousWound),
			"���� ������� ����� ���� ��� �����. ��������-���� ������, �� ������ ������ ������� �� ������",
			"������",
			10,1
		},
		{
			DEF_WOUND(LeftArmShot,CriticalWound),
			"���� �������� ������ � ����� ����. ����� �����! ����� ������!",
			"(�������� ����������) ����� ������ ����� [3]. ��������� � ������, ����������� �����."
				"�� ������ ������������ (�������� ����������)"
			50,10
		},
	},
	{//RightArmShot
		{
			DEF_WOUND(RightArmShot,NoWound),
			"",
			0,0
		},
		{
			DEF_WOUND(RightArmShot,GrazeWound),
			"",
			0,0
		},
		{
			DEF_WOUND(RightArmShot,LightWound),
			"",
			0,0
		},
		{
			DEF_WOUND(RightArmShot,SeriousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(RightArmShot,InsidiousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(RightArmShot,CriticalWound),
			"",
			0,0
		},
	},
	{//LeftLegShot
		{
			DEF_WOUND(LeftLegShot,NoWound),
			"",
			0,0
		},
		{
			DEF_WOUND(LeftLegShot,GrazeWound),
			"",
			0,0
		},
		{
			DEF_WOUND(LeftLegShot,LightWound),
			"",
			0,0
		},
		{
			DEF_WOUND(LeftLegShot,SeriousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(LeftLegShot,InsidiousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(LeftLegShot,CriticalWound),
			"",
			0,0
		},
	},
	{//RightLegShot
		{
			DEF_WOUND(RightLegShot,NoWound),
			"",
			0,0
		},
		{
			DEF_WOUND(RightLegShot,GrazeWound),
			"",
			0,0
		},
		{
			DEF_WOUND(RightLegShot,LightWound),
			"",
			0,0
		},
		{
			DEF_WOUND(RightLegShot,SeriousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(RightLegShot,InsidiousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(RightLegShot,CriticalWound),
			"",
			0,0
		},
	},
	{//ChestShot
		{
			DEF_WOUND(ChestShot,NoWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ChestShot,GrazeWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ChestShot,LightWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ChestShot,SeriousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ChestShot,InsidiousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ChestShot,CriticalWound),
			"",
			0,0
		},
	},
	{//AbdomenShot
		{
			DEF_WOUND(AbdomenShot,NoWound),
			"",
			0,0
		},
		{
			DEF_WOUND(AbdomenShot,GrazeWound),
			"",
			0,0
		},
		{
			DEF_WOUND(AbdomenShot,LightWound),
			"",
			0,0
		},
		{
			DEF_WOUND(AbdomenShot,SeriousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(AbdomenShot,InsidiousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(AbdomenShot,CriticalWound),
			"",
			0,0
		},
	},
	{//HeadShot
		{
			DEF_WOUND(HeadShot,NoWound),
			"",
			0,0
		},
		{
			DEF_WOUND(HeadShot,GrazeWound),
			"",
			0,0
		},
		{
			DEF_WOUND(HeadShot,LightWound),
			"",
			0,0
		},
		{
			DEF_WOUND(HeadShot,SeriousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(HeadShot,InsidiousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(HeadShot,CriticalWound),
			"",
			0,0
		},
	},
	{//KnockOut
		{
			DEF_WOUND(KnockOut,NoWound),
			"",
			0,0
		},
		{
			DEF_WOUND(KnockOut,GrazeWound),
			"",
			0,0
		},
		{
			DEF_WOUND(KnockOut,LightWound),
			"",
			0,0
		},
		{
			DEF_WOUND(KnockOut,SeriousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(KnockOut,InsidiousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(KnockOut,CriticalWound),
			"",
			0,0
		},
	},
	{//ExplosionBlast
		{
			DEF_WOUND(ExplosionBlast,NoWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionBlast,GrazeWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionBlast,LightWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionBlast,SeriousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionBlast,InsidiousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionBlast,CriticalWound),
			"",
			0,0
		},
	},
	{//ExplosionScorch
		{
			DEF_WOUND(ExplosionScorch,NoWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionScorch,GrazeWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionScorch,LightWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionScorch,SeriousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionScorch,InsidiousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionScorch,CriticalWound),
			"",
			0,0
		},
	},
	{//ExplosionRadiation
		{
			DEF_WOUND(ExplosionRadiation,NoWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionRadiation,GrazeWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionRadiation,LightWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionRadiation,SeriousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionRadiation,InsidiousWound),
			"",
			0,0
		},
		{
			DEF_WOUND(ExplosionRadiation,CriticalWound),
			"",
			0,0
		},
	}
};













//NAME (FirstName, LastName)
//BODY
	//STATE
	//blood
		RegenerationLevel: 1,2,3	//naming
		BloodLossLevel: 0..4		//naming
		BloodLoss: 0..10						=> provides regeneration if 0, cumulutive
		BloodCapacityLevel: 0..6	//naming	=> function to symptoms
		BloodCapacity: 0..200
	//...
	//WOUNDS
//SYMPTOMS
	������� ��������, �������� ������
	�������� ��������, ������ �������
	������ ������� ��������, �� ������ ������
	�������� ��������, ������������� 3
	����
	����� �������	��/���	������� ������, ���� �������� � ����� �����	�������	
	������������ �������	��/���	������		���������, ����� ���������������
	�������������	0..2	��������������� ������ ���������, ������ �������� ����		
	��������� ������ ��������	��/���	������� �� ���� �������� � ������		�������� �� �� ���� ������������ ������ ����
	�����	��/���	����� ����� ����		
	��������	��/���	�� ���� ������ ������ ��������		
	� ��������	��/���	�� ��� ���������		
	���� 1	�����������			����������� �������������� -1	
	���� 2	�����			����������� �������������� -2, ����������� ��� ���� 1 ��� ������������� -1	
	���� 3	������ �����			�� ����������� ��������������?	���������� ������������ ������ ����
	���� 4	������ ��������			?	
	������� ���	������������� ������������� (-1), ����� ����������� ��������� �������			�������� ����� X+Y*���. �����	
	�������					
	���������� ������������					
	���					
	�������+�����					
	������			������, �������		
	��������			������, �������		
	����� �������			�������������, ������, �������		
	��������� ����������			��������������, ���������� ��������, �������� �������, ����, ��� ��������		
	���� �������					
	������� �� ����� ������					
	������������
//CURES
//DAMAGES

					