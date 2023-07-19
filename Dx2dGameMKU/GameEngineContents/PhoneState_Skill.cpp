#include "PrecompileHeader.h"
#include "PhoneState_Skill.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "SkillMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

#include "HandPhoneUI.h"
#include "PlayerFSM.h"

#define CURSOR_MAX 4
#define CURSOR_MIN 0

#define INFO_MAX 7
#define INFO_MIN 0
#define INFO_RANGE 5

const std::string_view PhoneState_Skill::UnknownSkillTexName = "HandPhone_Skill_Unknown.png";

const std::vector<std::pair<std::string_view, PlayerStateType>> PhoneState_Skill::SkillInfoTexNames =
{
	{"HandPhone_Skill_Chop.png", PlayerStateType::QuickAttack_Chop},
	{"HandPhone_Skill_SnapKick.png", PlayerStateType::QuickAttack_SnapKick},
	{"HandPhone_Skill_BackKick.png", PlayerStateType::QuickAttack_BackKick},
	{"HandPhone_Skill_CrescentKick.png", PlayerStateType::QuickAttack_CrescentKick},
	{"HandPhone_Skill_HookKick.png", PlayerStateType::QuickAttack_HookKick},

	{"HandPhone_Skill_AxeKick.png", PlayerStateType::SpecialAttack_AxeKick},
	{"HandPhone_Skill_DAP.png", PlayerStateType::SpecialAttack_DAP},
	{"HandPhone_Skill_DonkeyKick.png", PlayerStateType::SpecialAttack_DonkeyKick},

	{"HandPhone_Skill_DragonKick.png", PlayerStateType::UniqueAttack_DragonFeet},
	{"HandPhone_Skill_HyrricaneKick.png", PlayerStateType::UniqueAttack_HyrricaneKick},

	{"HandPhone_Skill_BackElbow.png", PlayerStateType::DashAttack_BackElbow},
	{"HandPhone_Skill_DropKick.png", PlayerStateType::DashAttack_DropKick},
};




const std::vector<float4> PhoneState_Skill::Positions =
{
	{0.f, 97.f, 0.f},
	{0.f, 29.f, 0.f},
	{0.f, -36.f, 0.f},
	{0.f, -102.f, 0.f},
	{0.f, -169.f, 0.f},
};

GameEngineTime PhoneState_Skill::Time;


PhoneState_Skill::PhoneState_Skill()
{

}

PhoneState_Skill::~PhoneState_Skill()
{

}




void PhoneState_Skill::Start() 
{
	PhoneStateBase::Start();

	//Ŀ�� ����
	CursorRender = PhoneStateBase::CreateRender("HandPhone_Skill_Cursor.png");

	//Ŀ�� ��ġ ���� ��ŭ ��ų ������ ǥ���� ���� ����
	SkillInfoRenders.resize(Positions.size(), nullptr);
	for (size_t i = 0; i < SkillInfoRenders.size(); ++i)
	{
		SkillInfoRenders[i] = PhoneStateBase::CreateRender();
		SkillInfoRenders[i]->GetTransform()->SetLocalPosition(Positions[i]);
	}
}



void PhoneState_Skill::EnterState() 
{
	PhoneStateBase::EnterState();

	GetPhone()->ChangePhoneTexture("HandPhone_Skill_BackGround.png");

	//CursorIndex = 0;
	//InfoIndex = 0;

	SettingCursorRender();
	SettingInfoRender();
	
	CursorRender->On();
	for (size_t i = 0; i < SkillInfoRenders.size(); ++i)
	{
		SkillInfoRenders[i]->On();
	}

	Time.Reset();
}

void PhoneState_Skill::SettingCursorRender() 
{
	if (CURSOR_MAX < CursorIndex)
	{
		MsgAssert("Ŀ�� �ε����� �ִ�ũ��� 4�Դϴ�.\n�̵��Ϸ��� Ŀ�� : " + GameEngineString::ToString(static_cast<int>(CursorIndex)));
		return;
	}

	CursorRender->GetTransform()->SetLocalPosition(Positions[CursorIndex]);
}


void PhoneState_Skill::SettingInfoRender()
{
	const size_t Dest = (InfoIndex + INFO_RANGE);
	if (SkillInfoTexNames.size() < Dest)
	{
		MsgAssert("��ų ���� �ε����� ������ �ʰ��Ͽ����ϴ�");
		return;
	}

	for (size_t i = InfoIndex; i < Dest; ++i)
	{
		size_t PosIndex = (i - InfoIndex);
		PlayerStateType SkillType = SkillInfoTexNames[i].second;
		std::string_view SkillTexName = SkillInfoTexNames[i].first;

		if (false == SkillMgr::HasSkill(SkillType))
		{
			SkillTexName = UnknownSkillTexName;
		}
		
		SkillInfoRenders[PosIndex]->SetScaleToTexture(SkillTexName);
	}
}




void PhoneState_Skill::Update(float _DeltaTime) 
{
	PhoneStateBase::Update(0.f);

	//ESC�� �������� Close�� ����
	if (true == KeyMgr::IsDown(KeyNames::Esc))
	{
		GetPhoneFSM()->ChangeState(PhoneStateType::Close);
		return;
	}

	if (true == Update_HorizonArrow())
		return;

	Update_VerticalArrow();
}


bool PhoneState_Skill::Update_HorizonArrow()
{
	if (true == KeyMgr::IsDown(KeyNames::RightArrow))
	{
		SoundMgr::PlaySFX("Phone_ChangeUserState.wav");
		GetPhoneFSM()->ChangeState(PhoneStateType::Inventory);
		return true;
	}

	if (true == KeyMgr::IsDown(KeyNames::LeftArrow))
	{
		SoundMgr::PlaySFX("Phone_ChangeUserState.wav");
		GetPhoneFSM()->ChangeState(PhoneStateType::Weapon);
		return true;
	}

	return false;
}



void PhoneState_Skill::Update_VerticalArrow() 
{
	const float DeltaTime = Time.TimeCheck();
	VerticalArrowTimer += DeltaTime;
	if (VerticalArrowTimer < VerticalArrowMoveTime)
		return;

	bool IsMove = false;
	if (true == KeyMgr::IsPress(KeyNames::UpArrow))
	{
		//�̵� �Ұ���
		if (CURSOR_MIN == CursorIndex && INFO_MIN == InfoIndex)
		{
			SoundMgr::PlaySFX("Phone_Skill_MoveNo.wav");
			VerticalArrowTimer = 0.f;
			return;
		}

		MoveUp();
		IsMove = true;
	}

	else if (true == KeyMgr::IsPress(KeyNames::DownArrow))
	{
		//�̵� �Ұ���
		if (CURSOR_MAX == CursorIndex && INFO_MAX == InfoIndex)
		{
			SoundMgr::PlaySFX("Phone_Skill_MoveNo.wav");
			VerticalArrowTimer = 0.f;
			return;
		}

		MoveDown();
		IsMove = true;
	}

	if (false == IsMove)
		return;

	SoundMgr::PlaySFX("Phone_Skill_MoveOK.wav");
	SettingCursorRender();
	SettingInfoRender();
	VerticalArrowTimer = 0.f;
}


void PhoneState_Skill::MoveUp()
{
	//Ŀ���� �� ���� �ִ°� �ƴϸ� Ŀ���� �̵�
	if (CURSOR_MIN != CursorIndex)
	{
		--CursorIndex;
	}

	//Ŀ���� �� ������ ��ų ����� �� ���� �ƴ� ���
	else
	{
		--InfoIndex;
	}
}



void PhoneState_Skill::MoveDown()
{
	//Ŀ���� �� �Ʒ��� �ִ°� �ƴϸ� Ŀ���� �̵�
	if (CURSOR_MAX != CursorIndex)
	{
		++CursorIndex;
	}

	//Ŀ���� �� �Ʒ����� ��ų ����� �� �Ʒ��� �ƴ� ���
	else
	{
		++InfoIndex;
	}
}






void PhoneState_Skill::ExitState() 
{
	PhoneStateBase::ExitState();

	PhoneStateType NextState = GetFSM()->GetNowState<PhoneStateType>();
	if (false == IsUserState(NextState))
		return;

	CursorRender->Off();
	for (size_t i = 0; i < SkillInfoRenders.size(); ++i)
	{
		SkillInfoRenders[i]->Off();
	}

	VerticalArrowTimer = 0.f;
}
