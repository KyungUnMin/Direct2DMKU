#include "PrecompileHeader.h"
#include "CheerleaderState_NormalDamaged_Face.h"

#include "CheerleaderFSM.h"

const std::string_view CheerleaderState_NormalDamaged_Face::AniName = "NormalDamaged_Face";
const std::pair<int, int> CheerleaderState_NormalDamaged_Face::AniCutFrame = std::pair<int, int>{5, 2};
const std::pair<size_t, size_t> CheerleaderState_NormalDamaged_Face::AniFrameIndex = std::pair<size_t, size_t>{ 0,2 };
const float CheerleaderState_NormalDamaged_Face::AniInterTime = 0.08f;

CheerleaderState_NormalDamaged_Face::CheerleaderState_NormalDamaged_Face()
{

}

CheerleaderState_NormalDamaged_Face::~CheerleaderState_NormalDamaged_Face()
{

}

void CheerleaderState_NormalDamaged_Face::Start() 
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void CheerleaderState_NormalDamaged_Face::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(CheerleaderFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cheerleader");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(CheerleaderFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void CheerleaderState_NormalDamaged_Face::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = CheerleaderFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime
	});
}

void CheerleaderState_NormalDamaged_Face::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void CheerleaderState_NormalDamaged_Face::Update(float _DeltaTime) 
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(CheerleaderStateType::Idle);
}


