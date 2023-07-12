#include "PrecompileHeader.h"
#include "NoiseState_NormalDamaged_Face.h"

#include "NoiseFSM.h"

const std::string_view NoiseState_NormalDamaged_Face::AniName = "NormalDamaged_Face";
const std::pair<int, int> NoiseState_NormalDamaged_Face::AniCutFrame = std::pair<int, int>{5, 2};
const std::pair<size_t, size_t> NoiseState_NormalDamaged_Face::AniFrameIndex = std::pair<size_t, size_t>{ 0, 2 };
const float NoiseState_NormalDamaged_Face::AniInterTime = 0.08f;

NoiseState_NormalDamaged_Face::NoiseState_NormalDamaged_Face()
{

}

NoiseState_NormalDamaged_Face::~NoiseState_NormalDamaged_Face()
{

}

void NoiseState_NormalDamaged_Face::Start() 
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void NoiseState_NormalDamaged_Face::LoadAnimation()
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

void NoiseState_NormalDamaged_Face::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = NoiseFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}

void NoiseState_NormalDamaged_Face::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	SoundMgr::PlaySFX("Noise_FaceDamaged.wav");
}

void NoiseState_NormalDamaged_Face::Update(float _DeltaTime) 
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}


