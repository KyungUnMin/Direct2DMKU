#include "PrecompileHeader.h"
#include "EnemyState_DamagedBase.h"

#include "FieldEnemyBase.h"
#include "FieldLevelBase.h"
#include "BackGround.h"

EnemyState_DamagedBase::EnemyState_DamagedBase()
{

}

EnemyState_DamagedBase::~EnemyState_DamagedBase()
{

}



void EnemyState_DamagedBase::EnterState()
{
	EnemyStateBase::EnterState();

	//�÷��̾��� ����
	EnemyDir = EnemyStateBase::IsRightDir();

	if (true == IsHeightFix)
	{
		GetEnemy()->SetHeight(0.f);
	}
}

bool EnemyState_DamagedBase::Update_BlowBack(float _DeltaTime)
{
	float LiveTime = GetLiveTime();
	float Ratio = (LiveTime / Duration);
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);

	bool IsMoveOk = Update_BlowHorizon(ClampRatio, _DeltaTime);
	Update_BlowVertical(ClampRatio);

	return IsMoveOk;
}



bool EnemyState_DamagedBase::Update_BlowHorizon(float _Ratio, float _DeltaTime)
{
	//���� �������� �ٶ󺸰� ������
	if (true == EnemyDir)
	{
		//�ٶ󺸴� ���� �ݴ�� ���󰣴�
		return EnemyStateBase::Update_AccMove(_DeltaTime, _Ratio, float4::Left, StartAcc);
	}
	//���� ������ �ٶ󺸰� ������
	else
	{
		//�ٶ󺸴� ���� �ݴ�� ���󰣴�
		return EnemyStateBase::Update_AccMove(_DeltaTime, _Ratio, float4::Right, StartAcc);
	}
}

void EnemyState_DamagedBase::Update_BlowVertical(float _Ratio)
{
	if (true == IsHeightFix)
		return;


	float NowHeight = StartHeight * (1.f - _Ratio);
	GetEnemy()->SetHeight(NowHeight);
}


void EnemyState_DamagedBase::ExitState()
{
	EnemyStateBase::ExitState();
	GetEnemy()->SetHeight(0.f);
}