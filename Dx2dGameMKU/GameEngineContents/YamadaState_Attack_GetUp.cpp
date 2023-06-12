#include "PrecompileHeader.h"
#include "YamadaState_Attack_GetUp.h"

#include "RCGEnums.h"
#include "DataMgr.h"

#include "YamadaFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "HitEffect.h"
#include "FieldLevelBase.h"
#include "FieldCamController.h"



const std::string_view YamadaState_Attack_GetUp::AniName = "Attack_GetUp";
const std::string_view YamadaState_Attack_GetUp::AniFileName = "Yamada_GetUp.png";
const std::pair<int, int> YamadaState_Attack_GetUp::AniCutFrame = std::pair<int, int>(5, 3);
const float YamadaState_Attack_GetUp::AniInterTime = 0.08f;
const int YamadaState_Attack_GetUp::Damage = 5;

YamadaState_Attack_GetUp::YamadaState_Attack_GetUp()
{

}

YamadaState_Attack_GetUp::~YamadaState_Attack_GetUp()
{

}

void YamadaState_Attack_GetUp::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	EnemyStateBase::DontLookPlayer();
}

void YamadaState_Attack_GetUp::LoadAnimation()
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_Attack_GetUp::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 14,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyRender->SetAnimationStartEvent(AniName, 5, [this]()
	{
		static const float4 Scale = float4{ 2.f, 0.5f };

		std::shared_ptr<HitEffect> Effect = nullptr;
		Effect = this->EnemyState_AttackBase::CreateEffect<HitEffect>(float4::Zero, Scale);
		Effect->OffHitSpark();

		//카메라 쉐이킹
		FieldLevelBase::GetPtr()->GetCameraController().SetShakeState(0.4f);
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 6);
}




void YamadaState_Attack_GetUp::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 400.f);
}



void YamadaState_Attack_GetUp::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;
	

	
	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(YamadaStateType::Idle);
		return;
	}

	GetFSM()->ChangeState(YamadaStateType::Idle);
	return;

	////1/n로 Idle, 나머지는 현재와 다른 공격
	//YamadaStateType RandomAttack = static_cast<YamadaStateType>(GetEnemyFsm()->GetRandomAttack());
	//if (GetStateEnum<YamadaStateType>() == RandomAttack)
	//{
	//	GetFSM()->ChangeState(YamadaStateType::Idle);
	//}
	//else
	//{
	//	GetFSM()->ChangeState(RandomAttack);
	//}
}


void YamadaState_Attack_GetUp::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
