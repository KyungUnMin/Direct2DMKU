#include "PrecompileHeader.h"
#include "EnemyStateBase.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "EnemyFSMBase.h"
#include "FieldEnemyBase.h"

#include "FieldPlayer.h"

EnemyStateBase::EnemyStateBase()
{

}

EnemyStateBase::~EnemyStateBase()
{

}

void EnemyStateBase::Start()
{
	StateBase::Start();

	FsmPtr = GetConvertFSM<EnemyFSMBase>();
	EnemyPtr = FsmPtr->GetEnemy();
	Renderer = EnemyPtr->GetRenderer();
	MainCollider = EnemyPtr->GetMainCollider();
}



void EnemyStateBase::EnterState()
{
	StateBase::EnterState();

	ChangeRenderDirection();
}


void EnemyStateBase::ChangeRenderDirection()
{
	GameEngineTransform* EnemyTransform = EnemyPtr->GetTransform();
	float4 EnemyPos = EnemyTransform->GetWorldPosition();
	float4 PlayerPos = FieldPlayer::GetPtr()->GetTransform()->GetWorldPosition();

	//플레이어가 자신의 오른쪽에 있는 경우
	if (EnemyPos.x < PlayerPos.x)
	{
		EnemyTransform->SetLocalPositiveScaleX();
	}

	//플레이어가 자신의 왼쪽에 있는 경우
	else
	{
		EnemyTransform->SetLocalNegativeScaleX();
	}
}



void EnemyStateBase::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	float Height = EnemyPtr->GetHeight();
	Renderer->GetTransform()->SetLocalPosition(float4::Up * Height);
	MainCollider->GetTransform()->SetLocalPosition(float4::Up * Height);
}



float4 EnemyStateBase::GetVecToPlayer(bool Is2D /*= false*/)
{
	GameEngineTransform* ThisTrans = EnemyPtr->GetTransform();
	GameEngineTransform* PlayerTrans = FieldPlayer::GetPtr()->GetTransform();

	float4 ThisWorldPosition = ThisTrans->GetWorldPosition();
	float4 PlayerWorldPosition = PlayerTrans->GetWorldPosition();

	if (true == Is2D)
	{
		ThisWorldPosition.z = 0.f;
		PlayerWorldPosition.z = 0.f;
	}

	return (PlayerWorldPosition - ThisWorldPosition);
}



bool EnemyStateBase::IsRightDir()
{
	GameEngineTransform* EnemyTrans = EnemyPtr->GetTransform();
	return (0.f < EnemyTrans->GetLocalScale().x);
}


