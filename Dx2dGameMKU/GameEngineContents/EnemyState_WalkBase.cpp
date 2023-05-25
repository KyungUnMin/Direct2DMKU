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
	GridMapScale = GetBackGround()->GetGridMapScale();
	EnemySpawnerPtr = &(FieldLevelBase::GetPtr()->GetEnemySpawner());
}

void EnemyState_WalkBase::EnterState()
{
	EnemyStateBase::EnterState();

	FindPath();
	SetDest();

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

	std::shared_ptr<FieldEnemyBase> EnemyPtr = GetEnemy()->DynamicThis<FieldEnemyBase>();

	//이동하려는 위치에 다른 Enemy가 존재한다면 이동하지 않고 다른 상태로 전환
	if (true == EnemySpawnerPtr->IsOtherStay(EnemyPtr, DestGridPos/*, MoveVolume*/))
	{
		PathStack.clear();
		return false;
	}

	//이동하려는 위치를 기록
	EnemySpawnerPtr->MarkGridPos(EnemyPtr, DestGridPos);

	//목적지 설정
	DestPos = GetBackGround()->GetPosFromGrid(DestGridPos.first, DestGridPos.second);
	DestPos.z = DestPos.y;
	StartPos = EnemyPtr->GetTransform()->GetWorldPosition();
	return true;
}




void EnemyState_WalkBase::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	Timer += _DeltaTime;

	float Ratio = (Timer / MoveDuration);
	float4 NextPos = float4::LerpClamp(StartPos, DestPos, Ratio);



	GetEnemy()->GetTransform()->SetWorldPosition(NextPos);

	//이 Enemy에서 Player 까지의 벡터
	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();
	if (VecToPlayer.Size() < GetSightRadius())
	{
		//자식에서 지정해준 상태값으로 이동
		GetFSM()->ChangeState(NextState);
		return;
	}

	if (Ratio < 1.f)
		return;

	Timer -= MoveDuration;
	if (true == SetDest())
		return;

	//자식에서 지정해준 상태값으로 이동
	GetFSM()->ChangeState(NextState);
}

