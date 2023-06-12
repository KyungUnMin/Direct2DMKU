#include "PrecompileHeader.h"
#include "YamadaState_NormalDamaged_Jaw.h"

#include "YamadaFSM.h"

const std::string_view YamadaState_NormalDamaged_Jaw::AniName = "NormalDamaged_Jaw";
const std::pair<int, int> YamadaState_NormalDamaged_Jaw::AniCutFrame = std::pair<int, int>{ 5, 2 };
const std::pair<size_t, size_t> YamadaState_NormalDamaged_Jaw::AniFrameIndex = std::pair<size_t, size_t>{ 6,8 };
const float YamadaState_NormalDamaged_Jaw::AniInterTime = 0.08f;

YamadaState_NormalDamaged_Jaw::YamadaState_NormalDamaged_Jaw()
{

}

YamadaState_NormalDamaged_Jaw::~YamadaState_NormalDamaged_Jaw()
{

}

void YamadaState_NormalDamaged_Jaw::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void YamadaState_NormalDamaged_Jaw::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(YamadaFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Yamada");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(YamadaFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_NormalDamaged_Jaw::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = YamadaFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}

void YamadaState_NormalDamaged_Jaw::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void YamadaState_NormalDamaged_Jaw::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::Idle);
}


