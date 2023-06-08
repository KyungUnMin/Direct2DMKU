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