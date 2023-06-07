#include "PrecompileHeader.h"
#include "MisuzuState_Attack_Tackle.h"

#include "DataMgr.h"

#include "MisuzuFSM.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"
#include "BackGround.h"
#include "HitEffect.h"

const std::string_view MisuzuState_Attack_Tackle::TackleStart_AniFileName = "Misuzu_TackleStart.png";
const std::string_view MisuzuState_Attack_Tackle::TackleLoop_AniFileName = "Misuzu_TackleLoop.png";
const std::pair<int, int> MisuzuState_Attack_Tackle::TackleStart_AniCutFrame = std::pair<int, int>(5, 1);
const std::pair<int, int> MisuzuState_Attack_Tackle::TackleLoop_AniCutFrame = std::pair<int, int>(5, 2);
const float MisuzuState_Attack_Tackle::AniInterTime = 0.08f;
const int MisuzuState_Attack_Tackle::Damage = 25;

MisuzuState_Attack_Tackle::MisuzuState_Attack_Tackle()
{

}

MisuzuState_Attack_Tackle::~MisuzuState_Attack_Tackle()
{

}

void MisuzuState_Attack_Tackle::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void MisuzuState_Attack_Tackle::LoadAnimation()
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
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(TackleStart_AniFileName).GetFullPath(), TackleStart_AniCutFrame.first, TackleStart_AniCutFrame.second);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(TackleLoop_AniFileName).GetFullPath(), TackleLoop_AniCutFrame.first, TackleLoop_AniCutFrame.second);
}

void MisuzuState_Attack_Tackle::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = TackleStart_AniFileName,
		.SpriteName = TackleStart_AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false
	});

	Render->CreateAnimation
	({
		.AnimationName = TackleLoop_AniFileName,
		.SpriteName = TackleLoop_AniFileName,
		.Start = 0,
		.End = 7,
		.FrameInter = AniInterTime,
		.Loop = true,
	});
}


void MisuzuState_Attack_Tackle::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(TackleStart_AniFileName);
	EnemyState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 200.f);
}




void MisuzuState_Attack_Tackle::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == IsLaunched)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
		if (false == Render->IsAnimationEnd())
			return;

		Render->ChangeAnimation(TackleLoop_AniFileName);
		IsLaunched = true;
		LaunchTime = GetLiveTime();

		CalMoveDir();

		//이동할 방향으로 바라본다
		GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
		if (0.f < TackleDir.x)
		{
			EnemyTrans->SetLocalPositiveScaleX();
		}
		else
		{
			EnemyTrans->SetLocalNegativeScaleX();
		}

		return;
	}


	if (true == TackleMove(_DeltaTime))
		return;
	
	GetFSM()->ChangeState(MisuzuStateType::Idle);
}



void MisuzuState_Attack_Tackle::CalMoveDir()
{
	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	float4 PlayerPos = Player->GetTransform()->GetWorldPosition();
	float4 EnemyPos = GetEnemy()->GetTransform()->GetWorldPosition();


	//이 Enemy->Player 벡터
	float4 EnemyToPlayer = (PlayerPos - EnemyPos);

	//플레이어가 움직이고 있던 방향
	float4 PlayerMoveDir = Player->GetMoveDirVec();

	//플레이어가 정지해있었다면 방향을 예측하지 않는다
	if (true == PlayerMoveDir.IsZero())
	{
		TackleDir = EnemyToPlayer.NormalizeReturn();
		return;
	}


	//Enemy와 플레이어사이 거리
	float LengthToPlayer = EnemyToPlayer.Size();
	//플레이어 이동 경로 정규화
	PlayerMoveDir.Normalize();

	//플레이어의 예상경로
	float4 PlayerNextPos = PlayerPos + (PlayerMoveDir * LengthToPlayer);
	
	TackleDir = (PlayerNextPos - EnemyPos).NormalizeReturn();
}



bool MisuzuState_Attack_Tackle::TackleMove(float _DeltaTime)
{
	float TackleTimer = GetLiveTime() - LaunchTime;

	//이동 시간이 지난 경우
	if (TackleDuration < TackleTimer)
		return false;

	//가속도를 위해 사인 함수로 속도가 조절됨
	float Ratio = (TackleTimer / TackleDuration);
	Ratio = std::clamp(Ratio, 0.1f, 1.f);
	const float SinValue = sinf(GameEngineMath::PIE * Ratio);

	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	float4 NowPos = EnemyTrans->GetLocalPosition();
	float4 NextPos = NowPos + (TackleDir * SinValue * MaxSpeed * _DeltaTime);

	//벽에 부딪힌 경우1
	std::shared_ptr<BackGround> BGPtr = GetBackGround();
	if (true == BGPtr->IsBlockPos(NextPos))
	{
		CreateCollEffect();
		return false;
	}

	//벽에 부딪힌 경우2
	std::pair<int,int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
	{
		CreateCollEffect();
		return false;
	}

	//무사히 이동하는 경우
	EnemyTrans->SetLocalPosition(NextPos);

	//플레이어와 충돌체크
	if(true == EnemyState_AttackBase::AttackCheck())
	{
		CreateCollEffect();
		GetFSM()->ChangeState(MisuzuStateType::Taunt);
	}

	return true;
}

void MisuzuState_Attack_Tackle::CreateCollEffect()
{
	static const float4 Offset = float4::Up * 100.f;
	static const float4 Scale = float4{ 0.5f, 1.f };


	std::shared_ptr<HitEffect> Effect = nullptr;
	Effect = EnemyState_AttackBase::CreateEffect<HitEffect>(Offset, Scale);
	Effect->OffHitSpark();

	GetCamCtrl()->SetShakeState(0.5f);
}


void MisuzuState_Attack_Tackle::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}


void MisuzuState_Attack_Tackle::ExitState()
{
	EnemyState_AttackBase::ExitState();
	IsLaunched = false;
	TackleDir = float4::Zero;
	LaunchTime = 0.f;
}