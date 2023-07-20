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

	//모든 장비를 다 착용한 경우
	if (true == IsEquipKnuckle && true == IsEquipWatch)
	{
		Equip_All->On();
	}

	//너클만 착용한 경우
	else if (true == IsEquipKnuckle)
	{
		Equip_Knuckle->On();
	}

	//시계만 착용한 경우
	else if (true == IsEquipWatch)
	{
		Equip_Watch->On();
	}

	//아무것도 안 착용한 경우
	else
	{
		Equip_Nothing->On();
	}
}



void PhoneState_Weapon::MoveCursorRender()
{
	//커서 위치 이동
	GameEngineTransform* CursorTrans = Cursor->GetTransform();
	const float4& CursorPos = CursorPoses[NowCursorIndex];
	CursorTrans->SetLocalPosition(CursorPos);

	//커서에 따라 화면 하단 장비 설명창 변경
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

	//ESC를 눌렀을땐 Close로 변경
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
	
	//아무 일도 일어나지 않음
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

	//커서가 0과 1번째에 있던 것이 아니면 아무일도 하지 않음
	else
		return false;

	SelectEquipRender();
	SoundMgr::PlaySFX(SoundName);
	return true;
}





void PhoneState_Weapon::Update_MoveCursor()
{
	bool IsMove = false;

	//오른쪽 키를 누른경우
	if (true == KeyMgr::IsDown(KeyNames::RightArrow))
	{
		//커서가 가장 오른쪽에 있던 경우
		if (3 == NowCursorIndex || 7 == NowCursorIndex)
		{
			SoundMgr::PlaySFX("Phone_ChangeUserState.wav");
			GetPhoneFSM()->ChangeState(PhoneStateType::Skill);
			return;
		}

		++NowCursorIndex;
		IsMove = true;
	}

	//왼쪽 키를 누른 경우
	else if (true == KeyMgr::IsDown(KeyNames::LeftArrow))
	{
		//커서가 가장 왼쪽에 있던 경우
		if (0 == NowCursorIndex || 4 == NowCursorIndex)
		{
			SoundMgr::PlaySFX("Phone_ChangeUserState.wav");
			GetPhoneFSM()->ChangeState(PhoneStateType::Inventory);
			return;
		}

		--NowCursorIndex;
		IsMove = true;
	}

	//위쪽 키를 누른 경우
	else if (true == KeyMgr::IsDown(KeyNames::UpArrow))
	{
		//커서가 위쪽에 있던 경우 아래쪽으로 이동
		if (NowCursorIndex < 4)
		{
			NowCursorIndex = NowCursorIndex + 4;
		}
		//커서가 아래쪽에 있던 경우 위쪽으로 이동
		else
		{
			NowCursorIndex = NowCursorIndex - 4;
		}

		IsMove = true;
	}

	//아래쪽 키를 누른 경우
	else if (true == KeyMgr::IsDown(KeyNames::DownArrow))
	{
		//커서가 위쪽에 있던 경우
		if (NowCursorIndex < 4)
		{
			NowCursorIndex = NowCursorIndex + 4;
		}
		//커서가 아래쪽에 있던 경우
		else
		{
			NowCursorIndex = NowCursorIndex - 4;
		}

		IsMove = true;
	}

	if (false == IsMove)
		return;

	//커서 위치 이동
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

