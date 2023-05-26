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

	//n번째 프레임에 처리할 콜백 등록
	EnemyRender->SetAnimationStartEvent(_AniName, _Index,
		std::bind(&EnemyState_AttackBase::AttackCheck, this));
}


void EnemyState_AttackBase::SetAttackColValue(const float4& _Offset, const float4& _Scale)
{
	GameEngineTransform* AttackColTrans = AttackCollider->GetTransform();

	if (_Scale.z < 5.f)
	{
		MsgAssert("Enemy Attack의 충돌범위 설정 중에 Z값도 고려해주어야 합니다");
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
	
	//플레이어가 적 기준 오른쪽에 있는 경우
	if (EnemyColData.WorldPosition.x < PlayerColData.WorldPosition.x)
	{
		//왼쪽을 바라본다
		PlayerPtr->SetDirection(false);
		//PlayerTrans->SetLocalNegativeScaleX();
	}
	//플레이어가 적 기준 왼쪽에 있는 경우
	else
	{
		//오른쪽을 바라본다
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

	//이벤트를 통해 움직이는 상황일때만
	if (false == IsMovingAttack)
		return;

	//이동할 방향(true면 오른쪽, false면 왼쪽)
	bool MoveDir = EnemyDir;
	//Enemy가 바라보고 있는 방향의 역방향으로 이동하는 경우
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
	//플레이어를 향하는 방향
	float4 DirToPlayer = GetVecToPlayer();
	DirToPlayer.Normalize();

	//항상 플레이어 바라보기
	EnemyStateBase::ChangeRenderDirection();

	//가속도 더하기
	TraceVec += DirToPlayer * _Acc * _DeltaTime;

	//최대 속도 상한선
	if (_MaxSpeed < TraceVec.Size())
	{
		TraceVec.Normalize();
		TraceVec *= _MaxSpeed;
	}


	//다음에 움직일 위치 계산
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	float4 NowPos = EnemyTrans->GetLocalPosition();
	float4 NextPos = NowPos + (TraceVec * _DeltaTime);

	//벽에 막힌 경우1
	std::shared_ptr<BackGround> BGPtr = GetBackGround();
	if (true == BGPtr->IsBlockPos(NextPos))
	{
		//ChangeTraceDir(DirToPlayer);
		Rotate90Dir(TraceVec);
		return;
	}

	//벽에 막힌 경우2
	std::pair<int, int> GriNextPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(GriNextPos.first, GriNextPos.second))
	{
		//ChangeTraceDir(DirToPlayer);
		Rotate90Dir(TraceVec);
		return;
	}
	
	//실제 이동
	EnemyTrans->SetLocalPosition(NextPos);

	//공격 처리
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

	//오른쪽으로 회전하는 것이 빠를때
	if (DotVec.z < 0.f)
	{
		TraceVec.x = PrevTraceVec.y;
		TraceVec.y = -PrevTraceVec.x;
	}

	//왼쪽으로 회전하는 것이 빠를때
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



