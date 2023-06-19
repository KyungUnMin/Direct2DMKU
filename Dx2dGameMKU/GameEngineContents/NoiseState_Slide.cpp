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
	Collider = GetEnemy()->GetAttackCollider();
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

	Collider->GetTransform()->SetLocalScale(float4::One * 50.f);
	Collider->GetTransform()->SetLocalPosition(float4::Right * 50.f);
}


void NoiseState_Slide::ChangeStateAndAni(State _Next)
{
	CurState = _Next;
	size_t Index = static_cast<size_t>(CurState);
	GetRenderer()->ChangeAnimation(AniFileNames[Index]);
}

void NoiseState_Slide::SettingDir()
{
	FieldEnemyBase* Enemy = GetEnemy();
	
	float4 EnemyPos = Enemy->GetTransform()->GetWorldPosition();
	const float4 VecToPlayer = GetVecToPlayer(true);



	//플레이어로 향하는 길이보다 벽쪽으로 향하는 길이가 더 짧은 경우 벽쪽으로 이동한다
	//또는 플레이어와의 거리가 너무 짧은 경우에도 무조껀 벽쪽으로 간다
	float4 ReversePosToPlayer = (EnemyPos - VecToPlayer);
	if ((true == BGPtr->IsBlockPos(ReversePosToPlayer)) || (VecToPlayer.Size() < 10.f))
	{
		//오른쪽 영역에 있는 경우 오른쪽으로 이동한다
		if (0.f < EnemyPos.x)
		{
			MoveDir = float4::Right;
			Enemy->LookDir(false);
		}

		//왼쪽 영역에 있는 경우 왼쪽으로 이동한다
		else
		{
			MoveDir = float4::Left;
			Enemy->LookDir(true);
		}

		return;
	}


	//플레이어 쪽으로 이동하는 경우
	MoveDir = VecToPlayer.NormalizeReturn();

	//뒤로 이동하기 때문에 이동방향과 반대 방향을 바라 본다
	bool IsDirRight = (MoveDir.x < 0.f) ? true : false;
	Enemy->LookDir(IsDirRight);

	//플레이어 쪽으로 이동하는 경우엔 벽 충돌과 상관없이 CollisionExit될때 이벤트 발생
	ReflectionCount = 1;
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
	if (true == Update_LoopMove(_DeltaTime))
	{
		GetFSM()->ChangeState(NoiseStateType::AxeGrind);
		return;
	}


	if (2 == ReflectionCount)
	{
		ChangeStateAndAni(State::End);
		return;
	}

	if (false == Update_CheckPos())
		return;

	ChangeStateAndAni(State::End);
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



bool NoiseState_Slide::Update_CheckPos()
{
	if (0 == ReflectionCount)
		return false;

	if (nullptr == Collider->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D))
	{
		//CollisionExit 되는 순간
		if (true == PrevCollision)
			return true;

		return false;
	}

	//충돌중
	PrevCollision = true;
	return false;
}



bool NoiseState_Slide::Update_LoopMove(float _DeltaTime)
{
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();

	float4 PrevPos = EnemyTrans->GetWorldPosition();
	float4 NextPos = PrevPos + (MoveDir * MoveSpeed * _DeltaTime);

	if (true == BGPtr->IsBlockPos(NextPos))
	{
		return ChangeDir();
	}

	std::pair<int, int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
	{
		return ChangeDir();
	}

	NextPos.z = NextPos.y;
	EnemyTrans->SetWorldPosition(NextPos);
	return false;
}


bool NoiseState_Slide::ChangeDir()
{
	static const int Percent = 50;

	int RandNum = GameEngineRandom::MainRandom.RandomInt(0, 100);
	if (RandNum < Percent)
		return true;


	MoveDir.x = -MoveDir.x;
	++ReflectionCount;

	GetEnemy()->DirectionFlip();
	return false;
}




void NoiseState_Slide::Update_End(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}



void NoiseState_Slide::ExitState()
{
	EnemyStateBase::ExitState();
	EnemyStateBase::OnMainCollider();
	ReflectionCount = 0;
	PrevCollision = false;
}
