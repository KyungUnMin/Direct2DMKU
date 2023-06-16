#include "PrecompileHeader.h"
#include "YamadaState_Attack_Wormchi.h"


#include "YamadaFSM.h"
#include "AfterImageEffect.h"
#include "FieldEnemyBase.h"
#include "FieldLevelBase.h"
#include "YamadaWormchiObj.h"

const std::string_view YamadaState_Attack_Wormchi::AniFileName = "Yamada_Wormchi.png";
const std::vector<std::string_view> YamadaState_Attack_Wormchi::AniNames =
{
	"Worrmchi_SitDown",
	"Worrmchi_Sit",
	"Worrmchi_GetUp"
};

const std::pair<int, int> YamadaState_Attack_Wormchi::AniCurFrame = std::pair<int, int>(5, 3);
const float YamadaState_Attack_Wormchi::AniInterTime = 0.08f;
const float YamadaState_Attack_Wormchi::SitDuration = 5.0f;

YamadaState_Attack_Wormchi::YamadaState_Attack_Wormchi()
{

}

YamadaState_Attack_Wormchi::~YamadaState_Attack_Wormchi()
{

}

void YamadaState_Attack_Wormchi::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void YamadaState_Attack_Wormchi::LoadAnimation()
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
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCurFrame.first, AniCurFrame.second);
}

void YamadaState_Attack_Wormchi::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	std::vector<float> AniFrmTimes(5);
	for (size_t i = 0; i <= 4; ++i)
	{
		AniFrmTimes[i] = AniInterTime;
	}
	AniFrmTimes[3] = 0.2f;

	Render->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<size_t>(State::SitDown)],
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 4,
		.Loop = false,
		.FrameTime = AniFrmTimes
	});

	Render->SetAnimationStartEvent(AniNames[static_cast<size_t>(State::SitDown)], 4, std::bind(&YamadaState_Attack_Wormchi::CreateThrowObjs, this));

	

	Render->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<size_t>(State::Sit)],
		.SpriteName = AniFileName,
		.Start = 5,
		.End = 9,
		.FrameInter = AniInterTime,
		.Loop = true
	});

	Render->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<size_t>(State::GetUp)],
		.SpriteName = AniFileName,
		.Start = 10,
		.End = 12,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}


void YamadaState_Attack_Wormchi::CreateThrowObjs()
{
	static const float Range = 100.f;
	size_t Count = static_cast<size_t>(WormchiObjType::COUNT);
	ThrowObjs.reserve(Count);

	for (size_t i = 0; i < Count; ++i)
	{
		float Angle = 60.f * static_cast<float>(i);
		float4 Offset = float4::AngleToDirection2DToDeg(Angle);
		Offset *= Range;
		Offset.z = Offset.y;

		std::shared_ptr<YamadaWormchiObj> Missile = nullptr;
		Missile = CreateEffect<YamadaWormchiObj>(Offset);
		Missile->Init(static_cast<WormchiObjType>(i));

		ThrowObjs.push_back(Missile);
	}
}






void YamadaState_Attack_Wormchi::EnterState()
{
	BossState_AttackBase::EnterState();
	ChangeStateAndAni(State::SitDown);
}


void YamadaState_Attack_Wormchi::ChangeStateAndAni(State _Next)
{
	CurState = _Next;
	size_t Index = static_cast<size_t>(CurState);
	GetRenderer()->ChangeAnimation(AniNames[Index]);
}


void YamadaState_Attack_Wormchi::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	switch (CurState)
	{
	case YamadaState_Attack_Wormchi::State::SitDown:
		Update_SitDown(_DeltaTime);
		break;
	case YamadaState_Attack_Wormchi::State::Sit:
		Update_Sit(_DeltaTime);
		break;
	case YamadaState_Attack_Wormchi::State::GetUp:
		Update_GetUp(_DeltaTime);
		break;
	}
}

void YamadaState_Attack_Wormchi::Update_SitDown(float _DeltaTime)
{
	AfterEffectTimer += _DeltaTime;
	if (AfterEffectTime < AfterEffectTimer)
	{
		AfterEffectTimer = 0.f;

		std::shared_ptr<AfterImageEffect> Effect = nullptr;
		Effect = CreateEffect<AfterImageEffect>();
		Effect->Init(GetRenderer());
		Effect->SetPlusColor(float4::Green);
	}

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	SitTime = GetLiveTime();
	ChangeStateAndAni(State::Sit);
}




void YamadaState_Attack_Wormchi::Update_Sit(float _DeltaTime)
{
	static const float ThrowTime = 0.8f;

	ThrowTimer += _DeltaTime;
	if ((ThrowTime < ThrowTimer) && (ThrowIndex < ThrowObjs.size()))
	{
		ThrowObjs[ThrowIndex++]->MoveOn();
		ThrowTimer = 0.f;
	}

	float Time = GetLiveTime() - SitTime;
	if (Time < SitDuration)
		return;

	ChangeStateAndAni(State::GetUp);
}

void YamadaState_Attack_Wormchi::Update_GetUp(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::Idle);
}





void YamadaState_Attack_Wormchi::ExitState()
{
	BossState_AttackBase::ExitState();
	CurState = State::SitDown;
	ThrowIndex = 0;
	ThrowTimer = 0.f;

	for (std::shared_ptr<YamadaWormchiObj> ObjPtr : ThrowObjs)
	{
		if (false == ObjPtr->IsWait())
			continue;

		ObjPtr->Extinct();
	}

	ThrowObjs.clear();
}