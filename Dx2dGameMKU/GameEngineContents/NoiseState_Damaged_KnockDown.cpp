#include "PrecompileHeader.h"
#include "NoiseState_Damaged_KnockDown.h"

#include "NoiseFSM.h"
#include "FieldEnemyBase.h"

const std::string_view NoiseState_Damaged_KnockDown::AniFileName = "Noise_KnockDown.png";

const std::string_view NoiseState_Damaged_KnockDown::AniName = "KnockDown";
const std::pair<int, int> NoiseState_Damaged_KnockDown::AniCutFrame = std::pair<int, int>(5, 5);
const std::pair<size_t, size_t> NoiseState_Damaged_KnockDown::AniFrameIndex = std::pair<size_t, size_t>{ 0, 20 };
const float NoiseState_Damaged_KnockDown::AniInterTime = 0.08f;

NoiseState_Damaged_KnockDown::NoiseState_Damaged_KnockDown()
{

}

NoiseState_Damaged_KnockDown::~NoiseState_Damaged_KnockDown()
{

}



void NoiseState_Damaged_KnockDown::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc);
	EnemyState_DamagedBase::SetGroundBlow();
}

void NoiseState_Damaged_KnockDown::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Noise");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void NoiseState_Damaged_KnockDown::CreateAnimation()
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


void NoiseState_Damaged_KnockDown::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();
}


void NoiseState_Damaged_KnockDown::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	//EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);
	EnemyState_DamagedBase::Update_BlowReflect(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Defeat);
}

