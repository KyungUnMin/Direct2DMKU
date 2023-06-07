#include "PrecompileHeader.h"
#include "EnemyState_AttackBase.h"

#include <GameEngineCore/GameEngineCollision.h>


#include "FieldEnemyBase.h"
#include "FieldPlayer.h"


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




void EnemyState_AttackBase::SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index, bool _IsUpdateCallBack /*= false*/)
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();


	//Start �ִϸ��̼� �ݹ�
	if (false == _IsUpdateCallBack)
	{
		//n��° �����ӿ� ó���� �ݹ� ���
		EnemyRender->SetAnimationStartEvent(_AniName, _Index,
			std::bind(&EnemyState_AttackBase::AttackCheck, this));
	}

	//Update �ִϸ��̼� �ݹ�
	else
	{
		//n��° �����ӿ� ó���� �ݹ� ���
		EnemyRender->SetAnimationUpdateEvent(_AniName, _Index,
			std::bind(&EnemyState_AttackBase::AttackCheck, this));
	}
	
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






void EnemyState_AttackBase::ExitState()
{
	EnemyStateBase::ExitState();
	IsMovingAttack = false;
	GetEnemy()->SetHeight(0.f);

	AttackEnemy = nullptr;
}



void EnemyState_AttackBase::EffectInit(std::shared_ptr<GameEngineActor> _Effect, const float4& _Offset, const float4& _Scale)
{
	if (nullptr == _Effect)
	{
		MsgAssert("Effect �����Ͱ� nullptr�Դϴ�");
		return;
	}

	GameEngineTransform* EffectTrans = _Effect->GetTransform();
	const float4 EnemyPos = GetEnemy()->GetTransform()->GetWorldPosition();

	EffectTrans->SetLocalPosition(EnemyPos + _Offset);
	EffectTrans->SetLocalScale(_Scale);
}