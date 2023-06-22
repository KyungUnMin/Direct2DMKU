#include "PrecompileHeader.h"
#include "NoiseState_Attack_GuitarSlash.h"

#include "DataMgr.h"

#include "NoiseFSM.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"
#include "FieldCamController.h"

const std::string_view NoiseState_Attack_GuitarSlash::AniName = "Attack_GuitarSlash";
const std::string_view NoiseState_Attack_GuitarSlash::AniFileName = "Noise_GuitarSlash.png";
const std::pair<int, int> NoiseState_Attack_GuitarSlash::AniCutFrame = std::pair<int, int>(5, 4);
const float NoiseState_Attack_GuitarSlash::AniInterTime = 0.06f;
const int NoiseState_Attack_GuitarSlash::Damage = 15;
const int NoiseState_Attack_GuitarSlash::AttackFrm = 7;

NoiseState_Attack_GuitarSlash::NoiseState_Attack_GuitarSlash()
{

}

NoiseState_Attack_GuitarSlash::~NoiseState_Attack_GuitarSlash()
{

}

void NoiseState_Attack_GuitarSlash::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void NoiseState_Attack_GuitarSlash::LoadAnimation()
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

void NoiseState_Attack_GuitarSlash::CreateAnimation()
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

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, AttackFrm);
}




void NoiseState_Attack_GuitarSlash::EnterState()
{
	BossState_AttackBase::EnterState();

	FieldCamController* CamCtrl = GetCamCtrl();
	float ZoomOffset = (CamCtrl->ZoomOrigin - 0.05f);
	CamCtrl->SetZoom(ZoomOffset, 7.f * AniInterTime);
	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Right * 150.f, float4::One * 250.f);
}




void NoiseState_Attack_GuitarSlash::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}



void NoiseState_Attack_GuitarSlash::Attack()
{
	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	float4 LookPos = GetEnemy()->GetTransform()->GetWorldPosition();
	Player->Look(LookPos);

	bool Result = Player->OnDamage_BlowBack();
	if (false == Result)
		return;

	FieldCamController* CamCtrl = GetCamCtrl();
	CamCtrl->SetZoomFix();
	CamCtrl->SetShakeState(0.1f, 20.f);
	DataMgr::MinusPlayerHP(Damage);
}


void NoiseState_Attack_GuitarSlash::ExitState()
{
	BossState_AttackBase::ExitState();

	FieldCamController* CamCtrl = GetCamCtrl();
	CamCtrl->SetZoom(CamCtrl->ZoomOrigin, 0.2f);
}
