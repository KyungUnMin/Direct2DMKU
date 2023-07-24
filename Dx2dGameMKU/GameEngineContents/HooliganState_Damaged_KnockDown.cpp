#include "PrecompileHeader.h"
#include "HooliganState_Damaged_KnockDown.h"

#include "DataMgr.h"

#include "HooliganFSM.h"
#include "FieldEnemyBase.h"
#include "FieldMoney.h"

const std::string_view HooliganState_Damaged_KnockDown::AniFileName = "Hooligan_KnockDown.png";

const std::string_view HooliganState_Damaged_KnockDown::AniName = "KnockDown";
const std::pair<int, int> HooliganState_Damaged_KnockDown::AniCutFrame = std::pair<int, int>(5, 7);
const std::pair<size_t, size_t> HooliganState_Damaged_KnockDown::AniFrameIndex = std::pair<size_t, size_t>{ 4, 28 };
const float HooliganState_Damaged_KnockDown::AniInterTime = 0.08f;
const float HooliganState_Damaged_KnockDown::LiveDuration = 5.f;

HooliganState_Damaged_KnockDown::HooliganState_Damaged_KnockDown()
{

}

HooliganState_Damaged_KnockDown::~HooliganState_Damaged_KnockDown()
{

}



void HooliganState_Damaged_KnockDown::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc);
	EnemyState_DamagedBase::SetGroundBlow();
}

void HooliganState_Damaged_KnockDown::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Hooligan");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void HooliganState_Damaged_KnockDown::CreateAnimation()
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


void HooliganState_Damaged_KnockDown::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();

	SoundMgr::PlaySFX("MaleEnemy_KnockDown.wav");
	EnemyState_DamagedBase::CreateMoney(MoneyType::Bill_Green);
	DataMgr::AddPlayerExp(15);
}


void HooliganState_Damaged_KnockDown::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);

	if (GetLiveTime() < LiveDuration)
		return;

	GetEnemy()->Death();
}

