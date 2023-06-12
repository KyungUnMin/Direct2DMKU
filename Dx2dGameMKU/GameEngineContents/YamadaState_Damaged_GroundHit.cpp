#include "PrecompileHeader.h"
#include "YamadaState_Damaged_GroundHit.h"

#include "YamadaFSM.h"

const std::string_view YamadaState_Damaged_GroundHit::AniName = "GroundHit";
const std::string_view YamadaState_Damaged_GroundHit::AniFileName = "Yamada_GroundHit.png";
const std::pair<int, int> YamadaState_Damaged_GroundHit::AniCutFrame = std::pair<int, int>(5, 1);
const std::pair<size_t, size_t> YamadaState_Damaged_GroundHit::AniFrameIndex = std::pair<size_t, size_t>{ 0, 3 };
const float YamadaState_Damaged_GroundHit::AniInterTime = 0.08f;
const float YamadaState_Damaged_GroundHit::BlowStartAcc = 500.f;
const float YamadaState_Damaged_GroundHit::BlowDuration = 0.5f;



YamadaState_Damaged_GroundHit::YamadaState_Damaged_GroundHit()
{

}

YamadaState_Damaged_GroundHit::~YamadaState_Damaged_GroundHit()
{

}



void YamadaState_Damaged_GroundHit::Start()
{
	EnemyState_DamagedBase::Start();
	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(BlowStartAcc, BlowDuration);
	EnemyState_DamagedBase::SetGroundBlow();
}


void YamadaState_Damaged_GroundHit::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Yamada");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_Damaged_GroundHit::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

}


void YamadaState_Damaged_GroundHit::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}



void YamadaState_Damaged_GroundHit::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::GetUpAttack);
}