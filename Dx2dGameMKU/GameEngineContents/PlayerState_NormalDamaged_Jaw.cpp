#include "PrecompileHeader.h"
#include "PlayerState_NormalDamaged_Jaw.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_NormalDamaged_Jaw::AniName = "NormalDamaged_Jaw";
const float PlayerState_NormalDamaged_Jaw::AniInterTime = 0.08f;
const std::pair<size_t, size_t> PlayerState_NormalDamaged_Jaw::AniFrame = std::pair<size_t, size_t>{ 8, 11 };

PlayerState_NormalDamaged_Jaw::PlayerState_NormalDamaged_Jaw()
{

}

PlayerState_NormalDamaged_Jaw::~PlayerState_NormalDamaged_Jaw()
{

}

void PlayerState_NormalDamaged_Jaw::Start()
{
	PlayerState_DamagedBase::Start();

	CreateAnimation();
}



void PlayerState_NormalDamaged_Jaw::CreateAnimation()
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


void PlayerState_NormalDamaged_Jaw::EnterState()
{
	PlayerState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void PlayerState_NormalDamaged_Jaw::Update(float _DeltaTime)
{
	PlayerState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}

