#include "PrecompileHeader.h"
#include "HooliganState_NormalDamaged_Stomach.h"

#include "HooliganFSM.h"

const std::string_view HooliganState_NormalDamaged_Stomach::AniName = "NormalDamaged_Stomach";
const std::pair<int, int> HooliganState_NormalDamaged_Stomach::AniCutFrame = std::pair<int, int>{ 5, 2 };
const std::pair<size_t, size_t> HooliganState_NormalDamaged_Stomach::AniFrameIndex = std::pair<size_t, size_t>{ 3,5 };
const float HooliganState_NormalDamaged_Stomach::AniInterTime = 0.08f;

HooliganState_NormalDamaged_Stomach::HooliganState_NormalDamaged_Stomach()
{

}

HooliganState_NormalDamaged_Stomach::~HooliganState_NormalDamaged_Stomach()
{

}

void HooliganState_NormalDamaged_Stomach::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void HooliganState_NormalDamaged_Stomach::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(HooliganFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Hooligan");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(HooliganFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void HooliganState_NormalDamaged_Stomach::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = HooliganFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false
		});
}

void HooliganState_NormalDamaged_Stomach::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void HooliganState_NormalDamaged_Stomach::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(HooliganStateType::Idle);
}


