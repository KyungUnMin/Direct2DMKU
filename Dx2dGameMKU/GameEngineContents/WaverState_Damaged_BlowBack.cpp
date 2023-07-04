#include "PrecompileHeader.h"
#include "WaverState_Damaged_BlowBack.h"


#include "WaverFSM.h"
#include "FieldEnemyBase.h"

const std::string_view WaverState_Damaged_BlowBack::AniName = "BlowBack";
const std::string_view WaverState_Damaged_BlowBack::AniFileName = "Waver_BlowBack.png";
const std::pair<int, int> WaverState_Damaged_BlowBack::AniCutFrame = std::pair<int, int>(5, 7);
const std::pair<size_t, size_t> WaverState_Damaged_BlowBack::AniFrameIndex = std::pair<size_t, size_t>{ 0, 30 };
const float WaverState_Damaged_BlowBack::AniInterTime = 0.05f;



WaverState_Damaged_BlowBack::WaverState_Damaged_BlowBack()
{

}

WaverState_Damaged_BlowBack::~WaverState_Damaged_BlowBack()
{

}



void WaverState_Damaged_BlowBack::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc, Duration);
}

void WaverState_Damaged_BlowBack::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Waver");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void WaverState_Damaged_BlowBack::CreateAnimation()
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


void WaverState_Damaged_BlowBack::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	SoundMgr::PlaySFX("CheerLeader_BlowDamaged.wav");
}


void WaverState_Damaged_BlowBack::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	bool IsMoveOk = EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);
	if (false == IsMoveOk)
	{
		GetFSM()->ChangeState(WaverStateType::Damaged_WallHit);
		return;
	}
	
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(WaverStateType::Idle);
}

