#include "PrecompileHeader.h"
#include "TigerManState_NormalDamaged_Stomach.h"

#include "TigerManFSM.h"

const std::string_view TigerManState_NormalDamaged_Stomach::AniName = "NormalDamaged_Stomach";
const std::pair<int, int> TigerManState_NormalDamaged_Stomach::AniCutFrame = std::pair<int, int>{ 5, 2 };
const std::pair<size_t, size_t> TigerManState_NormalDamaged_Stomach::AniFrameIndex = std::pair<size_t, size_t>{ 4,6 };
const float TigerManState_NormalDamaged_Stomach::AniInterTime = 0.08f;

TigerManState_NormalDamaged_Stomach::TigerManState_NormalDamaged_Stomach()
{

}

TigerManState_NormalDamaged_Stomach::~TigerManState_NormalDamaged_Stomach()
{

}

void TigerManState_NormalDamaged_Stomach::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void TigerManState_NormalDamaged_Stomach::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(TigerManFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("TigerMan");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(TigerManFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void TigerManState_NormalDamaged_Stomach::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = TigerManFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false
		});
}

void TigerManState_NormalDamaged_Stomach::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void TigerManState_NormalDamaged_Stomach::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(TigerManStateType::Idle);
}


