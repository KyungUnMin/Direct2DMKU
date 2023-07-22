#include "PrecompileHeader.h"
#include "PlayerState_NormalDamaged_Stomach.h"

#include "SoundMgr.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_NormalDamaged_Stomach::AniName = "NormalDamaged_Stomach";
const float PlayerState_NormalDamaged_Stomach::AniInterTime = 0.08f;
const std::pair<size_t, size_t> PlayerState_NormalDamaged_Stomach::AniFrame = std::pair<size_t, size_t>{ 4, 7 };

PlayerState_NormalDamaged_Stomach::PlayerState_NormalDamaged_Stomach()
{

}

PlayerState_NormalDamaged_Stomach::~PlayerState_NormalDamaged_Stomach()
{

}

void PlayerState_NormalDamaged_Stomach::Start()
{
	PlayerState_DamagedBase::Start();

	CreateAnimation();
}



void PlayerState_NormalDamaged_Stomach::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = PlayerState_DamagedBase::NormalDamage_FileName,
		.Start = AniFrame.first,
		.End = AniFrame.second,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}


void PlayerState_NormalDamaged_Stomach::EnterState()
{
	PlayerState_DamagedBase::EnterState();
	if (true == PlayerState_DamagedBase::CheckKnockDown())
		return;

	GetRenderer()->ChangeAnimation(AniName);
	SoundMgr::PlaySFX("HitEffective.wav").SetVolume(2.5f);
	SoundMgr::PlaySFX("Player_StomachDamaged_Voice.wav");
}

void PlayerState_NormalDamaged_Stomach::Update(float _DeltaTime)
{
	PlayerState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}

