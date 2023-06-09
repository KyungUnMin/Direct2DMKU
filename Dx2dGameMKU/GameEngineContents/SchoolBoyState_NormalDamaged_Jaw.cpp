#include "PrecompileHeader.h"
#include "SchoolBoyState_NormalDamaged_Jaw.h"

#include "SchoolBoyFSM.h"

const std::string_view SchoolBoyState_NormalDamaged_Jaw::AniName = "NormalDamaged_Jaw";
const std::pair<int, int> SchoolBoyState_NormalDamaged_Jaw::AniCutFrame = std::pair<int, int>{ 5, 2 };
const std::pair<size_t, size_t> SchoolBoyState_NormalDamaged_Jaw::AniFrameIndex = std::pair<size_t, size_t>{ 6,8 };
const float SchoolBoyState_NormalDamaged_Jaw::AniInterTime = 0.08f;

SchoolBoyState_NormalDamaged_Jaw::SchoolBoyState_NormalDamaged_Jaw()
{

}

SchoolBoyState_NormalDamaged_Jaw::~SchoolBoyState_NormalDamaged_Jaw()
{

}

void SchoolBoyState_NormalDamaged_Jaw::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void SchoolBoyState_NormalDamaged_Jaw::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(SchoolBoyFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolBoy");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(SchoolBoyFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void SchoolBoyState_NormalDamaged_Jaw::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = SchoolBoyFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}

void SchoolBoyState_NormalDamaged_Jaw::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void SchoolBoyState_NormalDamaged_Jaw::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolBoyStateType::Idle);
}


