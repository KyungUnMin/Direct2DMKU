#include "PrecompileHeader.h"
#include "TigerManState_Damaged_KnockDown.h"

#include "TigerManFSM.h"
#include "FieldEnemyBase.h"
#include "FieldMoney.h"

const std::string_view TigerManState_Damaged_KnockDown::AniFileName = "TigerMan_KnockDown.png";

const std::string_view TigerManState_Damaged_KnockDown::AniName = "KnockDown";
const std::pair<int, int> TigerManState_Damaged_KnockDown::AniCutFrame = std::pair<int, int>(5, 5);
const float TigerManState_Damaged_KnockDown::AniInterTime = 0.08f;
const float TigerManState_Damaged_KnockDown::LiveDuration = 5.f;

TigerManState_Damaged_KnockDown::TigerManState_Damaged_KnockDown()
{

}

TigerManState_Damaged_KnockDown::~TigerManState_Damaged_KnockDown()
{

}



void TigerManState_Damaged_KnockDown::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc);
	EnemyState_DamagedBase::SetGroundBlow();
}

void TigerManState_Damaged_KnockDown::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("TigerMan");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void TigerManState_Damaged_KnockDown::CreateAnimation()
{
	std::vector<size_t> AniFrmIndex;
	AniFrmIndex.reserve(19);
	AniFrmIndex.push_back(0);
	for (size_t i = 2; i < 20; ++i)
	{
		AniFrmIndex.push_back(i);
	}

	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false,
		.FrameIndex = AniFrmIndex
	});
}


void TigerManState_Damaged_KnockDown::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();

	SoundMgr::PlaySFX("TigerMan_KnockDown.wav");
	EnemyState_DamagedBase::CreateMoney(MoneyType::Bill_Pupple);
}


void TigerManState_Damaged_KnockDown::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);

	if (GetLiveTime() < LiveDuration)
		return;

	GetEnemy()->Death();
}

