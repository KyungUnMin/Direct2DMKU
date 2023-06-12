#include "PrecompileHeader.h"
#include "YamadaState_Damaged_BlowBack.h"

#include "RCGEnums.h"

#include "YamadaFSM.h"
#include "FieldEnemyBase.h"

const std::string_view YamadaState_Damaged_BlowBack::AniName = "BlowBack";
const std::string_view YamadaState_Damaged_BlowBack::AniFileName = "Yamada_BlowBack.png";
const std::pair<int, int> YamadaState_Damaged_BlowBack::AniCutFrame = std::pair<int, int>(5, 8);
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
	const size_t GarbageFrmIdx = 24;
	const size_t TatalFrmIdx = 37;

	std::vector<size_t> AniFrmIdx;
	AniFrmIdx.reserve(TatalFrmIdx);
	for (size_t i = 0; i < GarbageFrmIdx; ++i)
	{
		AniFrmIdx.push_back(i);
	}

	for (size_t i = (GarbageFrmIdx + 1); i <= TatalFrmIdx; ++i)
	{
		AniFrmIdx.push_back(i);
	}

	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false,
		.FrameIndex = AniFrmIdx
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