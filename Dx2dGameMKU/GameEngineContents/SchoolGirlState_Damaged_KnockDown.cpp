#include "PrecompileHeader.h"
#include "SchoolGirlState_Damaged_KnockDown.h"

#include "DataMgr.h"

#include "SchoolGirlFSM.h"
#include "FieldEnemyBase.h"
#include "FieldMoney.h"
#include "TutorialUI.h"

const std::string_view SchoolGirlState_Damaged_KnockDown::AniFileName = "SchoolGirl_KnockDown.png";

const std::string_view SchoolGirlState_Damaged_KnockDown::AniName = "KnockDown";
const std::pair<int, int> SchoolGirlState_Damaged_KnockDown::AniCutFrame = std::pair<int, int>(5, 7);
const std::pair<size_t, size_t> SchoolGirlState_Damaged_KnockDown::AniFrameIndex = std::pair<size_t, size_t>{ 0, 24 };
const float SchoolGirlState_Damaged_KnockDown::AniInterTime = 0.08f;
const float SchoolGirlState_Damaged_KnockDown::LiveDuration = 5.f;

SchoolGirlState_Damaged_KnockDown::SchoolGirlState_Damaged_KnockDown()
{

}

SchoolGirlState_Damaged_KnockDown::~SchoolGirlState_Damaged_KnockDown()
{

}



void SchoolGirlState_Damaged_KnockDown::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc);
	EnemyState_DamagedBase::SetGroundBlow();
}

void SchoolGirlState_Damaged_KnockDown::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolGirl");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void SchoolGirlState_Damaged_KnockDown::CreateAnimation()
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


void SchoolGirlState_Damaged_KnockDown::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();

	SoundMgr::PlaySFX("FemaleEnemy_KnockDown.wav");
	EnemyState_DamagedBase::CreateMoney(MoneyType::Coin);
	DataMgr::AddPlayerExp(20);

	TutorialUI::BindOnceTutorial("탈출하자!", "모든 적을 물리치면 밖으로 나갈 수 있다");
}


void SchoolGirlState_Damaged_KnockDown::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);

	if (GetLiveTime() < LiveDuration)
		return;

	GetEnemy()->Death();
}

