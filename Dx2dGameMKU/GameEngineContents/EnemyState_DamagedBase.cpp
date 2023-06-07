#include "PrecompileHeader.h"
#include "EnemyState_DamagedBase.h"

#include "RCGEnums.h"

#include "FieldEnemyBase.h"
#include "FieldLevelBase.h"
#include "BackGround.h"
#include "HitEffect.h"

EnemyState_DamagedBase::EnemyState_DamagedBase()
{

}

EnemyState_DamagedBase::~EnemyState_DamagedBase()
{

}



void EnemyState_DamagedBase::EnterState()
{
	EnemyStateBase::EnterState();

	//플레이어의 방향
	EnemyDir = EnemyStateBase::IsRightDir();

	if (true == IsHeightFix)
	{
		GetEnemy()->SetHeight(0.f);
	}
}

bool EnemyState_DamagedBase::Update_BlowBack(float _DeltaTime)
{
	float LiveTime = GetLiveTime();
	float Ratio = (LiveTime / Duration);
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);

	bool IsMoveOK = Update_BlowHorizon(ClampRatio, _DeltaTime);
	Update_BlowVertical(ClampRatio);

	//벽과 충돌 여부
	IsWallHit = !IsMoveOK;

	//Effect

	return IsMoveOK;
}


void EnemyState_DamagedBase::Update_BlowReflect(float _DeltaTime)
{
	//아직 벽에 충돌하지 않았다면 정상적인 BlowBack
	if (false == IsWallHit)
	{
		Update_BlowBack(_DeltaTime);

		//이번 프레임에 벽과 충돌했었다면 충돌 이펙트
		if (true == IsWallHit)
		{
			CreateWallEffect();
		}
		return;
	}

	//벽에 충돌 했었다면 튕겨져 나오기
	float Ratio = (GetLiveTime() / Duration);
	//Enemy가 바라보고 있던 방향
	float4 ReflectDir = EnemyDir ? float4::Right : float4::Left;

	EnemyStateBase::Update_AccMove(_DeltaTime, Ratio, ReflectDir, StartAcc);
	EnemyState_DamagedBase::Update_BlowVertical(Ratio);
}





void EnemyState_DamagedBase::CreateWallEffect()
{
	static const float4 Offset = float4::Up * 100.f;
	static const float4 Scale = float4{ 0.5f, 1.f };

	std::shared_ptr<HitEffect> Effect = nullptr;
	Effect = FieldLevelBase::GetPtr()->CreateActor<HitEffect>(UpdateOrder::Effect);
	Effect->OffHitSpark();

	float4 EnemyPos = GetEnemy()->GetTransform()->GetWorldPosition();
	GameEngineTransform* EffectTrans = Effect->GetTransform();
	EffectTrans->SetLocalPosition(EnemyPos + Offset);
	EffectTrans->SetLocalScale(Scale);
}



bool EnemyState_DamagedBase::Update_BlowHorizon(float _Ratio, float _DeltaTime)
{
	//적이 오른쪽을 바라보고 있을때
	if (true == EnemyDir)
	{
		//바라보는 방향 반대로 날라간다
		return EnemyStateBase::Update_AccMove(_DeltaTime, _Ratio, float4::Left, StartAcc);
	}
	//적이 왼쪽을 바라보고 있을때
	else
	{
		//바라보는 방향 반대로 날라간다
		return EnemyStateBase::Update_AccMove(_DeltaTime, _Ratio, float4::Right, StartAcc);
	}
}

void EnemyState_DamagedBase::Update_BlowVertical(float _Ratio)
{
	if (true == IsHeightFix)
		return;


	float NowHeight = StartHeight * (1.f - _Ratio);
	GetEnemy()->SetHeight(NowHeight);
}


void EnemyState_DamagedBase::ExitState()
{
	EnemyStateBase::ExitState();
	GetEnemy()->SetHeight(0.f);
	IsWallHit = false;
}