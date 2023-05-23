#include "PrecompileHeader.h"
#include "SchoolGirlState_Damaged_BlowBack.h"


#include "SchoolGirlFSM.h"
#include "FieldEnemyBase.h"

const std::string_view SchoolGirlState_Damaged_BlowBack::AniName = "BlowBack";
const std::string_view SchoolGirlState_Damaged_BlowBack::AniFileName = "SchoolGirl_BlowBack.png";
const std::pair<int, int> SchoolGirlState_Damaged_BlowBack::AniCutFrame = std::pair<int, int>(5, 7);
const std::pair<size_t, size_t> SchoolGirlState_Damaged_BlowBack::AniFrameIndex = std::pair<size_t, size_t>{ 0, 32 };
const float SchoolGirlState_Damaged_BlowBack::AniInterTime = 0.05f;



SchoolGirlState_Damaged_BlowBack::SchoolGirlState_Damaged_BlowBack()
{

}

SchoolGirlState_Damaged_BlowBack::~SchoolGirlState_Damaged_BlowBack()
{

}



void SchoolGirlState_Damaged_BlowBack::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc, Duration);
}

void SchoolGirlState_Damaged_BlowBack::LoadAnimation()
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

void SchoolGirlState_Damaged_BlowBack::CreateAnimation()
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


void SchoolGirlState_Damaged_BlowBack::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void SchoolGirlState_Damaged_BlowBack::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	bool IsMoveOk = EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);
	if (false == IsMoveOk)
	{
		GetFSM()->ChangeState(SchoolGirlStateType::Damaged_WallHit);
		return;
	}
	
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolGirlStateType::Idle);
}

