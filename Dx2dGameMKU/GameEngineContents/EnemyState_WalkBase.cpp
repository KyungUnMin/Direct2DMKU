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
		MsgAssert("자식쪽에서 Enemy의 이동이 끝난 뒤 바꿀 State를 지정해주지 않았습니다");
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

	//자식에서 지정해준 상태값으로 이동
	GetFSM()->ChangeState(NextState);
}

