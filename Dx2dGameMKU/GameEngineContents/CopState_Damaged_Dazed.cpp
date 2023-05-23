#include "PrecompileHeader.h"
#include "CopState_Damaged_Dazed.h"


#include "CopFSM.h"

const std::string_view CopState_Damaged_Dazed::AniName = "Dazed";
const std::string_view CopState_Damaged_Dazed::AniFileName = "Cop_Dazed.png";
const std::pair<int, int> CopState_Damaged_Dazed::AniCutFrame = std::pair<int, int>(5, 1);
const std::pair<size_t, size_t> CopState_Damaged_Dazed::AniFrameIndex = std::pair<size_t, size_t>{ 0, 3 };
const float CopState_Damaged_Dazed::AniInterTime = 0.15f;

CopState_Damaged_Dazed::CopState_Damaged_Dazed()
{

}

CopState_Damaged_Dazed::~CopState_Damaged_Dazed()
{

}



void CopState_Damaged_Dazed::Start()
{
	EnemyState_DamagedBase::Start();
	LoadAnimation();
	CreateAnimation();
}


void CopState_Damaged_Dazed::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cop");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CopState_Damaged_Dazed::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
	});

}


void CopState_Damaged_Dazed::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}



void CopState_Damaged_Dazed::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (GetLiveTime() < Duration)
		return;

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(CopStateType::Idle);
}