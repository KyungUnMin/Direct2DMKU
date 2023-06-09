#include "PrecompileHeader.h"
#include "PlayerState_Dash.h"

#include "KeyMgr.h"
#include "RCGEnums.h"
#include "SoundMgr.h"

#include "PlayerFSM.h"
#include "FieldPlayer.h"

#include "FieldLevelBase.h"
#include "DashSmokeEffect.h"


const float4 PlayerState_Dash::DashSpeed = float4{ 800.f, 400.f };

const std::string_view PlayerState_Dash::AniName = "Dash";
const std::string_view PlayerState_Dash::AniFileName = "Player_Dash.png";
const std::pair<int, int> PlayerState_Dash::AniCutFrame = std::pair<int, int>(4, 4);
const float PlayerState_Dash::AniInterTime = 0.04f;

PlayerState_Dash::PlayerState_Dash()
{

}

PlayerState_Dash::~PlayerState_Dash()
{

}

void PlayerState_Dash::Start()
{
	PlayerState_MovementBase::Start();

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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_Dash::CreateAnimation() 
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime
	});

	Render->SetAnimationStartEvent(AniName, 0, []()
	{
		SoundMgr::PlaySFX("player_footsteps_run_01.wav");
	});

	Render->SetAnimationStartEvent(AniName, 7, []()
	{
		SoundMgr::PlaySFX("player_footsteps_run_02.wav");
	});

}


void PlayerState_Dash::EnterState()
{
	PlayerState_MovementBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	CreateEffect();
}

void PlayerState_Dash::CreateEffect()
{
	std::shared_ptr<DashSmokeEffect> Effect = nullptr;
	Effect = FieldLevelBase::GetPtr()->CreateActor<DashSmokeEffect>(UpdateOrder::Effect);

	float4 PlayerPos = FieldPlayer::GetPtr()->GetTransform()->GetWorldPosition();
	Effect->GetTransform()->SetLocalPosition(PlayerPos);
}




void PlayerState_Dash::Update(float _DeltaTime)
{
	PlayerState_MovementBase::Update(_DeltaTime);

	if (true == Check_Idle())
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Jump);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::Z))
	{
		GetFSM()->ChangeState(PlayerStateType::DashAttack_BackElbow);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::X) || true == KeyMgr::IsPress(KeyNames::C))
	{
		GetFSM()->ChangeState(PlayerStateType::DashAttack_DropKick);
		return;
	}


	PlayerState_MovementBase::Update_Move(_DeltaTime, DashSpeed);
}

