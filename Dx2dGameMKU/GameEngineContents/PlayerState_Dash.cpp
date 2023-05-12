#include "PrecompileHeader.h"
#include "PlayerState_Dash.h"

#include "KeyMgr.h"
#include "PlayerFSM.h"
#include "FieldPlayer.h"

const float4 PlayerState_Dash::DashSpeed = float4{ 800.f, 400.f };
const std::string_view PlayerState_Dash::AniName = "Dash";
const std::string_view PlayerState_Dash::AniFolderName = "PlayerRun";
const float PlayerState_Dash::AniInterTime = 0.04f;

PlayerState_Dash::PlayerState_Dash()
{

}

PlayerState_Dash::~PlayerState_Dash()
{

}

void PlayerState_Dash::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_Dash::LoadAnimation()
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

void PlayerState_Dash::CreateAnimation() 
{
	PlayerStateBase::SpritePtr = GameEngineSprite::Find(AniFolderName);

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = GetRenderer();
	PlayerStateBase::AniInfoPtr = Renderer->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFolderName,
		.FrameInter = AniInterTime
	});
}


void PlayerState_Dash::EnterState()
{
	PlayerStateBase::EnterState();

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = GetRenderer();
	Renderer->ChangeAnimation(AniName);

}



void PlayerState_Dash::Update(float _DeltaTime)
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




	Update_Move(_DeltaTime, DashSpeed);
}

