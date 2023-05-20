#include "PrecompileHeader.h"
#include "FieldEnemyBase.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCG_GameCore.h"
#include "RCGEnums.h"

#include "HitEffect.h"

FieldEnemyBase::FieldEnemyBase()
{

}

FieldEnemyBase::~FieldEnemyBase()
{

}

void FieldEnemyBase::Start()
{
	FieldActorBase::Start();
	FieldActorBase::CreateColliders(CollisionOrder::EnemyMain);
}

void FieldEnemyBase::OnDamage(int _Damage)
{
	Hp -= abs(_Damage);
	if (0 < Hp)
		return;

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

