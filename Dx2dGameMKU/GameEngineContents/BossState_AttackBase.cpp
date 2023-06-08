#include "PrecompileHeader.h"
#include "BossState_AttackBase.h"

#include "FieldPlayer.h"
#include "FieldEnemyBase.h"

BossState_AttackBase::BossState_AttackBase()
{

}

BossState_AttackBase::~BossState_AttackBase()
{

}


float4 BossState_AttackBase::GetExpectPlayerPos()
{
	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();

	GameEngineTransform* PlayerTrans = Player->GetTransform();
	float4 PlayerPos = PlayerTrans->GetWorldPosition();

	//Enemy -> Player
	float4 EnemyToPlayer = EnemyStateBase::GetVecToPlayer();

	
	//플레이어 이동 방향벡터
	float4 PlayerDir = Player->GetMoveDirVec();


	//플레이어가 정지해있는 경우
	if (true == PlayerDir.IsZero())
	{
		//플레이어를 향한 직접적인 방향 반환
		return EnemyToPlayer;
	}

	//플레이어가 움직이고 있는 경우

	//플레이어 이동 벡터 정규화(방향)
	PlayerDir.Normalize();

	//Enemy와 Player사이 거리
	float DistanceToPlayer = EnemyToPlayer.Size();

	//플레이어 예상경로(플레이어 위치 + (플레이어 이동 방향 * Enemy와 Player사이 거리))
	float4 PlayerExpect = PlayerPos + (PlayerDir * DistanceToPlayer);

	//Enemy -> Player 예상경로(벡터 덧셈)
	float4 EnemyToPlayerExpect = (EnemyToPlayer + PlayerExpect);

	//서로의 이동 방향이 엇갈린다면
	if (PlayerDir.x * EnemyToPlayer.x <= 0.f)
	{
		//플레이어를 향한 직접적인 방향 반환
		return EnemyToPlayer;
	}


	return EnemyToPlayerExpect;
}