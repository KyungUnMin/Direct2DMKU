#include "PrecompileHeader.h"
#include "NoiseState_Attack_GuitarSlashDash.h"

#include "DataMgr.h"
#include "SoundMgr.h"

#include "NoiseFSM.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"
#include "FieldCamController.h"

const std::string_view NoiseState_Attack_GuitarSlashDash::AniName = "Attack_GuitarSlashDash";
const std::string_view NoiseState_Attack_GuitarSlashDash::AniFileName = "Noise_GuitarSlash.png";
const std::pair<int, int> NoiseState_Attack_GuitarSlashDash::AniCutFrame = std::pair<int, int>(5, 4);
const float NoiseState_Attack_GuitarSlashDash::AniInterTime = 0.08f;
const int NoiseState_Attack_GuitarSlashDash::Damage = 15;
const int NoiseState_Attack_GuitarSlashDash::AttackFrm = 7;

NoiseState_Attack_GuitarSlashDash::NoiseState_Attack_GuitarSlashDash()
{

}

NoiseState_Attack_GuitarSlashDash::~NoiseState_Attack_GuitarSlashDash()
{

}

void NoiseState_Attack_GuitarSlashDash::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	SetSight(300.f);
}

void NoiseState_Attack_GuitarSlashDash::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(AniFileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Noise");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void NoiseState_Attack_GuitarSlashDash::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 15,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	Render->SetAnimationStartEvent(AniName, AttackFrm - 1, []()
	{
		SoundMgr::PlaySFX("Noise_GuitarSlashDash_Effect.wav");
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, AttackFrm);
}




void NoiseState_Attack_GuitarSlashDash::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Right * 150.f, float4::One * 250.f);

	//플레이어를 향해서
	float4 VecToPlayer = GetVecToPlayer();
	StartPos = GetEnemy()->GetTransform()->GetWorldPosition();

	float Sight = GetSightRadius();
	if (Sight < VecToPlayer.Size())
	{
		VecToPlayer.Normalize();
		DestPos = StartPos + (VecToPlayer * Sight);
	}
	else
	{
		DestPos = StartPos + (VecToPlayer * 0.6f);
	}

	IsAttack = false;

	SoundMgr::PlaySFX("Noise_GuitarSlashDash_Voice.wav");
}





void NoiseState_Attack_GuitarSlashDash::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	static const float Duration = AniInterTime * static_cast<float>(AttackFrm);
	Update_SinHalfMove(GetLiveTime(), Duration, StartPos, DestPos);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	if (true == IsAttack)
	{
		GetFSM()->ChangeState(NoiseStateType::Taunt);
	}
	else
	{
		GetFSM()->ChangeState(NoiseStateType::Idle);
	}
}



void NoiseState_Attack_GuitarSlashDash::Attack()
{
	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	float4 LookPos = GetEnemy()->GetTransform()->GetWorldPosition();
	Player->Look(LookPos);

	bool Result = Player->OnDamage_BlowBack(Damage);
	if (false == Result)
		return;

	static const float Duration = 0.5f;
	static const float RotDegree = 2.f;

	FieldCamController* CamCtrl = GetCamCtrl();
	if(true == IsRightDir())
	{
		CamCtrl->SetRoll(-RotDegree);
	}
	else
	{
		CamCtrl->SetRoll(RotDegree);
	}

	CamCtrl->SetRoll(0.f, Duration);
	IsAttack = true;
}

