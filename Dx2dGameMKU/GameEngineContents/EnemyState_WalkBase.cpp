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
		MsgAssert("�ڽ��ʿ��� Enemy�� �̵��� ���� �� �ٲ� State�� ���������� �ʾҽ��ϴ�");
		return;
	}
}

bool EnemyState_WalkBase::SetDest()
{
	if (true == PathStack.empty())
		return false;

	std::pair<int, int> DestGridPos = PathStack.back();
	std::shared_ptr<FieldEnemyBase> EnemyPtr = GetEnemy()->DynamicThis<FieldEnemyBase>();


	//���ڸ� ����
	if (true == EnemySpawnerPtr->IsOtherStay(EnemyPtr, DestGridPos))
	{
		StartPos = EnemyPtr->GetTransform()->GetWorldPosition();
		DestPos = StartPos;
		return true;
	}

	PathStack.pop_back();


	//�̵��Ϸ��� ��ġ�� ���(����)
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

	//MoveDuration���� ������ ���� �Ǵ� ���º�ȯ, ��� �缳��
	if (Ratio < 1.f)
		return;

	//�� Enemy���� Player ������ ����
	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();

	//�÷��̾ �þ� �ȿ� ���ö�
	if (VecToPlayer.Size() < GetSightRadius())
	{
		//�ڽĿ��� �������� ���°����� �̵�
		GetFSM()->ChangeState(ArriveState);
		return;
	}


	//���������� �̵��Ϸ��� �������� �÷��̾�� �ʹ� �ָ� ������������ ��θ� �� �����Ѵ�
	if (false == PathStack.empty())
	{
		//�̵��Ϸ��� ���� �������� ��ġ ���ϱ�
		std::shared_ptr<BackGround> BGPtr = GetBackGround();
		const std::pair<int, int>& FinalGridDest = PathStack.front();
		const float4& FinalPos = BGPtr->GetPosFromGrid(FinalGridDest.first, FinalGridDest.second);

		//�̵��Ϸ��� ���� �������� �÷��̾� ������ �Ÿ�
		float DistanceToPlayer = EnemyStateBase::GetVecToPlayer(FinalPos, true).Size();
		//������������ �÷��̾� ���� �Ÿ��� ReFindPathRange���� ũ�� ��θ� �� ����
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

	//�ڽĿ��� �������� ���°����� �̵�
	GetFSM()->ChangeState(ArriveState);
}

