#include "PrecompileHeader.h"
#include "NoiseFan.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"
#include "DataMgr.h"

#include "FieldPlayer.h"
#include "BackGround.h"

void NoiseFan::Update_Climb(float _DeltaTime)
{
	static const float Duration = 0.5f;
	static const float MaxHeight = 100.f;

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * 0.5f * ClampRatio);

	float NowHeight = (MaxHeight * (1.f - SinValue)) + (0.f * SinValue);
	SetHeight(NowHeight);

	if (Ratio < 1.f)
		return;

	GetMainCollider()->On();
	GetAttackCollider()->On();
	ChangeState(State::Trace);
}

void NoiseFan::Update_Trace(float _DeltaTime)
{
	static const float Acc = 600.f;
	static const float MaxSpeed = 300.f;
	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();

	float4 PlayerPos = Player->GetTransform()->GetWorldPosition();
	float4 ThisPos = GetTransform()->GetWorldPosition();
	float4 DirToPlayer = (PlayerPos - ThisPos);
	DirToPlayer.Normalize();

	TraceVec += (DirToPlayer * Acc * _DeltaTime);
	if (MaxSpeed < TraceVec.Size())
	{
		TraceVec.Normalize();
		TraceVec *= MaxSpeed;
	}

	GameEngineTransform* ThisTrans = GetTransform();
	float4 NowPos = ThisTrans->GetLocalPosition();
	float4 NextPos = NowPos + (TraceVec * _DeltaTime);

	std::shared_ptr<BackGround> BGPtr = GetBackGround();
	if (true == BGPtr->IsBlockPos(NextPos))
	{
		TraceVec = -TraceVec;
	}
	else
	{
		ThisTrans->SetLocalPosition(NextPos);
	}




	float LiveTime = GetLiveTime();
	if (LiveTime < (LastAttackTime + 1.0f))
		return;

	if (nullptr == GetAttackCollider()->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D))
		return;

	LastAttackTime = LiveTime;

	if (false == Player->OnDamage_Jaw())
		return;

	ChangeFlyState();
	DataMgr::MinusPlayerHP(1);
}

void NoiseFan::Update_FlyAway(float _DeltaTime)
{

}

void NoiseFan::Update_Fall(float _DeltaTime) 
{

}
