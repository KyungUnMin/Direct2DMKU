#include "PrecompileHeader.h"
#include "BossState_AttackBase.h"

#include "FieldPlayer.h"
#include "FieldEnemyBase.h"
#include "BackGround.h"

BossState_AttackBase::BossState_AttackBase()
{

}

BossState_AttackBase::~BossState_AttackBase()
{

}


float4 BossState_AttackBase::GetVecToExpectPlayerPos()
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



bool BossState_AttackBase::Update_SinHalfMove(
	float _Timer, float _Duration,
	const float4& _StartPos, const float4& _DestPos)
{
	float Ratio = (_Timer / _Duration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	float SinValue = std::sinf(GameEngineMath::PIE * Ratio * 0.5f);

	return Update_LerpMove(SinValue, _StartPos, _DestPos);
}



bool BossState_AttackBase::Update_CosHalfMove(
	float _Timer, float _Duration,
	const float4& _StartPos, const float4& _DestPos)
{
	float Ratio = (_Timer / _Duration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	float CosValue = std::cosf(GameEngineMath::PIE * Ratio * 0.5f);

	//Cos값 이 1부터 0으로 이동하기 때문에 DestPos -> StartPos
	return Update_LerpMove(CosValue, _DestPos, _StartPos);
}



bool BossState_AttackBase::Update_LerpMove(float _Ratio, const float4& _StartPos, const float4& _DestPos)
{
	//다음 이동 경로
	float4 NextPos = float4::LerpClamp(_StartPos, _DestPos, _Ratio);


	//벽에 막힌 경우1
	std::shared_ptr<BackGround> BGPtr = GetBackGround();
	if (true == BGPtr->IsBlockPos(NextPos))
		return false;

	//벽에 막힌 경우2
	std::pair<int, int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
		return false;

	//이동
	GetEnemy()->GetTransform()->SetLocalPosition(NextPos);
	return true;
}
