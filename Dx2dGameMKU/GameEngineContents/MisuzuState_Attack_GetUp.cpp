#include "PrecompileHeader.h"
#include "MisuzuState_Attack_GetUp.h"

#include "RCGEnums.h"
#include "DataMgr.h"
#include "SoundMgr.h"

#include "MisuzuFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "HitEffect.h"
#include "FieldLevelBase.h"
#include "FieldCamController.h"



const std::string_view MisuzuState_Attack_GetUp::AniName = "Attack_GetUp";
const std::string_view MisuzuState_Attack_GetUp::AniFileName = "Misuzu_GetUp.png";
const std::pair<int, int> MisuzuState_Attack_GetUp::AniCutFrame = std::pair<int, int>(5, 3);
const float MisuzuState_Attack_GetUp::AniInterTime = 0.08f;
const int MisuzuState_Attack_GetUp::Damage = 5;

MisuzuState_Attack_GetUp::MisuzuState_Attack_GetUp()
{

}

MisuzuState_Attack_GetUp::~MisuzuState_Attack_GetUp()
{

}

void MisuzuState_Attack_GetUp::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	EnemyStateBase::DontLookPlayer();
}

void MisuzuState_Attack_GetUp::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Misuzu");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void MisuzuState_Attack_GetUp::CreateAnimation()
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
		//사운드
		SoundMgr::PlaySFX("Misuzu_GetUp_Voice.wav");
	});
	
	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 6, false, "Misuzu_GetUp_Effect.mp3", 3.f);
}




void MisuzuState_Attack_GetUp::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 400.f);
}



void MisuzuState_Attack_GetUp::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;
	

	
	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(MisuzuStateType::Idle);
		return;
	}

	GetFSM()->ChangeState(MisuzuStateType::Idle);
	return;

	////1/n로 Idle, 나머지는 현재와 다른 공격
	//MisuzuStateType RandomAttack = static_cast<MisuzuStateType>(GetEnemyFsm()->GetRandomAttack());
	//if (GetStateEnum<MisuzuStateType>() == RandomAttack)
	//{
	//	GetFSM()->ChangeState(MisuzuStateType::Idle);
	//}
	//else
	//{
	//	GetFSM()->ChangeState(RandomAttack);
	//}
}


void MisuzuState_Attack_GetUp::Attack()
{
	BossState_AttackBase::Attack();
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face(Damage);
	
}
