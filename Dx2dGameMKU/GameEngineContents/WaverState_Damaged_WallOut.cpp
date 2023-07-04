#include "PrecompileHeader.h"
#include "WaverState_Damaged_WallOut.h"

#include "WaverFSM.h"
#include "FieldEnemyBase.h"

const std::string_view WaverState_Damaged_WallOut::AniName = "WallOut";
const std::string_view WaverState_Damaged_WallOut::AniFileName = "Waver_WallOut.png";
const std::pair<int, int> WaverState_Damaged_WallOut::AniCutFrame = std::pair<int, int>(5, 1);
const float WaverState_Damaged_WallOut::AniInterTime = 0.1f;

WaverState_Damaged_WallOut::WaverState_Damaged_WallOut()
{

}

WaverState_Damaged_WallOut::~WaverState_Damaged_WallOut()
{

}



void WaverState_Damaged_WallOut::Start()
{
	EnemyState_DamagedBase::Start();
	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetGroundBlow();
	EnemyState_DamagedBase::SetBlowValue(StartReflectSize, Duration);
}


void WaverState_Damaged_WallOut::LoadAnimation()
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

void WaverState_Damaged_WallOut::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 2,
		.Loop = false,
		.FrameTime = std::vector<float>{0.2f, 0.05f, 0.05f},
	});
}


void WaverState_Damaged_WallOut::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	SetReflectDirection();

	SoundMgr::PlaySFX("CheerLeader_WallOut.wav");
}

void WaverState_Damaged_WallOut::SetReflectDirection()
{
	//Enemy의 방향 == 튕겨져나올 방향
	bool ReflectDir = EnemyStateBase::IsRightDir();
	EnemyState_DamagedBase::Set_BlowDir(ReflectDir);
}


void WaverState_Damaged_WallOut::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	//벽으로부터 튕겨져 나오기
	EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);

	if (GetLiveTime() < Duration)
		return;

	GetFSM()->ChangeState(WaverStateType::Damaged_Dazed);
}