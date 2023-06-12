#include "PrecompileHeader.h"
#include "YamadaState_Damaged_BlowBack.h"

#include "RCGEnums.h"

#include "YamadaFSM.h"
#include "FieldEnemyBase.h"

const std::string_view YamadaState_Damaged_BlowBack::AniName = "BlowBack";
const std::string_view YamadaState_Damaged_BlowBack::AniFileName = "Yamada_BlowBack.png";
const std::pair<int, int> YamadaState_Damaged_BlowBack::AniCutFrame = std::pair<int, int>(5, 8);
const std::pair<size_t, size_t> YamadaState_Damaged_BlowBack::AniFrameIndex = std::pair<size_t, size_t>{ 0, 37 };
const float YamadaState_Damaged_BlowBack::AniInterTime = 0.05f;



YamadaState_Damaged_BlowBack::YamadaState_Damaged_BlowBack()
{

}

YamadaState_Damaged_BlowBack::~YamadaState_Damaged_BlowBack()
{

}



void YamadaState_Damaged_BlowBack::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc, Duration);
}

void YamadaState_Damaged_BlowBack::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Yamada");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_Damaged_BlowBack::CreateAnimation()
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


void YamadaState_Damaged_BlowBack::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();
}


void YamadaState_Damaged_BlowBack::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	//벽과 충돌시 튕겨져 나오는 BlowBack
	EnemyState_DamagedBase::Update_BlowReflect(_DeltaTime);
	
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::Idle);
}



void YamadaState_Damaged_BlowBack::ExitState()
{
	EnemyState_DamagedBase::ExitState();

	IsWallHit = false;
	WallOutDir = float4::Zero;
	EnemyStateBase::OnMainCollider();
}