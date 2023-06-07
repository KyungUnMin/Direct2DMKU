#include "PrecompileHeader.h"
#include "MisuzuState_Damaged_BlowBack.h"

#include "RCGEnums.h"

#include "MisuzuFSM.h"
#include "FieldEnemyBase.h"
#include "FieldLevelBase.h"
#include "HitEffect.h"

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
}


void MisuzuState_Damaged_BlowBack::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (false == IsWallHit)
	{
		Update_Blow(_DeltaTime);
	}
	else
	{
		Update_WallHit(_DeltaTime);
	}

	
	
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(MisuzuStateType::Damaged_Dizzy);
}


void MisuzuState_Damaged_BlowBack::Update_Blow(float _DeltaTime)
{
	if (true == EnemyState_DamagedBase::Update_BlowBack(_DeltaTime))
		return;

	IsWallHit = true;

	//Enemy가 바라보고 있던 방향
	WallOutDir = IsRightDir() ? float4::Right : float4::Left;

	CreateWallEffect();
}

void MisuzuState_Damaged_BlowBack::CreateWallEffect()
{
	static const float4 Offset = float4::Up * 100.f;
	static const float4 Scale = float4{ 0.5f, 1.f };

	std::shared_ptr<HitEffect> Effect = nullptr;
	Effect = FieldLevelBase::GetPtr()->CreateActor<HitEffect>(UpdateOrder::Effect);
	Effect->OffHitSpark();

	float4 EnemyPos = GetEnemy()->GetTransform()->GetWorldPosition();
	GameEngineTransform* EffectTrans = Effect->GetTransform();
	EffectTrans->SetLocalPosition(EnemyPos + Offset);
	EffectTrans->SetLocalScale(Scale);
}

void MisuzuState_Damaged_BlowBack::Update_WallHit(float _DeltaTime) 
{
	float Ratio = (GetLiveTime() / Duration);

	//벽에 부딪힌 후 튕겨져 나오기
	EnemyStateBase::Update_AccMove(_DeltaTime, Ratio, WallOutDir, StartAcc);

	EnemyState_DamagedBase::Update_BlowVertical(Ratio);
}

void MisuzuState_Damaged_BlowBack::ExitState()
{
	EnemyState_DamagedBase::ExitState();

	IsWallHit = false;
	WallOutDir = float4::Zero;
}