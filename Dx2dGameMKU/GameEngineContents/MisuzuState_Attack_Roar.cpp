#include "PrecompileHeader.h"
#include "MisuzuState_Attack_Roar.h"

#include "DataMgr.h"
#include "FieldCamController.h"
#include "SoundMgr.h"

#include "MisuzuFSM.h"
#include "FieldPlayer.h"
#include "HitEffect.h"

const std::string_view MisuzuState_Attack_Roar::AniName = "Attack_Roar";
const std::string_view MisuzuState_Attack_Roar::AniFileName = "Misuzu_Roar.png";
const std::pair<int, int> MisuzuState_Attack_Roar::AniCutFrame = std::pair<int, int>(5, 3);
const float MisuzuState_Attack_Roar::AniInterTime = 0.08f;
const int MisuzuState_Attack_Roar::Damage = 1;

MisuzuState_Attack_Roar::MisuzuState_Attack_Roar()
{

}

MisuzuState_Attack_Roar::~MisuzuState_Attack_Roar()
{

}

void MisuzuState_Attack_Roar::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	EnemyStateBase::SetSight(80.f);
}

void MisuzuState_Attack_Roar::LoadAnimation()
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

void MisuzuState_Attack_Roar::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 11,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	//5번째 프레임에서 카메라 쉐이킹
	Render->SetAnimationStartEvent(AniName, 5, [this]()
	{
		GetCamCtrl()->SetShakeState(0.5f, 10.f);
		SoundMgr::PlaySFX("Misuzu_Roar_Effect.wav").SetVolume(3.f);
	});

	//6번째~9번째 프레임에서 이펙트
	for (size_t i = 6; i < 10; ++i)
	{
		Render->SetAnimationStartEvent(AniName, i, [this]()
		{
			std::shared_ptr<HitEffect> Effect = nullptr;
			Effect = CreateEffect<HitEffect>(float4::Up * 100.f);
			Effect->OffHitSpark();
		});
	}

	//5번째~9번째 프레임에서 충돌 검출
	for (size_t i = 5; i < 10; ++i)
	{
		EnemyState_AttackBase::SetAttackCheckFrame(AniName, i, true);
	}
}


void MisuzuState_Attack_Roar::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 200.f);

	SoundMgr::PlaySFX("Misuzu_Roar_Voice.wav").SetVolume(3.f);
}





void MisuzuState_Attack_Roar::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//공격을 적중 시켰다면
	if (true == IsAttackOk)
	{
		GetFSM()->ChangeState(MisuzuStateType::WUPunch);
		return;
	}


	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(MisuzuStateType::Idle);
		return;
	}

	//일정 범위 안에 있다면 강 펀치 공격
	GetFSM()->ChangeState(MisuzuStateType::WUPunch);
}



void MisuzuState_Attack_Roar::Attack()
{
	//첫 적중 공격만
	if (true == IsAttackOk)
		return;

	bool Result = FieldPlayer::GetPtr()->OnDamage_Stun(Damage, true);
	if (false == Result)
		return;

	IsAttackOk = true;
}


void MisuzuState_Attack_Roar::ExitState()
{
	BossState_AttackBase::ExitState();
	IsAttackOk = false;
}