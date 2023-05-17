#include "PrecompileHeader.h"
#include "EnemyState_AttackBase.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "FieldEnemyBase.h"

EnemyState_AttackBase::EnemyState_AttackBase()
{

}

EnemyState_AttackBase::~EnemyState_AttackBase()
{

}

void EnemyState_AttackBase::SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index)
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	//n��° �����ӿ� ó���� �ݹ� ���
	EnemyRender->SetAnimationStartEvent(_AniName, _Index,
		std::bind(&EnemyState_AttackBase::AttackCheck, this));
}


void EnemyState_AttackBase::SetAttackColValue(const float4& _Offset, const float4& _Scale)
{
	GameEngineTransform* AttackColTrans =  GetEnemy()->GetAttackCollider()->GetTransform();
	AttackColTrans->SetLocalPosition(_Offset);
	AttackColTrans->SetLocalScale(_Scale);
}


void EnemyState_AttackBase::AttackCheck()
{
	std::shared_ptr<GameEngineCollision> AttackCollider = GetEnemy()->GetAttackCollider();
	std::shared_ptr<GameEngineCollision> PlayerCol = nullptr;
	PlayerCol = AttackCollider->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D);

	//������
	const TransformData& EnemyColData = AttackCollider->GetTransform()->GetTransDataRef();
	const TransformData& PlayerColData = PlayerCol->GetTransform()->GetTransDataRef();

	if (nullptr == PlayerCol)
		return;

	Attack();
}
