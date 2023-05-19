#include "PrecompileHeader.h"
#include "FieldEnemyBase.h"


#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCG_GameCore.h"
#include "RCGEnums.h"

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

