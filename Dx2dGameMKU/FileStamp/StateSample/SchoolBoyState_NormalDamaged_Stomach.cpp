#include "PrecompileHeader.h"
#include "SchoolBoyState_NormalDamaged_Stomach.h"

#include "SchoolBoyFSM.h"

const std::string_view SchoolBoyState_NormalDamaged_Stomach::AniName = "NormalDamaged_Stomach";
const std::pair<int, int> SchoolBoyState_NormalDamaged_Stomach::AniCutFrame = std::pair<int, int>{ 5, 2 };
const std::pair<size_t, size_t> SchoolBoyState_NormalDamaged_Stomach::AniFrameIndex = std::pair<size_t, size_t>{ 3,5 };
const float SchoolBoyState_NormalDamaged_Stomach::AniInterTime = 0.08f;

SchoolBoyState_NormalDamaged_Stomach::SchoolBoyState_NormalDamaged_Stomach()
{

}

SchoolBoyState_NormalDamaged_Stomach::~SchoolBoyState_NormalDamaged_Stomach()
{

}

void SchoolBoyState_NormalDamaged_Stomach::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void SchoolBoyState_NormalDamaged_Stomach::LoadAnimation()
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

void SchoolBoyState_NormalDamaged_Stomach::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = SchoolBoyFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime
		});
}

void SchoolBoyState_NormalDamaged_Stomach::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void SchoolBoyState_NormalDamaged_Stomach::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolBoyStateType::Idle);
}


