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

	Timer = 0.f;
	FindPath();
	SetDest();

	if (-1 == ArriveState)
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
	std::shared_ptr<FieldEnemyBase> EnemyPtr = GetEnemy()->DynamicThis<FieldEnemyBase>();


	//제자리 걸음
	if (true == EnemySpawnerPtr->IsOtherStay(EnemyPtr, DestGridPos))
	{
		StartPos = EnemyPtr->GetTransform()->GetWorldPosition();
		DestPos = StartPos;
		return true;
	}

	PathStack.pop_back();


	//이동하려는 위치를 기록(예약)
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

	//MoveDuration마다 목적지 설정 또는 상태변환, 경로 재설정
	if (Ratio < 1.f)
		return;

	//이 Enemy에서 Player 까지의 벡터
	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();

	//플레이어가 시야 안에 들어올때
	if (VecToPlayer.Size() < GetSightRadius())
	{
		//자식에서 지정해준 상태값으로 이동
		GetFSM()->ChangeState(ArriveState);
		return;
	}


	//최종적으로 이동하려던 목적지가 플레이어와 너무 멀리 떨어져있으면 경로를 재 설정한다
	if (false == PathStack.empty())
	{
		//이동하려던 최종 목적지의 위치 구하기
		std::shared_ptr<BackGround> BGPtr = GetBackGround();
		const std::pair<int, int>& FinalGridDest = PathStack.front();
		const float4& FinalPos = BGPtr->GetPosFromGrid(FinalGridDest.first, FinalGridDest.second);

		//이동하려던 최종 목적지와 플레이어 사이의 거리
		float DistanceToPlayer = EnemyStateBase::GetVecToPlayer(FinalPos, true).Size();
		//최종목적지와 플레이어 사이 거리가 ReFindPathRange보다 크면 경로를 재 설정
		if (ReFindPathRange < DistanceToPlayer)
		{
			FindPath();
			SetDest();
			EnemyStateBase::ChangeRenderDirection();
			return;
		}
	}


	Timer -= MoveDuration;
	if (true == SetDest())
		return;

	//자식에서 지정해준 상태값으로 이동
	GetFSM()->ChangeState(ArriveState);
}

