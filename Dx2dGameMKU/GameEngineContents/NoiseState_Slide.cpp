#include "PrecompileHeader.h"
#include "NoiseState_Slide.h"

#include "RCGEnums.h"

#include "NoiseFSM.h"
#include "FieldLevelBase.h"
#include "BackGround.h"
#include "FieldEnemyBase.h"
#include "AfterImageEffect.h"


const std::vector<std::string_view> NoiseState_Slide::AniFileNames =
{
	"Noise_SlideStart.png",
	"Noise_SlideMiddle.png",
	"Noise_SlideEnd.png"
};

const float NoiseState_Slide::AniInterTime = 0.08f;

NoiseState_Slide::NoiseState_Slide()
{

}

NoiseState_Slide::~NoiseState_Slide()
{

}


void NoiseState_Slide::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
}

void NoiseState_Slide::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Noise");
	Dir.Move("Movement");
	Dir.Move("Slide");
	
	const std::vector<std::pair<int, int>> CutFrms =
	{
		{5, 1},
		{5, 1},
		{5, 2},
	};
	
	for (size_t i = 0; i < CutFrms.size(); ++i)
	{
		const std::string_view& Path = AniFileNames[i];
		const std::pair<int, int>& Cut = CutFrms[i];
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Path).GetFullPath(), Cut.first, Cut.second);
	}
}

void NoiseState_Slide::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	std::string_view AniName = "";


	AniName = AniFileNames[static_cast<size_t>(State::Start)];
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = 3,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	AniName = AniFileNames[static_cast<size_t>(State::Loop)];
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = 3,
		.FrameInter = AniInterTime,
		.Loop = true,
	});

	AniName = AniFileNames[static_cast<size_t>(State::End)];
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}



void NoiseState_Slide::EnterState()
{
	EnemyStateBase::EnterState();
	ChangeStateAndAni(State::Start);

	//바라 보고 있는 방향의 반대로(뒤로) 움직일 예정
	MoveDir = EnemyStateBase::IsRightDir() ? float4::Left : float4::Right;
}


void NoiseState_Slide::ChangeStateAndAni(State _Next)
{
	CurState = _Next;
	size_t Index = static_cast<size_t>(CurState);
	GetRenderer()->ChangeAnimation(AniFileNames[Index]);
}



void NoiseState_Slide::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	switch (CurState)
	{
	case NoiseState_Slide::State::Start:
		Update_Start(_DeltaTime);
		break;
	case NoiseState_Slide::State::Loop:
		Update_Loop(_DeltaTime);
		break;
	case NoiseState_Slide::State::End:
		Update_End(_DeltaTime);
		break;
	}
}


void NoiseState_Slide::Update_Start(float _DeltaTime)
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	ChangeStateAndAni(State::Loop);
}

void NoiseState_Slide::Update_Loop(float _DeltaTime)
{
	Update_LoopEffect(_DeltaTime);
	Update_LoopMove(_DeltaTime);
}

void NoiseState_Slide::Update_LoopEffect(float _DeltaTime)
{
	static const float EffectTime = 0.1f;
	static float Timer = 0.f;

	Timer += _DeltaTime;
	if (Timer < EffectTime)
		return;

	std::shared_ptr<AfterImageEffect> Effect = nullptr;
	Effect = FieldLevelBase::GetPtr()->CreateActor<AfterImageEffect>(UpdateOrder::Effect);
	Effect->Init(GetRenderer());

	GameEngineTransform* EffectTrans = Effect->GetTransform();
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	EffectTrans->SetWorldPosition(EnemyTrans->GetWorldPosition());

	Timer = 0.f;
}

void NoiseState_Slide::Update_LoopMove(float _DeltaTime)
{
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();

	float4 PrevPos = EnemyTrans->GetWorldPosition();
	float4 NextPos = PrevPos + (MoveDir * MoveSpeed * _DeltaTime);

	if (true == BGPtr->IsBlockPos(NextPos))
	{
		ChangeStateAndAni(State::End);
		return;
	}

	std::pair<int, int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
	{
		ChangeStateAndAni(State::End);
		return;
	}

	EnemyTrans->SetWorldPosition(NextPos);
}





void NoiseState_Slide::Update_End(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}
