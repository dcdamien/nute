#if 0
void AnestheticsCure_t::OnUse(void) const
{
//	�������� ������� ��������.

	//CureDuration = 20
	//Reduce PAIN_LEVEL 1
/*
"� ��������� � ��������� ��������� ������,
�������� ������� �������� � ��������� �������
�������� ���������� ����������� ������� � ������������.
������� ���� 2 (�� ��������� ��������������)."
*/
}

void AnestheticsCure_t::OnTick(void) const
{
}

void AntispasmodicCure_t::OnUse(void) const
{
//	���������� ����� �����������, �������������� �����, ����� � �������.

	//CureDuration = ?
	//Reg 1: "��������� ����� � �����, ������������� ������, �������� � �����.
//				��������������� ������ ��������, ""���������"" �� ���� �������."
	//Reg 2: "��������� ����� � �����, ������������� ������, �������� � �����, �������� ��������������� ������ ��������."
	//Reg 3: "��������� ����� � �����, ������������� ������ �������� � �����"
/*
�������� ����, ������� ����: 1
*/
}

void AntispasmodicCure_t::OnTick(void) const
{
}

void PyreticCure_t::OnUse(void) const
{
//	��������� ����, ���������� ��������.

	//������� ���, ��������� ��������, �������� ����������.
/*
"� ��������� � ��������� ������� � �������� ������������ ���������� �������� �������� �������� ������ � ������.
������. � ��������� � ������ ��������� � ������� ��������, �������� ����� ��� �������.
"
*/
}

void PyreticCure_t::OnTick(void) const
{
}

void AspiratorCure_t::OnUse(void) const
{
//	����������� ������� ��� ������� ���������� �������.

	//������������ ������� �������� � ������� 10 �����.
/*
������� ���� ��� ����� � ������, ������������� �������� �����.
*/
}

void AspiratorCure_t::OnTick(void) const
{
}

void CoagulationFactorCure_t::OnUse(void) const
{
//	������������ �����������

//	Reg 1: �����: ����������� ������������
	//Reg 2: "����������: +5 ��. ����� �����: ����������� ������������"
	//Reg 3: "����������: +10 ��. ����� �����: + 1 ��. ����� � ������"
/*
"� ��������� � ��������� ��������� ������ � ����� �������� ������� ���� �� 1.
��� ���������� �� ������ � ������������ ��������� ��������� ������� � ��������� ��������� (��������� 1 ��� �� �������).
"
*/
}

void CoagulationFactorCure_t::OnTick(void) const
{
}

void SyntheticBloodCure_t::OnUse(void) const
{
	//�������������� ������ �����

	//Reg 1: "����������: +10 ��. �����
	//Reg 2: "	"����������: +20 ��. �����
	//Reg 3: "	"����������: +30 ��. �����
/*
������������� ������� ��������� � ���������� ��������� (��������� 1 ��� �� �������).
"	����� (��������� ����� ������ � �����), ���.
*/
}

void SyntheticBloodCure_t::OnTick(void) const
{
}

void LeatheretteCure_t::OnUse(void) const
{
	//������� ������

	//Reg 1: "�������� ������� ���� �� 1 + 5 ��. �����"
	//Reg 2: 	"�������� ������� ���� �� 1 + 10 ��. �����"
	//Reg 3: 	"�������� ������� ���� �� 1 + 10 ��. ����� ���� ��������� � ���������� ��������� (��������� 1 ��� �� �������)"
/*
�� ����������� � ��������� � ���� �������.
*/
}

void LeatheretteCure_t::OnTick(void) const
{
}

void MyorelaxantCure_t::OnUse(void) const
{
	//����������� �������, ������������ ���� ������� ������� �������� �������.

	//������� "�����������" �� ���� �������, �������� � ����� ������������.
/*
"������ ����� 5 ��.
������ ��������� � �������� � ������ (��������� ������� � ��������� ������������).
������ ��������� � �������� � ����������� ����� (��������� ������� � ��������� ������������).
��� ������������� ������ ��� ����� 10 ����� ����� ������������ ��������� ����� ������� � ��������� ���������."
*/
}

void MyorelaxantCure_t::OnTick(void) const
{
}

void VisceraNanoPackCure_t::OnUse(void) const
{
	//"��������� ��� ������� ������ � �������� ��������� 2 � ����.
	//����� ������������ ��� ������� ���������� ���������� � �����."
/*
Reg1:
"��������� ������������ ��� ������� ���� �� 1 ��������� �� 20 ����� �� ������� ���������.
���������� ����������� ��� ������������� ��������."

Reg2:
"��������� ������������ ��� ������� ���� �� 1 ��������� �� 15 ����� �� ������� ���������.
�������� ������� ���� �� 1.
���������� ����������� ��� ������������� ��������."

Reg3:
"��������� ������������ ��� ������� ���� �� 1 ��������� �� 10 ����� �� ������� ���������.
���������� ����������� ��� ������������� ��������.
�������� ������� ���� �� 1
+ 3 ��. ����� � ������ �� ������� ��������������.
"

"�������� ����� � ���� �� ���� ����, ������� ����� (��������� ����� ������ � �����).
�� ��������� � �������� � ���� �������.
� ���� ��������� � ������������ �������, �������� ������� ���������� � ��������� ������� � ��������� ���������.
"
*/
}

void VisceraNanoPackCure_tOnTick(void)
{
}

/*void RespiratoryNanoPackCure_t::OnUse(void) const
{

	��������� ��� ������� ������� ����������� � ���������� ����� ������� ���������.

	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 20 ����� �� ������� ���������.
	���������� ���� � ������ ��� 1 � 2 ���������� �������."

	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 15 ����� �� ������� ���������.
	�������� ������� ���� �� 1.
	���������� ���� � ������ ��� 1 � 2 ���������� �������."

	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 10 ����� �� ������� ���������.
	���������� ���� � ������ ��� 1 � 2 ���������� �������.
	�������� ������� ���� �� 1
	+ 3 ��. ����� � ������ �� ������� ��������������.

"�������� ����� � ���� �� ���� ����, ������� ����� (��������� ����� ������ � �����).
�� ��������� � �������� � ���� �������.
� ���� ��������� � ������������ �������, �������� ������� ���������� � ��������� ������� � ��������� ���������.
"
}
*/

}//namespace

/*
��� ������������ ��� ���������� �������.	"��������� ��� ������� ������ � �������� ��������� 2 � ����.
����� ������������ ��� ������� ���������� ���������� � �����."	"��������� ������������ ��� ������� ���� �� 1 ��������� �� 20 ����� �� ������� ���������.
���������� ����������� ��� ������������� ��������."	"��������� ������������ ��� ������� ���� �� 1 ��������� �� 15 ����� �� ������� ���������.
�������� ������� ���� �� 1.
���������� ����������� ��� ������������� ��������."	"��������� ������������ ��� ������� ���� �� 1 ��������� �� 10 ����� �� ������� ���������.
���������� ����������� ��� ������������� ��������.
�������� ������� ���� �� 1
+ 3 ��. ����� � ������ �� ������� ��������������.
"	"�������� ����� � ���� �� ���� ����, ������� ����� (��������� ����� ������ � �����).
�� ��������� � �������� � ���� �������.
� ���� ��������� � ������������ �������, �������� ������� ���������� � ��������� ������� � ��������� ���������.
"
��� ����������� ������������	��������� ��� ������� ������� ����������� � ���������� ����� ������� ���������.	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 20 ����� �� ������� ���������.
���������� ���� � ������ ��� 1 � 2 ���������� �������."	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 15 ����� �� ������� ���������.
�������� ������� ���� �� 1.
���������� ���� � ������ ��� 1 � 2 ���������� �������."	"��������� ������� ����������� ��� ��������� ����� �� 1 ��������� �� 10 ����� �� ������� ���������.
���������� ���� � ������ ��� 1 � 2 ���������� �������.
�������� ������� ���� �� 1
+ 3 ��. ����� � ������ �� ������� ��������������.
"	"�������� ����� � ���� �� ���� ����, ������� ����� (��������� ����� ������ � �����).
�� ��������� � �������� � ���� �������.
� ���� ��������� � ������������ �������, �������� ������� ���������� � ��������� ������� � ��������� ���������.
"
*/

//Anesthetics_CureEffect
//Anesthetics_SideEffect

/*
CURES:
name, function, action (3 per regeneration level), side effects

""

�������� ������� ���� �� 1
�������� ������� ���� �� 1
�������� ������� ���� �� 1
"� ��������� � ��������� ��������� ������, �������� ������� �������� � ���������
������� �������� ���������� ����������� ������� � ������������.
������� ���� 2 (�� ��������� ��������������)."
�����
*/

/*
FEELING FACTORS:
(aka SYMPTOMS:
	name, brief description, description for patient
PAIN		(1-3)
SPECIFIC_PAIN (1-3)	//"������� ����, ��������� ����, �������"
COUGH		(1-2)	//"������/�������" "������"
CONVULTION	(1-2)	//"������/�������" "��������"
WHEEZE		(1-2)	//"������/�������" "����"
FEVER		(1)		//"���"
UNCONSCIOUS (1)		//"��� ��������"
DELIRIUM	(1)		//"����"
CONFUSION	(1)		//"�������� �������"
VISUAL HALLUTINATIONS "���������� ������������"
DISRUPTED PERCEPTION "���������� ��������"
nausea				//"�������"
retching			//"�����"
cannot breathe		//"������� �� ����� ������"
Impaired fine motor skills //"������ �������� ��������"
BOXER_POSE			//"���� �������"
VERTIGO				//"��������������"
*/
}

void OnUseAnesthetics()
{
	//PainLevel -= 1;
/*
	if (
		(Body.Wounds[HEAD_SHOT]==Insidious)||
		(Body.Wounds[KNOCKOUT]==Insidious)
		)
	{
		//SPECIFIC_PAIN[�������]
	}
*/

	//Head
/*
"� ��������� � ��������� ��������� ������, �������� ������� �������� � ��������� ������� �������� ���������� ����������� ������� � ������������.
������� ���� 2 (�� ��������� ��������������)."
*/
}
#endif