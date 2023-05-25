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

	std::shared_ptr<FieldEnemyBase> EnemyPtr = GetEnemy()->DynamicThis<FieldEnemyBase>();

	//�̵��Ϸ��� ��ġ�� �ٸ� Enemy�� �����Ѵٸ� �̵����� �ʰ� �ٸ� ���·� ��ȯ
	if (true == EnemySpawnerPtr->IsOtherStay(EnemyPtr, DestGridPos/*, MoveVolume*/))
	{
		PathStack.clear();
		return false;
	}

	//�̵��Ϸ��� ��ġ�� ���
	EnemySpawnerPtr->MarkGridPos(EnemyPtr, DestGridPos);

	//������ ����
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

	//�� Enemy���� Player ������ ����
	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();
	if (VecToPlayer.Size() < GetSightRadius())
	{
		//�ڽĿ��� �������� ���°����� �̵�
		GetFSM()->ChangeState(NextState);
		return;
	}

	if (Ratio < 1.f)
		return;

	Timer -= MoveDuration;
	if (true == SetDest())
		return;

	//�ڽĿ��� �������� ���°����� �̵�
	GetFSM()->ChangeState(NextState);
}

