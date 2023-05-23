#include "PrecompileHeader.h"
#include "TigerManState_NormalDamaged_Jaw.h"

#include "TigerManFSM.h"

const std::string_view TigerManState_NormalDamaged_Jaw::AniName = "NormalDamaged_Jaw";
const std::pair<int, int> TigerManState_NormalDamaged_Jaw::AniCutFrame = std::pair<int, int>{ 5, 2 };
const std::pair<size_t, size_t> TigerManState_NormalDamaged_Jaw::AniFrameIndex = std::pair<size_t, size_t>{ 6,8 };
const float TigerManState_NormalDamaged_Jaw::AniInterTime = 0.08f;

TigerManState_NormalDamaged_Jaw::TigerManState_NormalDamaged_Jaw()
{

}

TigerManState_NormalDamaged_Jaw::~TigerManState_NormalDamaged_Jaw()
{

}

void TigerManState_NormalDamaged_Jaw::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void TigerManState_NormalDamaged_Jaw::LoadAnimation()
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

void TigerManState_NormalDamaged_Jaw::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = TigerManFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime
	});
}

void TigerManState_NormalDamaged_Jaw::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void TigerManState_NormalDamaged_Jaw::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(TigerManStateType::Idle);
}


