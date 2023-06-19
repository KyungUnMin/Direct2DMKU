#include "PrecompileHeader.h"
#include "FieldEnemyBase.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCG_GameCore.h"
#include "RCGEnums.h"

#include "HitEffect.h"
#include "FieldLevelBase.h"
#include "EnemySpawner.h"

FieldEnemyBase::FieldEnemyBase()
{
	//BindPosChecker();
}

FieldEnemyBase::~FieldEnemyBase()
{

}



void FieldEnemyBase::Look(const float4& _LookPos)
{
	FieldActorBase::Look(_LookPos);
	IsDirRegistValue = true;
}


void FieldEnemyBase::DirectionFlip()
{
	FieldActorBase::DirectionFlip();
	IsDirRegistValue = true;
}

void FieldEnemyBase::LookDir(bool _IsRight)
{
	FieldActorBase::LookDir(_IsRight);
	IsDirRegistValue = true;
}



void FieldEnemyBase::Start()
{
	FieldActorBase::Start();
	FieldActorBase::CreateColliders(CollisionOrder::EnemyMain);
}

void FieldEnemyBase::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);

	if (-1 != SpawnIdx)
		return;

	MsgAssert("Enemy는 반드시 EnemySpawner를 통해 생성되어야 합니다");
}

void FieldEnemyBase::OnDamage(int _Damage)
{
	Hp -= abs(_Damage);
	if (0 < Hp)
		return;

	//적이 죽은 한순간
	if (false == IsKOValue)
	{
		EnemySpawner& Spawner = FieldLevelBase::GetPtr()->GetEnemySpawner();
		Spawner.KillEnemy(DynamicThis<FieldEnemyBase>());
	}
	
	Hp = 0;
	IsKOValue = true;
}

void FieldEnemyBase::CreateHitEffect(const float4& _Offset)
{
	std::shared_ptr<HitEffect> Effect = GetLevel()->CreateActor<HitEffect>(UpdateOrder::Effect);
	GameEngineTransform* EffectTrans = Effect->GetTransform();
	float4 EffectPos = GetTransform()->GetWorldPosition() + _Offset;
	EffectTrans->SetLocalPosition(EffectPos);
}


