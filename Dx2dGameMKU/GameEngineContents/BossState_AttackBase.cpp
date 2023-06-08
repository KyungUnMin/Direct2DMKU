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

	
	//�÷��̾� �̵� ���⺤��
	float4 PlayerDir = Player->GetMoveDirVec();


	//�÷��̾ �������ִ� ���
	if (true == PlayerDir.IsZero())
	{
		//�÷��̾ ���� �������� ���� ��ȯ
		return EnemyToPlayer;
	}

	//�÷��̾ �����̰� �ִ� ���

	//�÷��̾� �̵� ���� ����ȭ(����)
	PlayerDir.Normalize();

	//Enemy�� Player���� �Ÿ�
	float DistanceToPlayer = EnemyToPlayer.Size();

	//�÷��̾� ������(�÷��̾� ��ġ + (�÷��̾� �̵� ���� * Enemy�� Player���� �Ÿ�))
	float4 PlayerExpect = PlayerPos + (PlayerDir * DistanceToPlayer);

	//Enemy -> Player ������(���� ����)
	float4 EnemyToPlayerExpect = (EnemyToPlayer + PlayerExpect);

	//������ �̵� ������ �������ٸ�
	if (PlayerDir.x * EnemyToPlayer.x <= 0.f)
	{
		//�÷��̾ ���� �������� ���� ��ȯ
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

	//Cos�� �� 1���� 0���� �̵��ϱ� ������ DestPos -> StartPos
	return Update_LerpMove(CosValue, _DestPos, _StartPos);
}



bool BossState_AttackBase::Update_LerpMove(float _Ratio, const float4& _StartPos, const float4& _DestPos)
{
	//���� �̵� ���
	float4 NextPos = float4::LerpClamp(_StartPos, _DestPos, _Ratio);


	//���� ���� ���1
	std::shared_ptr<BackGround> BGPtr = GetBackGround();
	if (true == BGPtr->IsBlockPos(NextPos))
		return false;

	//���� ���� ���2
	std::pair<int, int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
		return false;

	//�̵�
	GetEnemy()->GetTransform()->SetLocalPosition(NextPos);
	return true;
}
