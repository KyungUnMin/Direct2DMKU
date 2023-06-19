#include "PrecompileHeader.h"
#include "NoiseState_Damaged_BlowBack.h"

#include "RCGEnums.h"

#include "NoiseFSM.h"
#include "FieldEnemyBase.h"

const std::string_view NoiseState_Damaged_BlowBack::AniName = "BlowBack";
const std::string_view NoiseState_Damaged_BlowBack::AniFileName = "Noise_BlowBack.png";
const std::pair<int, int> NoiseState_Damaged_BlowBack::AniCutFrame = std::pair<int, int>(5, 2);
const std::pair<size_t, size_t> NoiseState_Damaged_BlowBack::AniFrameIndex = std::pair<size_t, size_t>{ 0, 6 };
const float NoiseState_Damaged_BlowBack::AniInterTime = 0.08f;



NoiseState_Damaged_BlowBack::NoiseState_Damaged_BlowBack()
{

}

NoiseState_Damaged_BlowBack::~NoiseState_Damaged_BlowBack()
{

}



void NoiseState_Damaged_BlowBack::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetGroundBlow();
	EnemyState_DamagedBase::SetBlowValue(StartAcc, Duration);
}

void NoiseState_Damaged_BlowBack::LoadAnimation()
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

void NoiseState_Damaged_BlowBack::CreateAnimation()
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


void NoiseState_Damaged_BlowBack::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();
}


void NoiseState_Damaged_BlowBack::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	//벽에 팅겨져 나오지는 않는 BlowBack
	EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);

	//벽과 충돌시 튕겨져 나오는 BlowBack
	//EnemyState_DamagedBase::Update_BlowReflect(_DeltaTime);
	
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}



void NoiseState_Damaged_BlowBack::ExitState()
{
	EnemyState_DamagedBase::ExitState();
	EnemyStateBase::OnMainCollider();
}