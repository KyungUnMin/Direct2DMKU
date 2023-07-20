#include "PrecompileHeader.h"
#include "PhoneState_Weapon.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "KeyMgr.h"
#include "RCGEnums.h"
#include "SoundMgr.h"
#include "DataMgr.h"

#include "HandPhoneUI.h"


const std::vector<float4> PhoneState_Weapon::CursorPoses
{
	{-88.f, -33.f},	{-28.f, -33.f},	{32.f, -33.f},		{92.f, -33.f},
	{-88.f, -97.f},	{-28.f, -97.f},	{32.f, -97.f},		{92.f, -97.f},
};

bool PhoneState_Weapon::IsEquipKnuckle = false;
bool PhoneState_Weapon::IsEquipWatch = false;

int PhoneState_Weapon::KnuckleDamage = 50;

PhoneState_Weapon::PhoneState_Weapon()
{

}

PhoneState_Weapon::~PhoneState_Weapon()
{

}


void PhoneState_Weapon::Start() 
{
	PhoneStateBase::Start();

	Cursor = PhoneStateBase::CreateRender("HandPhone_Weapone_Cursor.png");

	Info_Knuckle = PhoneStateBase::CreateRender("HandPhone_Weapon_KnuckleInfo.png");
	Info_Watch = PhoneStateBase::CreateRender("HandPhone_Weapon_WatchInfo.png");

	Equip_Knuckle = PhoneStateBase::CreateRender("HandPhone_Weapon_SelectKnuckle.png");
	Equip_Watch = PhoneStateBase::CreateRender("HandPhone_Weapon_SelectWatch.png");

	Equip_All = PhoneStateBase::CreateRender("HandPhone_Weapon_SelectAll.png");
	Equip_Nothing = PhoneStateBase::CreateRender("HandPhone_Weapon_SelectNon.png");
}


void PhoneState_Weapon::EnterState() 
{
	PhoneStateBase::EnterState();

	GetPhone()->ChangePhoneTexture("HandPhone_Weapon_BackGround.png");
	
	PhoneStateType PrevUserState = GetPrevUserState();
	if (PhoneStateType::Inventory == PrevUserState)
	{
		NowCursorIndex = 0;
	}
	else if (PhoneStateType::Skill == PrevUserState)
	{
		NowCursorIndex = 3;
	}


	//NowCursorIndex = 0;
	PhoneStateType LastUserState = GetPhoneFSM()->GetLastUserState();
	if (PhoneStateType::Skill == LastUserState)
	{
		NowCursorIndex = 3;
	}

	Cursor->On();
	SelectEquipRender();
	MoveCursorRender();
}



void PhoneState_Weapon::SelectEquipRender()
{
	Equip_Knuckle->Off();
	Equip_Watch->Off();
	Equip_All->Off();
	Equip_Nothing->Off();

	//��� ��� �� ������ ���
	if (true == IsEquipKnuckle && true == IsEquipWatch)
	{
		Equip_All->On();
	}

	//��Ŭ�� ������ ���
	else if (true == IsEquipKnuckle)
	{
		Equip_Knuckle->On();
	}

	//�ð踸 ������ ���
	else if (true == IsEquipWatch)
	{
		Equip_Watch->On();
	}

	//�ƹ��͵� �� ������ ���
	else
	{
		Equip_Nothing->On();
	}
}



void PhoneState_Weapon::MoveCursorRender()
{
	//Ŀ�� ��ġ �̵�
	GameEngineTransform* CursorTrans = Cursor->GetTransform();
	const float4& CursorPos = CursorPoses[NowCursorIndex];
	CursorTrans->SetLocalPosition(CursorPos);

	//Ŀ���� ���� ȭ�� �ϴ� ��� ����â ����
	Info_Knuckle->Off();
	Info_Watch->Off();

	if (0 == NowCursorIndex)
	{
		Info_Knuckle->On();
	}
	else if (1 == NowCursorIndex)
	{
		Info_Watch->On();
	}
}





void PhoneState_Weapon::Update(float _DeltaTime)
{
	PhoneStateBase::Update(0.f);

	//ESC�� �������� Close�� ����
	if (true == KeyMgr::IsDown(KeyNames::Esc))
	{
		GetPhoneFSM()->ChangeState(PhoneStateType::Close);
		return;
	}

	if (true == Update_Equip())
		return;

	Update_MoveCursor();
}


bool PhoneState_Weapon::Update_Equip()
{
	bool IsEquip = false;
	IsEquip |= KeyMgr::IsDown(KeyNames::Z);
	IsEquip |= KeyMgr::IsDown(KeyNames::X);
	IsEquip |= KeyMgr::IsDown(KeyNames::C);
	
	//�ƹ� �ϵ� �Ͼ�� ����
	if (false == IsEquip)
		return false;

	std::string_view SoundName = "";
	if (0 == NowCursorIndex)
	{
		IsEquipKnuckle = !IsEquipKnuckle;
		if (true == IsEquipKnuckle)
		{
			SoundName = "Phone_Weapon_Equip.wav";
			DataMgr::PlusPlayerAtt(KnuckleDamage);
		}
		else
		{
			SoundName = "Phone_Weapon_UnEquip.wav";
			DataMgr::MinusPlayerAtt(KnuckleDamage);
		}
	}

	else if (1 == NowCursorIndex)
	{
		IsEquipWatch = !IsEquipWatch;
		DataMgr::IsUnbeatable = IsEquipWatch;
		SoundName = IsEquipWatch ? "Phone_Weapon_Equip.wav" : "Phone_Weapon_UnEquip.wav";
	}

	//Ŀ���� 0�� 1��°�� �ִ� ���� �ƴϸ� �ƹ��ϵ� ���� ����
	else
		return false;

	SelectEquipRender();
	SoundMgr::PlaySFX(SoundName);
	return true;
}





void PhoneState_Weapon::Update_MoveCursor()
{
	bool IsMove = false;

	//������ Ű�� �������
	if (true == KeyMgr::IsDown(KeyNames::RightArrow))
	{
		//Ŀ���� ���� �����ʿ� �ִ� ���
		if (3 == NowCursorIndex || 7 == NowCursorIndex)
		{
			SoundMgr::PlaySFX("Phone_ChangeUserState.wav");
			GetPhoneFSM()->ChangeState(PhoneStateType::Skill);
			return;
		}

		++NowCursorIndex;
		IsMove = true;
	}

	//���� Ű�� ���� ���
	else if (true == KeyMgr::IsDown(KeyNames::LeftArrow))
	{
		//Ŀ���� ���� ���ʿ� �ִ� ���
		if (0 == NowCursorIndex || 4 == NowCursorIndex)
		{
			SoundMgr::PlaySFX("Phone_ChangeUserState.wav");
			GetPhoneFSM()->ChangeState(PhoneStateType::Inventory);
			return;
		}

		--NowCursorIndex;
		IsMove = true;
	}

	//���� Ű�� ���� ���
	else if (true == KeyMgr::IsDown(KeyNames::UpArrow))
	{
		//Ŀ���� ���ʿ� �ִ� ��� �Ʒ������� �̵�
		if (NowCursorIndex < 4)
		{
			NowCursorIndex = NowCursorIndex + 4;
		}
		//Ŀ���� �Ʒ��ʿ� �ִ� ��� �������� �̵�
		else
		{
			NowCursorIndex = NowCursorIndex - 4;
		}

		IsMove = true;
	}

	//�Ʒ��� Ű�� ���� ���
	else if (true == KeyMgr::IsDown(KeyNames::DownArrow))
	{
		//Ŀ���� ���ʿ� �ִ� ���
		if (NowCursorIndex < 4)
		{
			NowCursorIndex = NowCursorIndex + 4;
		}
		//Ŀ���� �Ʒ��ʿ� �ִ� ���
		else
		{
			NowCursorIndex = NowCursorIndex - 4;
		}

		IsMove = true;
	}

	if (false == IsMove)
		return;

	//Ŀ�� ��ġ �̵�
	MoveCursorRender();

	if (0 == NowCursorIndex || 1 == NowCursorIndex)
	{
		SoundMgr::PlaySFX("Phone_Weapon_MoveCursor.wav").SetVolume(0.5f);
	}
	else
	{
		SoundMgr::PlaySFX("Phone_Weapon_MoveCursor_Empty.wav");
	}
}

void PhoneState_Weapon::ExitState()
{
	PhoneStateBase::ExitState();

	PhoneStateType NextState = GetFSM()->GetNowState<PhoneStateType>();
	if (false == IsUserState(NextState))
		return;
		
	Cursor->Off();
	Info_Knuckle->Off();
	Info_Watch->Off();
	Equip_Knuckle->Off();
	Equip_Watch->Off();
	Equip_All->Off();
	Equip_Nothing->Off();
}

