#include "PrecompileHeader.h"
#include "TigerManState_NormalDamaged_Face.h"

#include "TigerManFSM.h"

const std::string_view TigerManState_NormalDamaged_Face::AniName = "NormalDamaged_Face";
const std::pair<int, int> TigerManState_NormalDamaged_Face::AniCutFrame = std::pair<int, int>{5, 2};
const float TigerManState_NormalDamaged_Face::AniInterTime = 0.08f;

TigerManState_NormalDamaged_Face::TigerManState_NormalDamaged_Face()
{

}

TigerManState_NormalDamaged_Face::~TigerManState_NormalDamaged_Face()
{

}

void TigerManState_NormalDamaged_Face::Start() 
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void TigerManState_NormalDamaged_Face::LoadAnimation()
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

void TigerManState_NormalDamaged_Face::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = TigerManFSM::NormalDamaged_FileName,
		.FrameInter = AniInterTime,
		.Loop = false,
		.FrameIndex = std::vector<size_t>{0, 2, 3}
	});
}

void TigerManState_NormalDamaged_Face::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void TigerManState_NormalDamaged_Face::Update(float _DeltaTime) 
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(TigerManStateType::Idle);
}


