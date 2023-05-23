#include "PrecompileHeader.h"
#include "CheerleaderState_NormalDamaged_Stomach.h"

#include "CheerleaderFSM.h"

const std::string_view CheerleaderState_NormalDamaged_Stomach::AniName = "NormalDamaged_Stomach";
const std::pair<int, int> CheerleaderState_NormalDamaged_Stomach::AniCutFrame = std::pair<int, int>{ 5, 2 };
const std::pair<size_t, size_t> CheerleaderState_NormalDamaged_Stomach::AniFrameIndex = std::pair<size_t, size_t>{ 3,5 };
const float CheerleaderState_NormalDamaged_Stomach::AniInterTime = 0.08f;

CheerleaderState_NormalDamaged_Stomach::CheerleaderState_NormalDamaged_Stomach()
{

}

CheerleaderState_NormalDamaged_Stomach::~CheerleaderState_NormalDamaged_Stomach()
{

}

void CheerleaderState_NormalDamaged_Stomach::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void CheerleaderState_NormalDamaged_Stomach::LoadAnimation()
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

void CheerleaderState_NormalDamaged_Stomach::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = CheerleaderFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime
		});
}

void CheerleaderState_NormalDamaged_Stomach::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void CheerleaderState_NormalDamaged_Stomach::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(CheerleaderStateType::Idle);
}


