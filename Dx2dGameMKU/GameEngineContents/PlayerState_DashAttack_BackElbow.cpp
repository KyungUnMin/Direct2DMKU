#include "PrecompileHeader.h"
#include "PlayerState_DashAttack_BackElbow.h"


#include "SoundMgr.h"

#include "FieldPlayer.h"
#include "PlayerFSM.h"
#include "FieldEnemyBase.h"

#include "PlayerState_Idle.h"

const std::string_view PlayerState_DashAttack_BackElbow::AniName = "DashAttack_BackElbow";
const std::string_view PlayerState_DashAttack_BackElbow::AniFileName = "Player_DashAttack_BackElbow.png";
const std::pair<int, int> PlayerState_DashAttack_BackElbow::AniCutFrame = std::pair<int, int>(5, 2);
const float PlayerState_DashAttack_BackElbow::AniInterTime = 0.08f;
const int PlayerState_DashAttack_BackElbow::Damage = 5;
const float PlayerState_DashAttack_BackElbow::IneriaDuration = 0.5f;

PlayerState_DashAttack_BackElbow::PlayerState_DashAttack_BackElbow()
{

}

PlayerState_DashAttack_BackElbow::~PlayerState_DashAttack_BackElbow()
{

}

void PlayerState_DashAttack_BackElbow::Start()
{
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_DashAttack_BackElbow::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("DashAttack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_DashAttack_BackElbow::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 7,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	PlayerState_AttackBase::SetAttackCheckFrame(AniName, 2);
}


void PlayerState_DashAttack_BackElbow::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	static const float4 AttackColPos = float4::Right * 100.f;
	static const float4 AttackColScale = float4::One * 150.f;
	PlayerState_AttackBase::SetAttackColValue(AttackColPos, AttackColScale);

	TotalDamage = Damage + DataMgr::GetPlayerAtt();

	SoundMgr::PlaySFX("Player_BackElbow_Effect.wav");
	SoundMgr::PlaySFX("Player_BackElbow_Voice.wav");

	PlayerState_Idle::AttackCycleEnd();
}





void PlayerState_DashAttack_BackElbow::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

	PlayerState_AttackBase::Update_DashIneria(_DeltaTime, IneriaDuration);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}

void PlayerState_DashAttack_BackElbow::Attack(FieldEnemyBase* _Enemy)
{
	bool Result = _Enemy->OnDamage_Jaw(TotalDamage);
	if (true == Result)
	{
		SoundMgr::PlaySFX("Player_Dash_Hit.wav").SetVolume(2.f);
		PlayerState_AttackBase::CreateHitEffect_Stomach();
	}
}

