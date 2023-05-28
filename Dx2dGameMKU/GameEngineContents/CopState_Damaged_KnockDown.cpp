#include "PrecompileHeader.h"
#include "CopState_Damaged_KnockDown.h"

#include "CopFSM.h"
#include "FieldEnemyBase.h"

const std::string_view CopState_Damaged_KnockDown::AniFileName = "Cop_KnockDown.png";

const std::string_view CopState_Damaged_KnockDown::AniName = "KnockDown";
const std::pair<int, int> CopState_Damaged_KnockDown::AniCutFrame = std::pair<int, int>(5, 5);
const std::pair<size_t, size_t> CopState_Damaged_KnockDown::AniFrameIndex = std::pair<size_t, size_t>{ 0, 23 };
const float CopState_Damaged_KnockDown::AniInterTime = 0.08f;
const float CopState_Damaged_KnockDown::LiveDuration = 5.f;

CopState_Damaged_KnockDown::CopState_Damaged_KnockDown()
{

}

CopState_Damaged_KnockDown::~CopState_Damaged_KnockDown()
{

}



void CopState_Damaged_KnockDown::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc);
	EnemyState_DamagedBase::SetGroundBlow();
}

void CopState_Damaged_KnockDown::LoadAnimation()
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

void CopState_Damaged_KnockDown::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}


void CopState_Damaged_KnockDown::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void CopState_Damaged_KnockDown::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);

	if (GetLiveTime() < LiveDuration)
		return;

	GetEnemy()->Death();
}

