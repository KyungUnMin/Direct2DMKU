#include "PrecompileHeader.h"
#include "PlayerState_Fall.h"
#include "FieldPlayer.h"
#include "PlayerFSM.h"

const std::string_view PlayerState_Fall::AniName = "Fall";
const std::string_view PlayerState_Fall::AniFolderName = "PlayerFall";
const float PlayerState_Fall::AniInterTime = 0.05f;

PlayerState_Fall::PlayerState_Fall()
{

}

PlayerState_Fall::~PlayerState_Fall()
{

}

void PlayerState_Fall::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Fall::LoadAnimation()
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


void PlayerState_Fall::CreateAnimation()
{
	PlayerStateBase::SpritePtr = GameEngineSprite::Find(AniFolderName);

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = GetRenderer();
	PlayerStateBase::AniInfoPtr = Renderer->CreateAnimation(AniName, AniFolderName, AniInterTime, -1, -1, false);
}



void PlayerState_Fall::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void PlayerState_Fall::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);


	NowGravity += (GravityAcc * _DeltaTime);
	FieldPlayer::GetPtr()->AddHeight(-NowGravity * _DeltaTime);

	if (true == FieldPlayer::GetPtr()->IsZeroHeight())
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		return;
	}

	//임시, 물체 위에 올라가는 경우 고려X
	/*if (true == GetPlayerPtr()->IsGround())
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		return;
	}*/

	Update_Move(_DeltaTime);
}

void PlayerState_Fall::ExitState()
{
	PlayerStateBase::ExitState();
	NowGravity = StartGravity;

}

