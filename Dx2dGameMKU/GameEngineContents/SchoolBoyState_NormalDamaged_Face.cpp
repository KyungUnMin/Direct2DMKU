#include "PrecompileHeader.h"
#include "SchoolBoyState_NormalDamaged_Face.h"


#include "SchoolBoyFSM.h"

const std::string_view SchoolBoyState_NormalDamaged_Face::AniName = "NormalDamaged_Face";
const std::pair<int, int> SchoolBoyState_NormalDamaged_Face::AniCutFrame = std::pair<int, int>{5, 2};
const std::pair<size_t, size_t> SchoolBoyState_NormalDamaged_Face::AniFrameIndex = std::pair<size_t, size_t>{ 0,2 };
const float SchoolBoyState_NormalDamaged_Face::AniInterTime = 0.08f;

SchoolBoyState_NormalDamaged_Face::SchoolBoyState_NormalDamaged_Face()
{

}

SchoolBoyState_NormalDamaged_Face::~SchoolBoyState_NormalDamaged_Face()
{

}

void SchoolBoyState_NormalDamaged_Face::Start() 
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void SchoolBoyState_NormalDamaged_Face::LoadAnimation()
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

void SchoolBoyState_NormalDamaged_Face::CreateAnimation()
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

void SchoolBoyState_NormalDamaged_Face::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	SoundMgr::PlaySFX("MaleEnemy_FaceDamaged.wav");
}

void SchoolBoyState_NormalDamaged_Face::Update(float _DeltaTime) 
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolBoyStateType::Idle);
}


