#include "PrecompileHeader.h"
#include "EnemyState_AttackBase.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "FieldEnemyBase.h"
#include "FieldPlayer.h"

EnemyState_AttackBase::EnemyState_AttackBase()
{

}

EnemyState_AttackBase::~EnemyState_AttackBase()
{

}

void EnemyState_AttackBase::Start()
{
	EnemyStateBase::Start();

	AttackCollider = GetEnemy()->GetAttackCollider();
}

void EnemyState_AttackBase::SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index)
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	//n번째 프레임에 처리할 콜백 등록
	EnemyRender->SetAnimationStartEvent(_AniName, _Index,
		std::bind(&EnemyState_AttackBase::AttackCheck, this));
}


void EnemyState_AttackBase::SetAttackColValue(const float4& _Offset, const float4& _Scale)
{
	GameEngineTransform* AttackColTrans = AttackCollider->GetTransform();

	if (_Scale.z < 5.f)
	{
		MsgAssert("Enemy Attack의 충돌범위 설정 중에 Z값도 고려해주어야 합니다");
		return;
	}

	AttackColTrans->SetLocalPosition(_Offset);
	AttackColTrans->SetLocalScale(_Scale);
}


void EnemyState_AttackBase::AttackCheck()
{
	std::shared_ptr<GameEngineCollision> PlayerCol = nullptr;
	PlayerCol = AttackCollider->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D);

	//디버깅용
	const TransformData& EnemyColData = AttackCollider->GetTransform()->GetTransDataRef();
	const TransformData& PlayerColData = PlayerCol->GetTransform()->GetTransDataRef();

	if (nullptr == PlayerCol)
		return;


	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();
	
	//플레이어가 적 기준 오른쪽에 있는 경우
	if (EnemyColData.WorldPosition.x < PlayerColData.WorldPosition.x)
	{
		//왼쪽을 바라본다
		PlayerPtr->SetDirection(false);
		//PlayerTrans->SetLocalNegativeScaleX();
	}
	//플레이어가 적 기준 왼쪽에 있는 경우
	else
	{
		//오른쪽을 바라본다
		PlayerPtr->SetDirection(true);
		//PlayerTrans->SetLocalPositiveScaleX();
	}

	Attack();
}
