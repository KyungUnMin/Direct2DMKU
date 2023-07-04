#include "PrecompileHeader.h"
#include "PlayerState_UniqueAttack_HyrricaneKick.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "DataMgr.h"
#include "SoundMgr.h"
#include "FieldCamController.h"

#include "PlayerFSM.h"
#include "FieldLevelBase.h"
#include "FieldEnemyBase.h"

const int PlayerState_UniqueAttack_HyrricaneKick::NeedMp = 30;

const std::string_view PlayerState_UniqueAttack_HyrricaneKick::AniName = "UniqueAttack_HyrricaneKick";
const std::string_view PlayerState_UniqueAttack_HyrricaneKick::AniFileName = "Player_UniqueAttack_HyrricaneKick.png";
const std::pair<int, int> PlayerState_UniqueAttack_HyrricaneKick::AniCutFrame = std::pair<int, int>(7, 4);
const float PlayerState_UniqueAttack_HyrricaneKick::AniInterTime = 0.05f;
const int PlayerState_UniqueAttack_HyrricaneKick::Damage = 5;
const float PlayerState_UniqueAttack_HyrricaneKick::EffectRange = 100.f;


PlayerState_UniqueAttack_HyrricaneKick::PlayerState_UniqueAttack_HyrricaneKick()
{

}

PlayerState_UniqueAttack_HyrricaneKick::~PlayerState_UniqueAttack_HyrricaneKick()
{

}

void PlayerState_UniqueAttack_HyrricaneKick::Start()
{
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	CamCtrl = &(FieldLevelBase::GetPtr()->GetCameraController());
}

void PlayerState_UniqueAttack_HyrricaneKick::LoadAnimation()
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
	Dir.Move("UniqueAttack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_UniqueAttack_HyrricaneKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 23,
		.FrameInter = AniInterTime,
		.Loop = false
	});

	//나중에 Attack함수 내에서 인트로 구분한다거나 하자
	for (size_t i = 5; i < 20; ++i)
	{
		PlayerState_AttackBase::SetAttackCheckFrame(AniName, i);
	}
}

void PlayerState_UniqueAttack_HyrricaneKick::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	DataMgr::MinusPlayerMP(NeedMp);
	PlayerState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 200.f);
	TotalDamage = Damage + DataMgr::GetPlayerAtt();

	SoundMgr::PlaySFX("Player_HyrricaneKick_Effect.wav");
	SoundMgr::PlaySFX("Player_HyrricaneKick_Voice.wav");
}




void PlayerState_UniqueAttack_HyrricaneKick::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//TODO

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

}



void PlayerState_UniqueAttack_HyrricaneKick::Attack(FieldEnemyBase* _Enemy)
{
	//처음 공격을 맞췄을때
	if (false == IsHit)
	{
		CamCtrl->SetShakeState(0.5f);
		IsHit = true;
	}

	bool IsHited = false;
	size_t CurFrame = GetRenderer()->GetCurrentFrame();
	if (19 == CurFrame)
	{
		IsHited = _Enemy->OnDamage_BlowBack(TotalDamage);
	}
	else if (0 == (CurFrame % 2))
	{
		IsHited = _Enemy->OnDamage_Face(TotalDamage);
	}
	else
	{
		IsHited = _Enemy->OnDamage_Jaw(TotalDamage);
	}

	//공격이 정상적으로 맞았다면
	if (false == IsHited)
		return;

	static const float4 EffectPivot = float4::Up * 100.f;
	static float4 EffectOffset = float4::Zero;
	EffectOffset.x = GameEngineRandom::MainRandom.RandomFloat(-EffectRange, EffectRange);
	EffectOffset.y = GameEngineRandom::MainRandom.RandomFloat(0.f, EffectRange * 0.5f);

	SoundMgr::PlaySFX("HitEffective.wav").SetVolume(2.5f);
	PlayerState_AttackBase::CreateHitEffect(EffectPivot + EffectOffset);
}

void PlayerState_UniqueAttack_HyrricaneKick::ExitState()
{
	PlayerState_AttackBase::ExitState();
	IsHit = false;
}


