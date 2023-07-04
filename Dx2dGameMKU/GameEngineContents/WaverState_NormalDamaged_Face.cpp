#include "PrecompileHeader.h"
#include "WaverState_NormalDamaged_Face.h"

#include "WaverFSM.h"

const std::string_view WaverState_NormalDamaged_Face::AniName = "NormalDamaged_Face";
const std::pair<int, int> WaverState_NormalDamaged_Face::AniCutFrame = std::pair<int, int>{5, 2};
const std::pair<size_t, size_t> WaverState_NormalDamaged_Face::AniFrameIndex = std::pair<size_t, size_t>{ 0,2 };
const float WaverState_NormalDamaged_Face::AniInterTime = 0.08f;

WaverState_NormalDamaged_Face::WaverState_NormalDamaged_Face()
{

}

WaverState_NormalDamaged_Face::~WaverState_NormalDamaged_Face()
{

}

void WaverState_NormalDamaged_Face::Start() 
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void WaverState_NormalDamaged_Face::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(WaverFSM::NormalDamaged_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Waver");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(
		Dir.GetPlusFileName(WaverFSM::NormalDamaged_FileName).GetFullPath(),
		AniCutFrame.first, AniCutFrame.second);
}

void WaverState_NormalDamaged_Face::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = WaverFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}

void WaverState_NormalDamaged_Face::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	SoundMgr::PlaySFX("CheerLeader_FaceDamaged.wav");
}

void WaverState_NormalDamaged_Face::Update(float _DeltaTime) 
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(WaverStateType::Idle);
}


