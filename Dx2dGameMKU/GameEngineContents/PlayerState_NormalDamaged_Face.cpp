#include "PrecompileHeader.h"
#include "PlayerState_NormalDamaged_Face.h"

#include "SoundMgr.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_NormalDamaged_Face::AniName = "NormalDamaged_Face";
const float PlayerState_NormalDamaged_Face::AniInterTime = 0.08f;
const std::pair<size_t, size_t> PlayerState_NormalDamaged_Face::AniFrame = std::pair<size_t, size_t>{ 0, 3 };

PlayerState_NormalDamaged_Face::PlayerState_NormalDamaged_Face()
{

}

PlayerState_NormalDamaged_Face::~PlayerState_NormalDamaged_Face()
{

}

void PlayerState_NormalDamaged_Face::Start()
{
	PlayerState_DamagedBase::Start();

	CreateAnimation();
}



void PlayerState_NormalDamaged_Face::CreateAnimation()
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


void PlayerState_NormalDamaged_Face::EnterState()
{
	PlayerState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	SoundMgr::PlaySFX("HitEffective.wav").SetVolume(2.5f);
	SoundMgr::PlaySFX("Player_FaceDamaged_Voice.wav");
}

void PlayerState_NormalDamaged_Face::Update(float _DeltaTime)
{
	PlayerState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}

