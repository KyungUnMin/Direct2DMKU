#include "PrecompileHeader.h"
#include "YamadaState_Attack_Meteor.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DataMgr.h"

#include "YamadaFSM.h"
#include "FieldPlayer.h"
#include "FieldCamController.h"
#include "FieldEnemyBase.h"
#include "HitEffect.h"

const std::vector<YamadaState_Attack_Meteor::AniInfo> YamadaState_Attack_Meteor::AniInfoes =
{
	{
		"Yamada_Meteor_JumpUp.png",
		std::pair<int, int>{5,2},
		std::pair<size_t, size_t>{0,5},
		false
	},
	{
		"Yamada_Meteor_Jumping.png",
		std::pair<int, int>{5,1},
		std::pair<size_t, size_t>{0,1},
		true,
	},
	{
		"Yamada_Meteor_Fall.png",
		std::pair<int, int>{5,1},
		std::pair<size_t, size_t>{0,1},
		true
	},
	{
		"Yamada_MeteroMiss.png",
		std::pair<int, int>{5,4},
		std::pair<size_t, size_t>{0,18},
		false
	},
	{
		"Yamada_MeteroLanded.png",
		std::pair<int, int>{5,3},
		std::pair<size_t, size_t>{0,11},
		false
	},
};

const float YamadaState_Attack_Meteor::AniInter = 0.08f;
const int YamadaState_Attack_Meteor::Damage = 15;
const int YamadaState_Attack_Meteor::AttackFrm = 8;

YamadaState_Attack_Meteor::YamadaState_Attack_Meteor()
{

}

YamadaState_Attack_Meteor::~YamadaState_Attack_Meteor()
{

}

void YamadaState_Attack_Meteor::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void YamadaState_Attack_Meteor::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Yamada");
	Dir.Move("Attack");
	for (const AniInfo& Info : AniInfoes)
	{
		const std::string_view AniFileName = Info.AniName;
		const std::pair<int, int> AniCutFrame = Info.AniCutFram;
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
	}
}

void YamadaState_Attack_Meteor::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	for (const AniInfo& Info : AniInfoes)
	{
		const std::string_view AniName = Info.AniName;
		const std::pair<size_t, size_t> AniFrm = Info.AniFrm;

		Render->CreateAnimation
		({
			.AnimationName = AniName,
			.SpriteName = AniName,
			.Start = AniFrm.first,
			.End = AniFrm.second,
			.FrameInter = AniInter,
			.Loop = Info.Loop,
		});
	}

}




void YamadaState_Attack_Meteor::EnterState()
{
	BossState_AttackBase::EnterState();

	ChangeStateWithAni(State::JumpUp);
	EnemyState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 300.f);
}



void YamadaState_Attack_Meteor::ChangeStateWithAni(State _NextState)
{
	Timer = 0.f;
	CurState = _NextState;
	size_t Index = static_cast<size_t>(CurState);
	GetRenderer()->ChangeAnimation(AniInfoes[Index].AniName);
}


void YamadaState_Attack_Meteor::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	switch (CurState)
	{
	case YamadaState_Attack_Meteor::State::JumpUp:
		Update_JumpUp(_DeltaTime);
		break;
	case YamadaState_Attack_Meteor::State::Jumping:
		Update_JumpingMove(_DeltaTime);
		Update_Jumping(_DeltaTime);
		break;
	case YamadaState_Attack_Meteor::State::Fall:
		Update_FallMove(_DeltaTime);
		Update_Fall(_DeltaTime);
		break;
	case YamadaState_Attack_Meteor::State::Miss:
		Update_Land(_DeltaTime);
		break;
	case YamadaState_Attack_Meteor::State::Land:
		Update_Land(_DeltaTime);
		break;
	}
}

void YamadaState_Attack_Meteor::Update_JumpUp(float _DeltaTime)
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	if (false == Render->IsAnimationEnd())
		return;

	MoveStartPos = GetEnemy()->GetTransform()->GetLocalPosition();
	MoveDestPos = MoveStartPos + BossState_AttackBase::GetVecToExpectPlayerPos();
	MoveHalfPos = (MoveDestPos - MoveStartPos).half();
	MoveHalfPos = (MoveStartPos + MoveHalfPos);

	EnemyStateBase::OffMainCollider();
	ChangeStateWithAni(State::Jumping);
}



void YamadaState_Attack_Meteor::Update_Jumping(float _DeltaTime)
{
	Timer += _DeltaTime;
	EnemyStateBase::Update_SinHalfJump(Timer, Duration, MaxHeight);

	if (Timer < Duration)
		return;

	ChangeStateWithAni(State::Fall);
}



void YamadaState_Attack_Meteor::Update_JumpingMove(float _DeltaTime)
{
	BossState_AttackBase::Update_SinHalfMove(Timer, Duration, MoveStartPos, MoveHalfPos);
}




void YamadaState_Attack_Meteor::Update_Fall(float _DeltaTime)
{
	Timer += _DeltaTime;
	EnemyStateBase::Update_SinHalfFall(Timer, Duration, MaxHeight);

	if (Timer < Duration)
		return;

	//�÷��̾�� ������ ���
	if (true == AttackCheck())
	{
		ChangeStateWithAni(State::Land);
	}

	//�̻��� ���� ������ ���
	else
	{
		ChangeStateWithAni(State::Miss);
	}

	EnemyStateBase::OnMainCollider();
	CreateEffect<HitEffect>()->OffHitSpark();

	FieldCamController* CamCtrl = GetCamCtrl();
	CamCtrl->SetZoom(0.95f);
	CamCtrl->SetZoom(CamCtrl->ZoomOrigin, 0.1f);
}

void YamadaState_Attack_Meteor::Update_FallMove(float _DeltaTime)
{
	//Cos�̶� �������� �������� ��ġ�� �ݴ��
	BossState_AttackBase::Update_CosHalfMove(Timer, Duration, MoveHalfPos, MoveDestPos);
}

void YamadaState_Attack_Meteor::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}


void YamadaState_Attack_Meteor::Update_Land(float _DeltaTime) 
{
	Timer += _DeltaTime;
	EnemyStateBase::Update_SinJump(Timer, LandDuration, LandHeight);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::Idle);
}




void YamadaState_Attack_Meteor::ExitState()
{
	BossState_AttackBase::ExitState();

	CurState = State::JumpUp;
	GetEnemy()->SetHeight(0.f);
	Timer = 0.f;

	EnemyStateBase::OnMainCollider();
	FieldCamController* CamCtrl = GetCamCtrl();
	CamCtrl->SetZoom(CamCtrl->ZoomOrigin);
}
