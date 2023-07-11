#include "PrecompileHeader.h"
#include "MisuzuState_Damaged_BlowBack.h"

#include "RCGEnums.h"

#include "MisuzuFSM.h"
#include "FieldEnemyBase.h"

const std::string_view MisuzuState_Damaged_BlowBack::AniName = "BlowBack";
const std::string_view MisuzuState_Damaged_BlowBack::AniFileName = "Misuzu_BlowBack.png";
const std::pair<int, int> MisuzuState_Damaged_BlowBack::AniCutFrame = std::pair<int, int>(5, 5);
const std::pair<size_t, size_t> MisuzuState_Damaged_BlowBack::AniFrameIndex = std::pair<size_t, size_t>{ 0, 21 };
const float MisuzuState_Damaged_BlowBack::AniInterTime = 0.05f;



MisuzuState_Damaged_BlowBack::MisuzuState_Damaged_BlowBack()
{

}

MisuzuState_Damaged_BlowBack::~MisuzuState_Damaged_BlowBack()
{

}



void MisuzuState_Damaged_BlowBack::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc, Duration);
}

void MisuzuState_Damaged_BlowBack::LoadAnimation()
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

void MisuzuState_Damaged_BlowBack::CreateAnimation()
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


void MisuzuState_Damaged_BlowBack::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();

	SoundMgr::PlaySFX("Misuzu_BlowDamaged.wav");
}


void MisuzuState_Damaged_BlowBack::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	//벽과 충돌시 튕겨져 나오는 BlowBack
	EnemyState_DamagedBase::Update_BlowReflect(_DeltaTime);
	
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(MisuzuStateType::Damaged_Dizzy);
}



void MisuzuState_Damaged_BlowBack::ExitState()
{
	EnemyState_DamagedBase::ExitState();
	EnemyStateBase::OnMainCollider();
}