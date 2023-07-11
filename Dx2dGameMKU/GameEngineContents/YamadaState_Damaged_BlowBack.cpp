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
	ShadowRender = GetEnemy()->GetShadowRender();
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
	AniFrmInter[GarbageFrmIdx - 1] = 0.2f;

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Loop = false,
		.FrameIndex = AniFrmIdx,
		.FrameTime = AniFrmInter
	});

	//그림자 지우기 시작하는 프레임
	Render->SetAnimationStartEvent(AniName, GarbageFrmIdx + 1, [this]()
	{
		this->ShadowTime = GetLiveTime();

		GameEngineSoundPlayer GetUpSfx = SoundMgr::PlaySFX("Yamada_TeleportDistappear_Effect.wav");
		GetUpSfx.SetVolume(0.5f);
		GetUpSfx.SetPitch(1.5f);
	});
}





void YamadaState_Damaged_BlowBack::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();

	SoundMgr::PlaySFX("Yamada_BlowDamaged.wav");
}


void YamadaState_Damaged_BlowBack::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	//벽과 충돌시 튕겨져 나오는 BlowBack
	EnemyState_DamagedBase::Update_BlowReflect(_DeltaTime);
	Update_ShadowScale();

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::TeleportAppear);
}

void YamadaState_Damaged_BlowBack::Update_ShadowScale()
{
	if (ShadowTime < 0.f)
		return;

	float Time = GetLiveTime() - ShadowTime;
	float Ratio = (Time / ShadowDuration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	ShadowRender->ColorOptionValue.MulColor = float4::One * (1.f - Ratio);
}

void YamadaState_Damaged_BlowBack::ExitState()
{
	EnemyState_DamagedBase::ExitState();
	EnemyStateBase::OnMainCollider();
	ShadowRender->ColorOptionValue.MulColor = float4::One;
}