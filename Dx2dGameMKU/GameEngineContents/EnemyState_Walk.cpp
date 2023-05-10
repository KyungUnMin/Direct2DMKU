#include "PrecompileHeader.h"
#include "EnemyState_Walk.h"


#include "FieldEnemyBase.h"
#include "FieldLevelBase.h"
#include "BackGround.h"



EnemyState_Walk::EnemyState_Walk()
{

}

EnemyState_Walk::~EnemyState_Walk()
{

}


void EnemyState_Walk::Start()
{
	EnemyStateBase::Start();

	FsmPtr = GetConvertFSM<EnemyFSM>();
	EnemyPtr = FsmPtr->GetEnemy();
	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
	GridMapScale = BGPtr->GetGridMapScale();
}

void EnemyState_Walk::EnterState()
{
	EnemyStateBase::EnterState();

	FindPath();
	SetDest();
}

bool EnemyState_Walk::SetDest()
{
	if (true == PathStack.empty())
		return false;

	std::pair<int, int> DestGridPos = PathStack.back();
	PathStack.pop_back();

	DestPos = BGPtr->GetPosFromGrid(DestGridPos.first, DestGridPos.second);
	StartPos = EnemyPtr->GetTransform()->GetWorldPosition();
	return true;
}




void EnemyState_Walk::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	if (nullptr != EnemyStateBase::CheckCallback && true == EnemyStateBase::CheckCallback())
		return;

	Timer += _DeltaTime;

	float Ratio = (Timer / MoveDuration);
	float4 NextPos = float4::LerpClamp(StartPos, DestPos, Ratio);
	EnemyPtr->GetTransform()->SetWorldPosition(NextPos);

	if (Ratio < 1.f)
		return;

	Timer -= MoveDuration;
	if (true == SetDest())
		return;

	FsmPtr->ChangeState(EnemyStateType::Idle);
}

