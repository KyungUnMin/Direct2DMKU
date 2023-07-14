#include "PrecompileHeader.h"
#include "YamadaState_Damaged_KnockDown.h"

#include "YamadaFSM.h"
#include "FieldEnemyBase.h"

const std::string_view YamadaState_Damaged_KnockDown::AniFileName = "Yamada_KnockDown.png";

const std::string_view YamadaState_Damaged_KnockDown::AniName = "KnockDown";
const std::pair<int, int> YamadaState_Damaged_KnockDown::AniCutFrame = std::pair<int, int>(5, 8);
const std::pair<size_t, size_t> YamadaState_Damaged_KnockDown::AniFrameIndex = std::pair<size_t, size_t>{ 0, 37 };
const float YamadaState_Damaged_KnockDown::AniInterTime = 0.08f;

YamadaState_Damaged_KnockDown::YamadaState_Damaged_KnockDown()
{

}

YamadaState_Damaged_KnockDown::~YamadaState_Damaged_KnockDown()
{

}



void YamadaState_Damaged_KnockDown::Start()
{
	EnemyState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetBlowValue(StartAcc);
	EnemyState_DamagedBase::SetGroundBlow();
}

void YamadaState_Damaged_KnockDown::LoadAnimation()
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

void YamadaState_Damaged_KnockDown::CreateAnimation()
{
	const size_t GarbageFrmIdx = 24;
	const size_t TatalFrmIdx = 37;

	//리소스의 X프레임 제거 작업
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

	//누워있는 대기시간 조정
	std::vector<float> AniFrmInter(AniFrmIdx.size());
	for (size_t i = 0; i < AniFrmInter.size(); ++i)
	{
		AniFrmInter[i] = AniInterTime;
	}
	AniFrmInter[GarbageFrmIdx - 1] = 1.f;

	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Loop = false,
		.FrameIndex = AniFrmIdx,
		.FrameTime = AniFrmInter
	});
}


void YamadaState_Damaged_KnockDown::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();

	SoundMgr::BgmPauseOn();
	SoundMgr::PlaySFX("Yamada_KnockDown.wav").SetPitch(0.5f);
	SoundMgr::PlaySFX("Boss_KnockDown.wav");
}


void YamadaState_Damaged_KnockDown::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	//EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);
	EnemyState_DamagedBase::Update_BlowReflect(_DeltaTime);
	EnemyState_DamagedBase::Update_Money(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::Defeat);
}

