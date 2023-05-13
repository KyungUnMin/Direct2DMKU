#include "PrecompileHeader.h"
#include "PlayerState_Move.h"

#include "FieldPlayer.h"
#include "PlayerFSM.h"

const std::string_view PlayerState_Move::AniName = "Walk";
const std::string_view PlayerState_Move::AniFileName = "Player_Walk.png";
const std::pair<int, int> PlayerState_Move::AniCutFrame = std::pair<int, int>(4, 3);
const float PlayerState_Move::AniInterTime = 0.08f;

std::vector<KeyNames>  PlayerState_Move::CheckArrows =
{
	KeyNames::RightArrow,
	KeyNames::LeftArrow,
	KeyNames::UpArrow,
	KeyNames::DownArrow,
};

PlayerState_Move::PlayerState_Move()
{

}

PlayerState_Move::~PlayerState_Move()
{

}

void PlayerState_Move::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Move::LoadAnimation()
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

void PlayerState_Move::CreateAnimation() 
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime
	});
}


void PlayerState_Move::EnterState()
{
	PlayerStateBase::EnterState();

	CheckPressArrow(PressArrow);
	GetRenderer()->ChangeAnimation(AniName);
}



void PlayerState_Move::CheckPressArrow(KeyNames& _SettingEnum)
{
	for (const KeyNames Arrow : CheckArrows)
	{
		if (false == KeyMgr::IsPress(Arrow))
			continue;

		_SettingEnum = Arrow;
	}
}


void PlayerState_Move::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	//아이들 처리
	if (true == Check_Idle())
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}


	//일반 기본 공격
	if (true == KeyMgr::IsPress(KeyNames::Z))
	{
		GetFSM()->ChangeState(PlayerStateType::QuickAttack_Chop);
		return;
	}

	//특수 공격
	if (true == KeyMgr::IsPress(KeyNames::X))
	{
		GetFSM()->ChangeState(PlayerStateType::SpecialAttack_DAP);
		return;
	}


	//특수 스킬
	if (true == KeyMgr::IsPress(KeyNames::C) && true == KeyMgr::IsPress(KeyNames::DownArrow))
	{
		GetFSM()->ChangeState(PlayerStateType::UniqueAttack_HyrricaneKick);
		return;
	}


	//점프 처리
	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Jump);
		return;
	}
	
	//대시처리
	float NowTime = GetFSM()->GetFsmTime();
	if (NowTime < (LastTime + 0.1f) && (PressArrow == LastArrow))
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Dash);
		return;
	}


	

	//실제 이동
	PlayerStateBase::Update_Move(_DeltaTime);
}


void PlayerState_Move::ExitState()
{
	PlayerStateBase::ExitState();

	LastArrow = PressArrow;
	LastTime = GetFSM()->GetFsmTime();
}

