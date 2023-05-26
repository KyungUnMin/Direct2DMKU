#include "PrecompileHeader.h"
#include "EnemyState_AttackBase.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "BackGround.h"

FieldEnemyBase* EnemyState_AttackBase::AttackEnemy = nullptr;

EnemyState_AttackBase::EnemyState_AttackBase()
{

}

EnemyState_AttackBase::~EnemyState_AttackBase()
{

}

void EnemyState_AttackBase::Start()
{
	EnemyStateBase::Start();

	AttackCollider = GetEnemy()->GetAttackCollider();
}




void EnemyState_AttackBase::EnterState()
{
	EnemyStateBase::EnterState();
	EnemyDir = EnemyStateBase::IsRightDir();

	AttackEnemy = GetEnemy();
}




void EnemyState_AttackBase::SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index)
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	//n��° �����ӿ� ó���� �ݹ� ���
	EnemyRender->SetAnimationStartEvent(_AniName, _Index,
		std::bind(&EnemyState_AttackBase::AttackCheck, this));
}


void EnemyState_AttackBase::SetAttackColValue(const float4& _Offset, const float4& _Scale)
{
	GameEngineTransform* AttackColTrans = AttackCollider->GetTransform();

	if (_Scale.z < 5.f)
	{
		MsgAssert("Enemy Attack�� �浹���� ���� �߿� Z���� ������־�� �մϴ�");
		return;
	}

	AttackColTrans->SetLocalPosition(_Offset);
	AttackColTrans->SetLocalScale(_Scale);
}


void EnemyState_AttackBase::AttackCheck()
{
	std::shared_ptr<GameEngineCollision> PlayerCol = nullptr;
	PlayerCol = AttackCollider->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D);

	const TransformData& EnemyColData = AttackCollider->GetTransform()->GetTransDataRef();
	const TransformData& PlayerColData = PlayerCol->GetTransform()->GetTransDataRef();

	if (nullptr == PlayerCol)
		return;


	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();
	
	//�÷��̾ �� ���� �����ʿ� �ִ� ���
	if (EnemyColData.WorldPosition.x < PlayerColData.WorldPosition.x)
	{
		//������ �ٶ󺻴�
		PlayerPtr->SetDirection(false);
		//PlayerTrans->SetLocalNegativeScaleX();
	}
	//�÷��̾ �� ���� ���ʿ� �ִ� ���
	else
	{
		//�������� �ٶ󺻴�
		PlayerPtr->SetDirection(true);
		//PlayerTrans->SetLocalPositiveScaleX();
	}

	Attack();
}





void EnemyState_AttackBase::SetMoveEvent(
	const std::string_view& _AniName, size_t _MoveStartFrame, 
	bool _IsReverseDir /*= false*/, float _MoveDuration /*= 0.5f*/, float _StartAcc /*= 1000.f*/)
{
	StartAcc = _StartAcc;
	IsReverseMoveDir = _IsReverseDir;
	MoveDuration = _MoveDuration;

	GetRenderer()->SetAnimationStartEvent(_AniName, _MoveStartFrame, [this]()
	{
		this->MoveOn();
	});
}


void EnemyState_AttackBase::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	//�̺�Ʈ�� ���� �����̴� ��Ȳ�϶���
	if (false == IsMovingAttack)
		return;

	//�̵��� ����(true�� ������, false�� ����)
	bool MoveDir = EnemyDir;
	//Enemy�� �ٶ󺸰� �ִ� ������ ���������� �̵��ϴ� ���
	if (true == IsReverseMoveDir)
	{
		MoveDir = !MoveDir;
	}

	float4 MoveDirVec = MoveDir ? float4::Right : float4::Left;

	float Timer = GetLiveTime() - MoveStartTime;
	float Ratio = (Timer / MoveDuration);
	EnemyStateBase::Update_AccMove(_DeltaTime, Ratio, MoveDirVec, StartAcc);
}



void EnemyState_AttackBase::Update_AccTraceAttack(float _DeltaTime, float _Acc /*= 200.f*/, float _MaxSpeed /*= 200.f*/)
{
	//�÷��̾ ���ϴ� ����
	float4 DirToPlayer = GetVecToPlayer();
	DirToPlayer.Normalize();

	//�׻� �÷��̾� �ٶ󺸱�
	EnemyStateBase::ChangeRenderDirection();

	//���ӵ� ���ϱ�
	TraceVec += DirToPlayer * _Acc * _DeltaTime;

	//�ִ� �ӵ� ���Ѽ�
	if (_MaxSpeed < TraceVec.Size())
	{
		TraceVec.Normalize();
		TraceVec *= _MaxSpeed;
	}


	//������ ������ ��ġ ���
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	float4 NowPos = EnemyTrans->GetLocalPosition();
	float4 NextPos = NowPos + (TraceVec * _DeltaTime);

	//���� ���� ���1
	std::shared_ptr<BackGround> BGPtr = GetBackGround();
	if (true == BGPtr->IsBlockPos(NextPos))
	{
		//ChangeTraceDir(DirToPlayer);
		Rotate90Dir(TraceVec);
		return;
	}

	//���� ���� ���2
	std::pair<int, int> GriNextPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(GriNextPos.first, GriNextPos.second))
	{
		//ChangeTraceDir(DirToPlayer);
		Rotate90Dir(TraceVec);
		return;
	}
	
	//���� �̵�
	EnemyTrans->SetLocalPosition(NextPos);

	//���� ó��
	AttackCheck();
}


void EnemyState_AttackBase::ChangeTraceDir(const float4& _DirToPlayer)
{
	float4 LookDir= TraceVec;
	LookDir.z = 0.f;
	float4 ToPlayer = _DirToPlayer;
	ToPlayer.z = 0.f;

	float4 DotVec = float4::Cross3DReturnNormal(LookDir, ToPlayer);

	
	float4 PrevTraceVec = TraceVec;

	//���������� ȸ���ϴ� ���� ������
	if (DotVec.z < 0.f)
	{
		TraceVec.x = PrevTraceVec.y;
		TraceVec.y = -PrevTraceVec.x;
	}

	//�������� ȸ���ϴ� ���� ������
	else
	{
		TraceVec.x = -PrevTraceVec.y;
		TraceVec.y = PrevTraceVec.x;
	}

	TraceVec.z = TraceVec.y;
}


void EnemyState_AttackBase::Rotate90Dir(float4& _Vec)
{
	float4 PrevTraceVec = _Vec;

	_Vec.x = PrevTraceVec.y;
	_Vec.y = -PrevTraceVec.x;
	_Vec.z = _Vec.y;
}



void EnemyState_AttackBase::ExitState()
{
	EnemyStateBase::ExitState();
	IsMovingAttack = false;
	GetEnemy()->SetHeight(0.f);

	AttackEnemy = nullptr;

	TraceVec = float4::Zero;
}



