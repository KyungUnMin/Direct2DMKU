#include "PrecompileHeader.h"
#include "SchoolGirlState_NormalDamaged_Face.h"

#include "SchoolGirlFSM.h"

const std::string_view SchoolGirlState_NormalDamaged_Face::AniName = "NormalDamaged_Face";
const std::pair<int, int> SchoolGirlState_NormalDamaged_Face::AniCutFrame = std::pair<int, int>{5, 2};
const std::pair<size_t, size_t> SchoolGirlState_NormalDamaged_Face::AniFrameIndex = std::pair<size_t, size_t>{ 0,2 };
const float SchoolGirlState_NormalDamaged_Face::AniInterTime = 0.08f;

SchoolGirlState_NormalDamaged_Face::SchoolGirlState_NormalDamaged_Face()
{

}

SchoolGirlState_NormalDamaged_Face::~SchoolGirlState_NormalDamaged_Face()
{

}

void SchoolGirlState_NormalDamaged_Face::Start() 
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void SchoolGirlState_NormalDamaged_Face::LoadAnimation()
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

void SchoolGirlState_NormalDamaged_Face::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = SchoolGirlFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime
	});
}

void SchoolGirlState_NormalDamaged_Face::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void SchoolGirlState_NormalDamaged_Face::Update(float _DeltaTime) 
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolGirlStateType::Idle);
}


