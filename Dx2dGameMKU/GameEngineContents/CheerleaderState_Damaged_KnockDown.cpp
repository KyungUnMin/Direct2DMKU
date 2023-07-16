#include "PrecompileHeader.h"
#include "CheerleaderState_Damaged_KnockDown.h"

#include "DataMgr.h"

#include "CheerleaderFSM.h"
#include "FieldEnemyBase.h"
#include "FieldMoney.h"

const std::string_view CheerleaderState_Damaged_KnockDown::AniFileName = "Cheerleader_KnockDown.png";

const std::string_view CheerleaderState_Damaged_KnockDown::AniName = "KnockDown";
const std::pair<int, int> CheerleaderState_Damaged_KnockDown::AniCutFrame = std::pair<int, int>(5, 7);
const std::pair<size_t, size_t> CheerleaderState_Damaged_KnockDown::AniFrameIndex = std::pair<size_t, size_t>{ 0, 24 };
const float CheerleaderState_Damaged_KnockDown::AniInterTime = 0.08f;
const float CheerleaderState_Damaged_KnockDown::LiveDuration = 5.f;

CheerleaderState_Damaged_KnockDown::CheerleaderState_Damaged_KnockDown()
{

}

CheerleaderState_Damaged_KnockDown::~CheerleaderState_Damaged_KnockDown()
{

}



void CheerleaderState_Damaged_KnockDown::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc);
	EnemyState_DamagedBase::SetGroundBlow();
}

void CheerleaderState_Damaged_KnockDown::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cheerleader");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CheerleaderState_Damaged_KnockDown::CreateAnimation()
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


void CheerleaderState_Damaged_KnockDown::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();

	SoundMgr::PlaySFX("CheerLeader_KnockDown.wav");
	EnemyState_DamagedBase::CreateMoney(MoneyType::Bill_Blue);
	DataMgr::AddPlayerExp(20);
}


void CheerleaderState_Damaged_KnockDown::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);

	if (GetLiveTime() < LiveDuration)
		return;

	GetEnemy()->Death();
}

