#include "PrecompileHeader.h"
#include "SchoolGirlState_NormalDamaged_Stomach.h"

#include "SchoolGirlFSM.h"

const std::string_view SchoolGirlState_NormalDamaged_Stomach::AniName = "NormalDamaged_Stomach";
const std::pair<int, int> SchoolGirlState_NormalDamaged_Stomach::AniCutFrame = std::pair<int, int>{ 5, 2 };
const std::pair<size_t, size_t> SchoolGirlState_NormalDamaged_Stomach::AniFrameIndex = std::pair<size_t, size_t>{ 3,5 };
const float SchoolGirlState_NormalDamaged_Stomach::AniInterTime = 0.08f;

SchoolGirlState_NormalDamaged_Stomach::SchoolGirlState_NormalDamaged_Stomach()
{

}

SchoolGirlState_NormalDamaged_Stomach::~SchoolGirlState_NormalDamaged_Stomach()
{

}

void SchoolGirlState_NormalDamaged_Stomach::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void SchoolGirlState_NormalDamaged_Stomach::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(SchoolGirlFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolGirl");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(SchoolGirlFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void SchoolGirlState_NormalDamaged_Stomach::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = SchoolGirlFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false,
		});
}

void SchoolGirlState_NormalDamaged_Stomach::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	SoundMgr::PlaySFX("FemaleEnemy_StomachDamaged.wav");
}

void SchoolGirlState_NormalDamaged_Stomach::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolGirlStateType::Idle);
}


