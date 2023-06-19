#include "PrecompileHeader.h"
#include "NoiseState_Attack_Meteor.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DataMgr.h"

#include "NoiseFSM.h"
#include "FieldPlayer.h"
#include "FieldCamController.h"
#include "FieldEnemyBase.h"
#include "HitEffect.h"

const std::vector<NoiseState_Attack_Meteor::AniInfo> NoiseState_Attack_Meteor::AniInfoes =
{
	{
		"Noise_Meteor_JumpUp.png",
		std::pair<int, int>{5,2},
		std::pair<size_t, size_t>{0,5},
		false
	},
	{
		"Noise_Meteor_Jumping.png",
		std::pair<int, int>{5,1},
		std::pair<size_t, size_t>{0,1},
		true,
	},
	{
		"Noise_Meteor_Fall.png",
		std::pair<int, int>{5,1},
		std::pair<size_t, size_t>{0,1},
		true
	},
	{
		"Noise_MeteroMiss.png",
		std::pair<int, int>{5,4},
		std::pair<size_t, size_t>{0,18},
		false
	},
	{
		"Noise_MeteroLanded.png",
		std::pair<int, int>{5,3},
		std::pair<size_t, size_t>{0,11},
		false
	},
};

const float NoiseState_Attack_Meteor::AniInter = 0.08f;
const int NoiseState_Attack_Meteor::Damage = 15;
const int NoiseState_Attack_Meteor::AttackFrm = 8;

NoiseState_Attack_Meteor::NoiseState_Attack_Meteor()
{

}

NoiseState_Attack_Meteor::~NoiseState_Attack_Meteor()
{

}

void NoiseState_Attack_Meteor::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void NoiseState_Attack_Meteor::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Noise");
	Dir.Move("Attack");
	for (const AniInfo& Info : AniInfoes)
	{
		const std::string_view AniFileName = Info.AniName;
		const std::pair<int, int> AniCutFrame = Info.AniCutFram;
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
	}
}

void NoiseState_Attack_Meteor::CreateAnimation()
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




void NoiseState_Attack_Meteor::EnterState()
{
	BossState_AttackBase::EnterState();

	ChangeStateWithAni(State::JumpUp);
	EnemyState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 300.f);
}



void NoiseState_Attack_Meteor::ChangeStateWithAni(State _NextState)
{
	Timer = 0.f;
	CurState = _NextState;
	size_t Index = static_cast<size_t>(CurState);
	GetRenderer()->ChangeAnimation(AniInfoes[Index].AniName);
}


void NoiseState_Attack_Meteor::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	switch (CurState)
	{
	case NoiseState_Attack_Meteor::State::JumpUp:
		Update_JumpUp(_DeltaTime);
		break;
	case NoiseState_Attack_Meteor::State::Jumping:
		Update_JumpingMove(_DeltaTime);
		Update_Jumping(_DeltaTime);
		break;
	case NoiseState_Attack_Meteor::State::Fall:
		Update_FallMove(_DeltaTime);
		Update_Fall(_DeltaTime);
		break;
	case NoiseState_Attack_Meteor::State::Miss:
		Update_Land(_DeltaTime);
		break;
	case NoiseState_Attack_Meteor::State::Land:
		Update_Land(_DeltaTime);
		break;
	}
}

void NoiseState_Attack_Meteor::Update_JumpUp(float _DeltaTime)
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



void NoiseState_Attack_Meteor::Update_Jumping(float _DeltaTime)
{
	Timer += _DeltaTime;
	EnemyStateBase::Update_SinHalfJump(Timer, Duration, MaxHeight);

	if (Timer < Duration)
		return;

	ChangeStateWithAni(State::Fall);
}



void NoiseState_Attack_Meteor::Update_JumpingMove(float _DeltaTime)
{
	BossState_AttackBase::Update_SinHalfMove(Timer, Duration, MoveStartPos, MoveHalfPos);
}




void NoiseState_Attack_Meteor::Update_Fall(float _DeltaTime)
{
	Timer += _DeltaTime;
	EnemyStateBase::Update_SinHalfFall(Timer, Duration, MaxHeight);

	if (Timer < Duration)
		return;

	//플레이어에게 공격한 경우
	if (true == AttackCheck())
	{
		ChangeStateWithAni(State::Land);
	}

	//이상한 곳을 공격한 경우
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

void NoiseState_Attack_Meteor::Update_FallMove(float _DeltaTime)
{
	//Cos이라 목적지와 시작점의 위치가 반대로
	BossState_AttackBase::Update_CosHalfMove(Timer, Duration, MoveHalfPos, MoveDestPos);
}

void NoiseState_Attack_Meteor::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}


void NoiseState_Attack_Meteor::Update_Land(float _DeltaTime) 
{
	Timer += _DeltaTime;
	EnemyStateBase::Update_SinJump(Timer, LandDuration, LandHeight);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}




void NoiseState_Attack_Meteor::ExitState()
{
	BossState_AttackBase::ExitState();

	CurState = State::JumpUp;
	GetEnemy()->SetHeight(0.f);
	Timer = 0.f;

	EnemyStateBase::OnMainCollider();
	FieldCamController* CamCtrl = GetCamCtrl();
	CamCtrl->SetZoom(CamCtrl->ZoomOrigin);
}
