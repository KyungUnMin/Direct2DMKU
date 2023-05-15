#include "PrecompileHeader.h"
#include "EnemyState_WalkBase.h"


#include "FieldLevelBase.h"
#include "BackGround.h"
#include "FieldEnemyBase.h"
#include "EnemyFSMBase.h"



EnemyState_WalkBase::EnemyState_WalkBase()
{

}

EnemyState_WalkBase::~EnemyState_WalkBase()
{

}


void EnemyState_WalkBase::Start()
{
	EnemyStateBase::Start();

	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
	GridMapScale = BGPtr->GetGridMapScale();
}

void EnemyState_WalkBase::EnterState()
{
	EnemyStateBase::EnterState();

	FindPath();
	SetDest();
	EnemyStateBase::ChangeRenderDirection();

	if (-1 == NextState)
	{
		MsgAssert("�ڽ��ʿ��� Enemy�� �̵��� ���� �� �ٲ� State�� ���������� �ʾҽ��ϴ�");
		return;
	}
}

bool EnemyState_WalkBase::SetDest()
{
	if (true == PathStack.empty())
		return false;

	std::pair<int, int> DestGridPos = PathStack.back();
	PathStack.pop_back();

	DestPos = BGPtr->GetPosFromGrid(DestGridPos.first, DestGridPos.second);
	StartPos = GetEnemy()->GetTransform()->GetWorldPosition();
	return true;
}




void EnemyState_WalkBase::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	Timer += _DeltaTime;

	float Ratio = (Timer / MoveDuration);
	float4 NextPos = float4::LerpClamp(StartPos, DestPos, Ratio);
	GetEnemy()->GetTransform()->SetWorldPosition(NextPos);

	if (Ratio < 1.f)
		return;

	Timer -= MoveDuration;
	if (true == SetDest())
		return;

	//�ڽĿ��� �������� ���°����� �̵�
	GetFSM()->ChangeState(NextState);
}

