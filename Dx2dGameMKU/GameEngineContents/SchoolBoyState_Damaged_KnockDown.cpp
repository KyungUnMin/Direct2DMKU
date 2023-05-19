#include "PrecompileHeader.h"
#include "SchoolBoyState_Damaged_KnockDown.h"

#include "SchoolBoyFSM.h"
#include "FieldEnemyBase.h"

const std::string_view SchoolBoyState_Damaged_KnockDown::AniFileName = "SchoolBoy_KnockDown.png";

const std::string_view SchoolBoyState_Damaged_KnockDown::AniName = "KnockDown";
const std::pair<int, int> SchoolBoyState_Damaged_KnockDown::AniCutFrame = std::pair<int, int>(5, 7);
const std::pair<size_t, size_t> SchoolBoyState_Damaged_KnockDown::AniFrameIndex = std::pair<size_t, size_t>{ 0, 24 };
const float SchoolBoyState_Damaged_KnockDown::AniInterTime = 0.08f;
const float SchoolBoyState_Damaged_KnockDown::LiveDuration = 5.f;

SchoolBoyState_Damaged_KnockDown::SchoolBoyState_Damaged_KnockDown()
{

}

SchoolBoyState_Damaged_KnockDown::~SchoolBoyState_Damaged_KnockDown()
{

}



void SchoolBoyState_Damaged_KnockDown::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc);
	EnemyState_DamagedBase::SetGroundBlow();
}

void SchoolBoyState_Damaged_KnockDown::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolBoy");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void SchoolBoyState_Damaged_KnockDown::CreateAnimation()
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


void SchoolBoyState_Damaged_KnockDown::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void SchoolBoyState_Damaged_KnockDown::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);

	if (GetLiveTime() < LiveDuration)
		return;

	GetEnemy()->Death();
}

