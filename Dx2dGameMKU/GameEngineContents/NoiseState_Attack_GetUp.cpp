#include "PrecompileHeader.h"
#include "NoiseState_Attack_GetUp.h"

#include "RCGEnums.h"
#include "DataMgr.h"

#include "NoiseFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "HitEffect.h"
#include "FieldLevelBase.h"
#include "FieldCamController.h"



const std::string_view NoiseState_Attack_GetUp::AniName = "Attack_GetUp";
const std::string_view NoiseState_Attack_GetUp::AniFileName = "Noise_GetUp.png";
const std::pair<int, int> NoiseState_Attack_GetUp::AniCutFrame = std::pair<int, int>(5, 3);
const float NoiseState_Attack_GetUp::AniInterTime = 0.08f;
const int NoiseState_Attack_GetUp::Damage = 5;

NoiseState_Attack_GetUp::NoiseState_Attack_GetUp()
{

}

NoiseState_Attack_GetUp::~NoiseState_Attack_GetUp()
{

}

void NoiseState_Attack_GetUp::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	EnemyStateBase::DontLookPlayer();
}

void NoiseState_Attack_GetUp::LoadAnimation()
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void NoiseState_Attack_GetUp::CreateAnimation()
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

		//ī�޶� ����ŷ
		FieldLevelBase::GetPtr()->GetCameraController().SetShakeState(0.4f);
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 6);
}




void NoiseState_Attack_GetUp::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 400.f);
}



void NoiseState_Attack_GetUp::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;
	

	
	//���� ���� �ۿ� �ִٸ� idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(NoiseStateType::Idle);
		return;
	}

	GetFSM()->ChangeState(NoiseStateType::Idle);
	return;

	////1/n�� Idle, �������� ����� �ٸ� ����
	//NoiseStateType RandomAttack = static_cast<NoiseStateType>(GetEnemyFsm()->GetRandomAttack());
	//if (GetStateEnum<NoiseStateType>() == RandomAttack)
	//{
	//	GetFSM()->ChangeState(NoiseStateType::Idle);
	//}
	//else
	//{
	//	GetFSM()->ChangeState(RandomAttack);
	//}
}


void NoiseState_Attack_GetUp::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
