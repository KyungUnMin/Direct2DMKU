#include "PrecompileHeader.h"
#include "MisuzuState_Damaged_KnockDown.h"

#include "MisuzuFSM.h"
#include "FieldEnemyBase.h"

const std::string_view MisuzuState_Damaged_KnockDown::AniFileName = "Misuzu_KnockDown.png";

const std::string_view MisuzuState_Damaged_KnockDown::AniName = "KnockDown";
const std::pair<int, int> MisuzuState_Damaged_KnockDown::AniCutFrame = std::pair<int, int>(5, 7);
const std::pair<size_t, size_t> MisuzuState_Damaged_KnockDown::AniFrameIndex = std::pair<size_t, size_t>{ 0, 30 };
const float MisuzuState_Damaged_KnockDown::AniInterTime = 0.08f;

MisuzuState_Damaged_KnockDown::MisuzuState_Damaged_KnockDown()
{

}

MisuzuState_Damaged_KnockDown::~MisuzuState_Damaged_KnockDown()
{

}



void MisuzuState_Damaged_KnockDown::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc);
	EnemyState_DamagedBase::SetGroundBlow();
}

void MisuzuState_Damaged_KnockDown::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Misuzu");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void MisuzuState_Damaged_KnockDown::CreateAnimation()
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


void MisuzuState_Damaged_KnockDown::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();

	SoundMgr::BgmPauseOn();
	SoundMgr::PlaySFX("Misuzu_KnockDown.wav").SetPitch(0.5f);
	SoundMgr::PlaySFX("Boss_KnockDown.wav");
}


void MisuzuState_Damaged_KnockDown::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	//EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);
	EnemyState_DamagedBase::Update_BlowReflect(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(MisuzuStateType::Defeat);
}

