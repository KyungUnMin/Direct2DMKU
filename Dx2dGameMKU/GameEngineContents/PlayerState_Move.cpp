#include "PrecompileHeader.h"
#include "PlayerState_Move.h"

#include "FieldPlayer.h"
#include "PlayerFSM.h"

const std::string_view PlayerState_Move::AniName = "Walk";
const std::string_view PlayerState_Move::AniFolderName = "PlayerWalk";
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
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName(AniFolderName).GetFullPath());
}

void PlayerState_Move::CreateAnimation() 
{
	PlayerStateBase::SpritePtr = GameEngineSprite::Find(AniFolderName);

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = GetRenderer();
	PlayerStateBase::AniInfoPtr = Renderer->CreateAnimation(AniName, AniFolderName, AniInterTime);
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

	if (true == Check_Idle())
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Jump);
		return;
	}
	
	float NowTime = GetFSM()->GetFsmTime();
	if (NowTime < (LastTime + 0.1f) && (PressArrow == LastArrow))
	{
		GetFSM()->ChangeState(PlayerStateType::Dash);
		return;
	}


	/*if (false == FieldPlayer::GPtr->IsGround() && true == IsOnAir())
	{
		GetFSM()->ChangeState(PlayerStateType::Fall);
		return;
	}*/

	PlayerStateBase::Update_Move(_DeltaTime);
}


void PlayerState_Move::ExitState()
{
	PlayerStateBase::ExitState();

	LastArrow = PressArrow;
	LastTime = GetFSM()->GetFsmTime();
}

