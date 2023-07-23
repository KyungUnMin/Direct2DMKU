#include "PrecompileHeader.h"
#include "NoiseState_Attack_AxeDash.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "SoundMgr.h"

#include "NoiseFSM.h"
#include "NoiseAxe.h"
#include "FieldEnemyBase.h"
#include "BackGround.h"
#include "AfterImageEffect.h"

#include "NoiseState_Attack_AxeGrind.h"
#include "NoiseFan.h"

const std::vector<std::string_view> NoiseState_Attack_AxeDash::AniFileNames =
{
	"Noise_AxeDashStart.png",
	"Noise_AxeDashLoop.png",
	"Noise_AxeDashLand.png"
};

const float NoiseState_Attack_AxeDash::AniInterTime = 0.08f;
const float NoiseState_Attack_AxeDash::StartDashRotRange = 20.f;

/*반사 영역 범위	Left, Right, Up, Down*/
const float4 NoiseState_Attack_AxeDash::ReflectArea = { -503.f, 503.f, -60.f, -446.f };
//반사 횟수
const size_t NoiseState_Attack_AxeDash::ReflectMaxCnt = 5;


//도끼가 이동할때 StandardFollowRange 의 거리를 StandardFollowDuration 의 시간으로 이동
const float NoiseState_Attack_AxeDash::StandardFollowRange = 1000.f;
const float NoiseState_Attack_AxeDash::StandardFollowDuration = 0.5f;

const float4 NoiseState_Attack_AxeDash::FanSpawnPos = { 510.f,  -100.f,  -100.f };

NoiseState_Attack_AxeDash::NoiseState_Attack_AxeDash()
{

}

NoiseState_Attack_AxeDash::~NoiseState_Attack_AxeDash()
{

}

void NoiseState_Attack_AxeDash::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	EnemyStateBase::SetUnbeatable();

	ReflectPositions.resize(ReflectMaxCnt + 1);
}

void NoiseState_Attack_AxeDash::LoadAnimation()
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
	Dir.Move("Attack");
	Dir.Move("AxeDash");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::DashStart)]).GetFullPath(), 5, 1);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::DashLoop)]).GetFullPath(), 5, 1);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::DashLand)]).GetFullPath(), 5, 2);
}

void NoiseState_Attack_AxeDash::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	size_t Index = -1;
	std::string_view AniName = "";


	Index = static_cast<size_t>(State::DashStart);
	AniName = AniFileNames[Index];
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = 3,
		.FrameInter = AniInterTime,
		.Loop = false,
	});


	Index = static_cast<size_t>(State::DashLoop);
	AniName = AniFileNames[Index];
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.FrameInter = AniInterTime,
		.Loop = true,
	});


	Index = static_cast<size_t>(State::DashLand);
	AniName = AniFileNames[Index];
	Render->CreateAnimation
	({
		.AnimationName = AniName ,
		.SpriteName = AniName,
		.Start = 0,
		.End = 5,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}





void NoiseState_Attack_AxeDash::EnterState()
{
	BossState_AttackBase::EnterState();

	ChangeStateAndAni(State::DashStart);
	OffMainCollider();
	
	CreateFan();
}


void NoiseState_Attack_AxeDash::ChangeStateAndAni(State _Next)
{
	CurState = _Next;

	if (State::WaitIdle == CurState)
	{
		GetRenderer()->ChangeAnimation(NoiseState_Attack_AxeGrind::Idle_AniFileName);
	}
	else if (State::WaitCatch == CurState)
	{
		GetRenderer()->ChangeAnimation(NoiseState_Attack_AxeGrind::Catch_AniFileName);
	}
	else
	{
		size_t Index = static_cast<size_t>(CurState);
		GetRenderer()->ChangeAnimation(AniFileNames[Index]);
	}
}



void NoiseState_Attack_AxeDash::CreateFan()
{
	EnemySpawner& FanSpawner = FieldLevelBase::GetPtr()->GetEnemySpawner();

	//2명 이상일 땐 더이상 팬을 생성하지 않음
	if (2 <= NoiseFan::GetCurFanCount())
		return;

	FanSpawner.CreateEnemy(EnemyType::NoiseFan, FanSpawnPos)->LookDir(false);
	FanSpawner.CreateEnemy(EnemyType::NoiseFan, FanSpawnPos * float4{ -1.f, 1.f, 1.f });
}


void NoiseState_Attack_AxeDash::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	switch (CurState)
	{
	case NoiseState_Attack_AxeDash::State::DashStart:
		Update_DashStart(_DeltaTime);
		break;
	case NoiseState_Attack_AxeDash::State::DashLoop:
		Update_DahsLoopEffect(_DeltaTime);
		Update_DashLoop(_DeltaTime);
		break;
	case NoiseState_Attack_AxeDash::State::DashLand:
		Update_DashLand(_DeltaTime);
		break;
	case NoiseState_Attack_AxeDash::State::WaitIdle:
		Update_WaitIdle(_DeltaTime);
		break;
	case NoiseState_Attack_AxeDash::State::WaitCatch:
		Update_WaitCatch(_DeltaTime);
		break;
	}
}

void NoiseState_Attack_AxeDash::Update_DashStart(float _DeltaTime)
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	FieldEnemyBase* Enemy = GetEnemy();
	ReflectPositions.front() = Enemy->GetTransform()->GetWorldPosition();

	float RotAngle = GameEngineRandom::MainRandom.RandomFloat(-StartDashRotRange, StartDashRotRange);
	DashDir = GetVecToPlayer().NormalizeReturn();
	DashDir.RotationZDeg(RotAngle);
	DashDir.Normalize();

	//왼쪽으로 이동해야 한다면 오른쪽을 바라본다(뒤로 이동하기 때문에 이동방향과 반대가 되어야 함)
	Enemy->LookDir(DashDir.x < 0.f);

	Axe = CreateEffect<NoiseAxe>();
	AxeLoopSFX = SoundMgr::PlaySFX("NoiseAxe_Loop.wav", true);
	ChangeStateAndAni(State::DashLoop);

	SoundMgr::PlaySFX("Noise_AxeDash_Launch_Voice.wav");
	SoundMgr::PlaySFX("Noise_AxeDash_Launch_Effect.wav");
}





void NoiseState_Attack_AxeDash::Update_DahsLoopEffect(float _DeltaTime)
{
	static const float EffectTime = 0.05f;
	static float Timer = 0.f;

	Timer += _DeltaTime;
	if (Timer < EffectTime)
		return;

	std::shared_ptr<AfterImageEffect> Effect = nullptr;
	Effect = FieldLevelBase::GetPtr()->CreateActor<AfterImageEffect>(UpdateOrder::Effect);
	Effect->Init(GetRenderer());
	Effect->SetDuration(0.5f);

	GameEngineTransform* EffectTrans = Effect->GetTransform();
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	EffectTrans->SetWorldPosition(EnemyTrans->GetWorldPosition());

	Timer = 0.f;
}


void NoiseState_Attack_AxeDash::Update_DashLoop(float _DeltaTime)
{
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();

	float4 PrevPos = EnemyTrans->GetWorldPosition();
	float4 NextPos = PrevPos + (DashDir * DashSpeed * _DeltaTime);

	//다음에 이동할 위치가 영역 밖으로 나가는지 검사
	ReflectType IsReflect = ReflectType::None;
	if (NextPos.x < ReflectArea.Arr1D[static_cast<size_t>(ReflectType::Left)])
	{
		IsReflect = ReflectType::Left;
	}
	else if (ReflectArea.Arr1D[static_cast<size_t>(ReflectType::Right)] < NextPos.x)
	{
		IsReflect = ReflectType::Right;
	}
	else if (ReflectArea.Arr1D[static_cast<size_t>(ReflectType::Up)] < NextPos.y)
	{
		IsReflect = ReflectType::Up;
	}
	else if (NextPos.y < ReflectArea.Arr1D[static_cast<size_t>(ReflectType::Down)])
	{
		IsReflect = ReflectType::Down;
	}

	//영역 밖으로 나가지 않았다면 이동을 실행
	if (ReflectType::None == IsReflect)
	{
		NextPos.z = NextPos.y;
		EnemyTrans->SetWorldPosition(NextPos);
		return;
	}


	//영역 밖으로 나갔다면 방향을 바꾸거나, 다음 State로 변경
	ReflectDirection(PrevPos, IsReflect);

	//시야 방향 전환
	SetLookDir(IsReflect);

	SoundMgr::PlaySFX("Noise_AxeDash_Reflect_Effect.wav");
}


void NoiseState_Attack_AxeDash::ReflectDirection(const float4 _PrevPos, ReflectType _Type)
{
	ReflectPositions[ReflectCount] = _PrevPos;

	++ReflectCount;
	if (ReflectPositions.size() <= ReflectCount)
	{
		OnMainCollider();
		ChangeStateAndAni(State::DashLand);
		return;
	}


	if (ReflectType::Left == _Type || ReflectType::Right == _Type)
	{
		DashDir.x = -DashDir.x;
	}
	else if (ReflectType::Up == _Type || ReflectType::Down == _Type)
	{
		DashDir.y = -DashDir.y;
	}
	else
	{
		MsgAssert("영역밖으로 나가지 않았는데, 방향을 바꾸려고 했습니다");
		return;
	}
}


void NoiseState_Attack_AxeDash::SetLookDir(ReflectType _Type)
{
	if (ReflectPositions.size() <= ReflectCount)
		return;

	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	float4 EnemyPos = EnemyTrans->GetWorldPosition();
	

	if (ReflectType::Left == _Type)
	{
		EnemyTrans->SetLocalNegativeScaleX();
	}
	else if (ReflectType::Right == _Type)
	{
		EnemyTrans->SetLocalPositiveScaleX();
	}
}






void NoiseState_Attack_AxeDash::Update_DashLand(float _DeltaTime)
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	CalcFollowDuration();
	ChangeStateAndAni(State::WaitIdle);

	SoundMgr::PlaySFX("NoiseAxe_Return.wav");
	SoundMgr::PlaySFX("Noise_AxeDash_Reflect_Voice.wav");
}





void NoiseState_Attack_AxeDash::Update_WaitIdle(float _DeltaTime)
{
	GameEngineTransform* AxeTrans = Axe->GetTransform();

	FollowTimer += _DeltaTime;
	float Ratio = (FollowTimer / FollowDuration);
	if (1.f <= Ratio)
	{
		AxeTrans->SetWorldPosition(ReflectPositions[FollowIndex]);
		++FollowIndex;
		FollowTimer = 0.f;

		if (ReflectPositions.size() <= FollowIndex)
		{
			Axe->Death();
			Axe = nullptr;

			AxeLoopSFX.Stop();
			ChangeStateAndAni(State::WaitCatch);
		}
		else
		{
			CalcFollowDuration();
		}

		return;
	}

	float4 NowPos = float4::LerpClamp(ReflectPositions[FollowIndex - 1], ReflectPositions[FollowIndex], Ratio);
	NowPos.z = NowPos.y;
	AxeTrans->SetWorldPosition(NowPos);
}




void NoiseState_Attack_AxeDash::Update_WaitCatch(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}


void NoiseState_Attack_AxeDash::CalcFollowDuration()
{
	const float4& StartPos = ReflectPositions[FollowIndex - 1];
	const float4& DestPos = ReflectPositions[FollowIndex];

	float MoveLength = (DestPos - StartPos).Size();

	float Ratio = MoveLength / StandardFollowRange;
	FollowDuration = StandardFollowDuration * Ratio;
}






void NoiseState_Attack_AxeDash::ExitState()
{
	BossState_AttackBase::ExitState();
	OnMainCollider();

	//임시
	if (nullptr != Axe)
	{
		Axe->Death();
		Axe = nullptr;
	}
	

	ReflectCount = 1;
	FollowIndex = 1;
	FollowTimer = 0.f;

	bool IsPlay = false;
	AxeLoopSFX.isPlaying(&IsPlay);
	if (true == IsPlay)
	{
		AxeLoopSFX.Stop();
	}
}