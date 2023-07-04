#include "PrecompileHeader.h"
#include "PlayerState_Avoid.h"

//#include <GameEngineCore/GameEngineCollision.h>

#include "KeyMgr.h"
#include "RCGEnums.h"
#include "RCGDefine.h"
#include "SoundMgr.h"

#include "BackGround.h"
#include "PlayerFSM.h"
#include "FieldPlayer.h"
#include "FieldLevelBase.h"

#include "DashSmokeEffect.h"

const std::string_view PlayerState_Avoid::AniName = "Player_Dodge.png";

const float PlayerState_Avoid::MaxSpeed = 1000.f;
const float PlayerState_Avoid::MaxHeight = 50.f;
const float PlayerState_Avoid::Duration = 0.2f;


PlayerState_Avoid::PlayerState_Avoid()
{

}

PlayerState_Avoid::~PlayerState_Avoid()
{
	
}

void PlayerState_Avoid::Start()
{
	PlayerState_MovementBase::Start();

	ImageLoad();
	CreateAnimation();
}

void PlayerState_Avoid::ImageLoad()
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniName).GetFullPath(), 2, 1);
}

void PlayerState_Avoid::CreateAnimation() 
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = 1,
		.FrameInter = 0.08f,
		.Loop = false,
	});
}


void PlayerState_Avoid::EnterState()
{
	PlayerState_MovementBase::EnterState();

	if (true == KeyMgr::IsPress(KeyNames::UpArrow))
	{
		MoveDir = float4::Up;
	}
	else
	{
		MoveDir = float4::Down;
	}

	CreateEffect();
	GetRenderer()->ChangeAnimation(AniName);
	//FieldPlayer::GetPtr()->GetMainCollider()->Off();

	SoundMgr::PlaySFX("player_footsteps_run_03.wav");
}

void PlayerState_Avoid::CreateEffect()
{
	std::shared_ptr<FieldLevelBase> Level = FieldLevelBase::GetPtr();
	std::shared_ptr<DashSmokeEffect> Effect = nullptr;
	Effect = Level->CreateActor<DashSmokeEffect>(UpdateOrder::Effect);

	GameEngineTransform* PlayerTrans = FieldPlayer::GetPtr()->GetTransform();
	GameEngineTransform* EffectTrans = Effect->GetTransform();
	
	float4 CreatePos = PlayerTrans->GetWorldPosition();
	EffectTrans->SetLocalPosition(CreatePos);
}

void PlayerState_Avoid::Update(float _DeltaTime)
{
	PlayerState_MovementBase::Update(_DeltaTime);

	float Ratio = (GetLiveTime() / Duration);
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);

	Update_Move(_DeltaTime, ClampRatio);
	Update_Jump(ClampRatio);
	

	if (GetLiveTime() < Duration)
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}



void PlayerState_Avoid::Update_Move(float _DeltaTime, float _Ratio)
{
	//0 -> 1 -> 0
	float SinValue = sinf(GameEngineMath::PIE * _Ratio);
	float NowSpeed = (SinValue * MaxSpeed);

	//다음에 이동할 위치 계산
	GameEngineTransform* PlayerTrans = GetPlayerTransform();
	float4 PrevPos = PlayerTrans->GetLocalPosition();
	float4 NextPos = PrevPos + (MoveDir * NowSpeed * _DeltaTime);
	NextPos.z = NextPos.y;

	//벽으로 막힌 곳인지 확인1
	std::shared_ptr<BackGround> BGPtr = GetBackGround();
	if (true == BGPtr->IsBlockPos(NextPos))
		return;

	//벽으로 막힌 곳인지 확인2
	std::pair<int, int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
		return;

	//이동
	PlayerTrans->SetLocalPosition(NextPos);
}


void PlayerState_Avoid::Update_Jump(float _Ratio)
{
	//위로 이동할땐 점프X
	if (float4::Up == MoveDir)
		return;

	float SinValue = sinf(GameEngineMath::PIE * _Ratio);
	float NowHeight = (SinValue * MaxHeight);

	FieldPlayer::GetPtr()->SetHeight(NowHeight);
}


void PlayerState_Avoid::ExitState()
{
	PlayerState_MovementBase::ExitState();
	FieldPlayer::GetPtr()->SetHeight(0.f);
	//FieldPlayer::GetPtr()->GetMainCollider()->On();
}
