#include "PrecompileHeader.h"
#include "MisuzuState_NormalDamaged_Stomach.h"

#include "MisuzuFSM.h"

const std::string_view MisuzuState_NormalDamaged_Stomach::AniName = "NormalDamaged_Stomach";
const std::pair<int, int> MisuzuState_NormalDamaged_Stomach::AniCutFrame = std::pair<int, int>{ 5, 2 };
const std::pair<size_t, size_t> MisuzuState_NormalDamaged_Stomach::AniFrameIndex = std::pair<size_t, size_t>{ 0,2 };
const float MisuzuState_NormalDamaged_Stomach::AniInterTime = 0.08f;

MisuzuState_NormalDamaged_Stomach::MisuzuState_NormalDamaged_Stomach()
{

}

MisuzuState_NormalDamaged_Stomach::~MisuzuState_NormalDamaged_Stomach()
{

}

void MisuzuState_NormalDamaged_Stomach::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void MisuzuState_NormalDamaged_Stomach::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(MisuzuFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Misuzu");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(MisuzuFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void MisuzuState_NormalDamaged_Stomach::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = MisuzuFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false
		});
}

void MisuzuState_NormalDamaged_Stomach::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void MisuzuState_NormalDamaged_Stomach::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(MisuzuStateType::Idle);
}


