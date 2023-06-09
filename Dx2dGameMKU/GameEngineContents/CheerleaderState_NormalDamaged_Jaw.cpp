#include "PrecompileHeader.h"
#include "CheerleaderState_NormalDamaged_Jaw.h"

#include "CheerleaderFSM.h"

const std::string_view CheerleaderState_NormalDamaged_Jaw::AniName = "NormalDamaged_Jaw";
const std::pair<int, int> CheerleaderState_NormalDamaged_Jaw::AniCutFrame = std::pair<int, int>{ 5, 2 };
const std::pair<size_t, size_t> CheerleaderState_NormalDamaged_Jaw::AniFrameIndex = std::pair<size_t, size_t>{ 6,8 };
const float CheerleaderState_NormalDamaged_Jaw::AniInterTime = 0.08f;

CheerleaderState_NormalDamaged_Jaw::CheerleaderState_NormalDamaged_Jaw()
{

}

CheerleaderState_NormalDamaged_Jaw::~CheerleaderState_NormalDamaged_Jaw()
{

}

void CheerleaderState_NormalDamaged_Jaw::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void CheerleaderState_NormalDamaged_Jaw::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(CheerleaderFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cheerleader");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(CheerleaderFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void CheerleaderState_NormalDamaged_Jaw::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = CheerleaderFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}

void CheerleaderState_NormalDamaged_Jaw::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void CheerleaderState_NormalDamaged_Jaw::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(CheerleaderStateType::Idle);
}


