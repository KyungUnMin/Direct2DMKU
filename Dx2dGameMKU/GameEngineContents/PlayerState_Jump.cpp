#include "PrecompileHeader.h"
#include "PlayerState_Jump.h"

#include <algorithm>

#include "FieldPlayer.h"
#include "PlayerFSM.h"

const std::string_view PlayerState_Jump::AniName = "Jump";
const std::string_view PlayerState_Jump::AniFolderName = "PlayerJump";
const float PlayerState_Jump::AniInterTime = FLT_MAX;

PlayerState_Jump::PlayerState_Jump()
{

}

PlayerState_Jump::~PlayerState_Jump()
{

}


void PlayerState_Jump::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Jump::LoadAnimation()
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


void PlayerState_Jump::CreateAnimation()
{
	PlayerStateBase::SpritePtr = GameEngineSprite::Find(AniFolderName);

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = GetRenderer();
	PlayerStateBase::AniInfoPtr = Renderer->CreateAnimation(AniName, AniFolderName, AniInterTime, -1, -1, false);
}



void PlayerState_Jump::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}



void PlayerState_Jump::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	GetLiveTIme();

	LiveTime += _DeltaTime;
	float Ratio = (LiveTime / Duration);

	//float NowJumpScale = JumpScale * (1.f - Ratio);
	float NowJumpScale = JumpScale * Ratio;
	FieldPlayer::GetPtr()->SetHeight(NowJumpScale);
	//FieldPlayer::GetPtr()->AddHeight(NowJumpScale * _DeltaTime);

	if (Duration < LiveTime)
	{
		GetFSM()->ChangeState(PlayerStateType::Fall);
		return;
	}

	Update_Move(_DeltaTime);
}


void PlayerState_Jump::ExitState()
{
	PlayerStateBase::ExitState();
	LiveTime = 0.f;
}
