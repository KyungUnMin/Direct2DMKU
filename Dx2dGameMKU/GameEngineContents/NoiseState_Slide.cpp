#include "PrecompileHeader.h"
#include "NoiseState_Slide.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "NoiseFSM.h"
#include "FieldLevelBase.h"
#include "BackGround.h"
#include "FieldEnemyBase.h"
#include "AfterImageEffect.h"
#include "FieldPlayer.h"
#include "BossFSMBase.h"


const std::vector<std::string_view> NoiseState_Slide::AniFileNames =
{
	"Noise_SlideStart.png",
	"Noise_SlideMiddle.png",
	"Noise_SlideEnd.png"
};

const float NoiseState_Slide::AniInterTime = 0.08f;
const float NoiseState_Slide::MoveDuration = 0.25f;

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
	SettingDir();

	EnemyStateBase::OffMainCollider();
}


void NoiseState_Slide::ChangeStateAndAni(State _Next)
{
	CurState = _Next;
	size_t Index = static_cast<size_t>(CurState);
	GetRenderer()->ChangeAnimation(AniFileNames[Index]);
}

void NoiseState_Slide::SettingDir()
{
	static const float BackMoveOffset = 200.f;
	static const float ToPlayerMoveOffset = 100.f;

	int RandNum = GameEngineRandom::MainRandom.RandomInt(0, 1);


	FieldEnemyBase* Enemy = GetEnemy();
	GameEngineTransform* EnemyTrans = Enemy->GetTransform();
	float4 EnemyPos = EnemyTrans->GetWorldPosition();


	//플레이어 쪽으로 이동하는 경우
	if (0 == RandNum % 2)
	{
		IsTargetPlayer = true;
		float4 MoveDir = GetVecToPlayer();
		float4 PlayerPos = EnemyPos + MoveDir;
		MoveDir.Normalize();

		StartPos = EnemyPos;
		DestPos = PlayerPos + (MoveDir * ToPlayerMoveOffset);

		//뒤로 이동하기 때문에 이동방향과 반대 방향을 바라 본다
		bool IsDirRight = (MoveDir.x < 0.f) ? true : false;
		Enemy->LookDir(IsDirRight);
		return;
	}

	//백점프를 하는 경우
	
	//바라보고 있는 방향 뒤쪽으로 이동
	float4 MoveDir = IsRightDir() ? float4::Left : float4::Right;
	StartPos = EnemyPos;
	DestPos = EnemyPos + (MoveDir * BackMoveOffset);
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

	ResetLiveTime();
	ChangeStateAndAni(State::Loop);
}

void NoiseState_Slide::Update_Loop(float _DeltaTime)
{
	float Ratio = GetLiveTime() / MoveDuration;

	Update_LoopEffect(_DeltaTime);
	Update_LoopMove(Ratio);

	if (Ratio < 1.f)
		return;

	ChangeStateAndAni(State::End);
}




void NoiseState_Slide::Update_LoopEffect(float _DeltaTime)
{
	static const float EffectTime = 0.01f;
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


void NoiseState_Slide::Update_LoopMove(float _Ratio)
{
	float4 NextPos = float4::LerpClamp(StartPos, DestPos, _Ratio);
	
	if (true == BGPtr->IsBlockPos(NextPos))
		return;

	std::pair<int, int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
		return;


	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	NextPos.z = NextPos.y;
	EnemyTrans->SetWorldPosition(NextPos);
}




void NoiseState_Slide::Update_End(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	if (true == IsTargetPlayer)
	{
		GetFSM()->ChangeState(NoiseStateType::GuitarSlash);
	}
	else
	{
		GetFSM()->ChangeState(NoiseStateType::AxeGrind);
	}
}



void NoiseState_Slide::ExitState()
{
	EnemyStateBase::ExitState();
	EnemyStateBase::OnMainCollider();
	IsTargetPlayer = false;
}
