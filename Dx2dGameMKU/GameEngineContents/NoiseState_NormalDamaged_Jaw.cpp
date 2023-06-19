#include "PrecompileHeader.h"
#include "NoiseState_NormalDamaged_Jaw.h"

#include "NoiseFSM.h"

const std::string_view NoiseState_NormalDamaged_Jaw::AniName = "NormalDamaged_Jaw";
const std::pair<int, int> NoiseState_NormalDamaged_Jaw::AniCutFrame = std::pair<int, int>{ 6, 8 };
const std::pair<size_t, size_t> NoiseState_NormalDamaged_Jaw::AniFrameIndex = std::pair<size_t, size_t>{ 3,5 };
const float NoiseState_NormalDamaged_Jaw::AniInterTime = 0.08f;

NoiseState_NormalDamaged_Jaw::NoiseState_NormalDamaged_Jaw()
{

}

NoiseState_NormalDamaged_Jaw::~NoiseState_NormalDamaged_Jaw()
{

}

void NoiseState_NormalDamaged_Jaw::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void NoiseState_NormalDamaged_Jaw::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(NoiseFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Noise");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(NoiseFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void NoiseState_NormalDamaged_Jaw::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = NoiseFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}

void NoiseState_NormalDamaged_Jaw::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void NoiseState_NormalDamaged_Jaw::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}


