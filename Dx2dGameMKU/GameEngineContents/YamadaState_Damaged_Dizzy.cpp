#include "PrecompileHeader.h"
#include "YamadaState_Damaged_Dizzy.h"

#include "YamadaFSM.h"

const std::string_view YamadaState_Damaged_Dizzy::AniName = "Dizzy";
const std::string_view YamadaState_Damaged_Dizzy::AniFileName = "Yamada_Dizzy.png";
const std::pair<int, int> YamadaState_Damaged_Dizzy::AniCutFrame = std::pair<int, int>(5, 1);
const std::pair<size_t, size_t> YamadaState_Damaged_Dizzy::AniFrameIndex = std::pair<size_t, size_t>{ 0, 3 };
const float YamadaState_Damaged_Dizzy::AniInterTime = 0.2f;

YamadaState_Damaged_Dizzy::YamadaState_Damaged_Dizzy()
{

}

YamadaState_Damaged_Dizzy::~YamadaState_Damaged_Dizzy()
{

}



void YamadaState_Damaged_Dizzy::Start()
{
	EnemyState_DamagedBase::Start();
	LoadAnimation();
	CreateAnimation();
	EnemyStateBase::DontLookPlayer();
}


void YamadaState_Damaged_Dizzy::LoadAnimation()
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

void YamadaState_Damaged_Dizzy::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = true,
	});

}


void YamadaState_Damaged_Dizzy::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}



void YamadaState_Damaged_Dizzy::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (GetLiveTime() < Duration)
		return;

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::GetUpAttack);
}