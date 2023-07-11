#include "PrecompileHeader.h"
#include "YamadaState_NormalDamaged_Face.h"


#include "YamadaFSM.h"

const std::string_view YamadaState_NormalDamaged_Face::AniName = "NormalDamaged_Face";
const std::pair<int, int> YamadaState_NormalDamaged_Face::AniCutFrame = std::pair<int, int>{5, 2};
const std::pair<size_t, size_t> YamadaState_NormalDamaged_Face::AniFrameIndex = std::pair<size_t, size_t>{ 0,2 };
const float YamadaState_NormalDamaged_Face::AniInterTime = 0.08f;

YamadaState_NormalDamaged_Face::YamadaState_NormalDamaged_Face()
{

}

YamadaState_NormalDamaged_Face::~YamadaState_NormalDamaged_Face()
{

}

void YamadaState_NormalDamaged_Face::Start() 
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void YamadaState_NormalDamaged_Face::LoadAnimation()
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

void YamadaState_NormalDamaged_Face::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = YamadaFSM::NormalDamaged_FileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}

void YamadaState_NormalDamaged_Face::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	SoundMgr::PlaySFX("Yamada_FaceDamaged.wav");
}

void YamadaState_NormalDamaged_Face::Update(float _DeltaTime) 
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::Idle);
}


