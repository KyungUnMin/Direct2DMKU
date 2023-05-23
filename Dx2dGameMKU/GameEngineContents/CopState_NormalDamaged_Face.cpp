#include "PrecompileHeader.h"
#include "CopState_NormalDamaged_Face.h"

#include "CopFSM.h"

const std::string_view CopState_NormalDamaged_Face::AniName = "NormalDamaged_Face";
const std::pair<int, int> CopState_NormalDamaged_Face::AniCutFrame = std::pair<int, int>{5, 2};
const std::pair<size_t, size_t> CopState_NormalDamaged_Face::AniFrameIndex = std::pair<size_t, size_t>{ 0,2 };
const float CopState_NormalDamaged_Face::AniInterTime = 0.08f;

CopState_NormalDamaged_Face::CopState_NormalDamaged_Face()
{

}

CopState_NormalDamaged_Face::~CopState_NormalDamaged_Face()
{

}

void CopState_NormalDamaged_Face::Start() 
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void CopState_NormalDamaged_Face::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(CopFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cop");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(CopFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void CopState_NormalDamaged_Face::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = CopFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime
	});
}

void CopState_NormalDamaged_Face::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void CopState_NormalDamaged_Face::Update(float _DeltaTime) 
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(CopStateType::Idle);
}


