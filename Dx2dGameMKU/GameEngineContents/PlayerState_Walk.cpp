#include "PrecompileHeader.h"
#include "PlayerState_Walk.h"

#include "DataMgr.h"

#include "FieldPlayer.h"
#include "PlayerFSM.h"
#include "PlayerState_UniqueAttack_HyrricaneKick.h"



const std::string_view PlayerState_Walk::AniName = "Walk";
const std::string_view PlayerState_Walk::AniFileName = "Player_Walk.png";
const std::pair<int, int> PlayerState_Walk::AniCutFrame = std::pair<int, int>(4, 3);
const float PlayerState_Walk::AniInterTime = 0.08f;

std::vector<KeyNames>  PlayerState_Walk::CheckArrows =
{
	KeyNames::RightArrow,
	KeyNames::LeftArrow,
	KeyNames::UpArrow,
	KeyNames::DownArrow,
};

PlayerState_Walk::PlayerState_Walk()
{

}

PlayerState_Walk::~PlayerState_Walk()
{

}

void PlayerState_Walk::Start()
{
	PlayerState_MovementBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Walk::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_Walk::CreateAnimation() 
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime
	});
}


void PlayerState_Walk::EnterState()
{
	PlayerState_MovementBase::EnterState();

	CheckPressArrow(PressArrow);
	GetRenderer()->ChangeAnimation(AniName);
}



void PlayerState_Walk::CheckPressArrow(KeyNames& _SettingEnum)
{
	for (const KeyNames Arrow : CheckArrows)
	{
		if (false == KeyMgr::IsPress(Arrow))
			continue;

		_SettingEnum = Arrow;
	}
}


void PlayerState_Walk::Update(float _DeltaTime)
{
	PlayerState_MovementBase::Update(_DeltaTime);

	//���̵� ó��
	if (true == Check_Idle())
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}

	//���
	if (true == KeyMgr::IsPress(KeyNames::LeftShift))
	{
		GetFSM()->ChangeState(PlayerStateType::Damaged_Block);
		return;
	}

	//�Ϲ� �⺻ ����
	if (true == KeyMgr::IsPress(KeyNames::Z))
	{
		GetFSM()->ChangeState(PlayerStateType::QuickAttack_Chop);
		return;
	}

	//Ư�� ����
	if (true == KeyMgr::IsPress(KeyNames::X))
	{
		GetFSM()->ChangeState(PlayerStateType::SpecialAttack_DAP);
		return;
	}


	//Ư�� ��ų
	if (true == KeyMgr::IsPress(KeyNames::C) && true == KeyMgr::IsPress(KeyNames::DownArrow))
	{
		int CurMp = DataMgr::GetPlayerMP();
		if (PlayerState_UniqueAttack_HyrricaneKick::NeedMp <= CurMp)
		{
			GetFSM()->ChangeState(PlayerStateType::UniqueAttack_HyrricaneKick);
			return;
		}
	}


	//���� ó��
	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Jump);
		return;
	}
	
	//���ó��
	float NowTime = GetFSM()->GetFsmTime();
	if (NowTime < (LastTime + 0.1f) && (PressArrow == LastArrow))
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Dash);
		return;
	}


	

	//���� �̵�
	PlayerState_MovementBase::Update_Move(_DeltaTime);
}


void PlayerState_Walk::ExitState()
{
	PlayerState_MovementBase::ExitState();

	LastArrow = PressArrow;
	LastTime = GetFSM()->GetFsmTime();
}

