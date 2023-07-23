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

	//5��° �����ӿ��� ī�޶� ����ŷ
	Render->SetAnimationStartEvent(AniName, 5, [this]()
	{
		GetCamCtrl()->SetShakeState(0.5f, 10.f);
		SoundMgr::PlaySFX("Misuzu_Roar_Effect.wav").SetVolume(3.f);
	});

	//6��°~9��° �����ӿ��� ����Ʈ
	for (size_t i = 6; i < 10; ++i)
	{
		Render->SetAnimationStartEvent(AniName, i, [this]()
		{
			std::shared_ptr<HitEffect> Effect = nullptr;
			Effect = CreateEffect<HitEffect>(float4::Up * 100.f);
			Effect->OffHitSpark();
		});
	}

	//5��°~9��° �����ӿ��� �浹 ����
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

	//������ ���� ���״ٸ�
	if (true == IsAttackOk)
	{
		GetFSM()->ChangeState(MisuzuStateType::WUPunch);
		return;
	}


	//���� ���� �ۿ� �ִٸ� idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(MisuzuStateType::Idle);
		return;
	}

	//���� ���� �ȿ� �ִٸ� �� ��ġ ����
	GetFSM()->ChangeState(MisuzuStateType::WUPunch);
}



void MisuzuState_Attack_Roar::Attack()
{
	//ù ���� ���ݸ�
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