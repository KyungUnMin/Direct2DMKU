#include "PrecompileHeader.h"
#include "NoiseState_Attack_Tackle.h"

#include "DataMgr.h"

#include "NoiseFSM.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"
#include "BackGround.h"
#include "HitEffect.h"

const std::string_view NoiseState_Attack_Tackle::TackleStart_AniFileName = "Noise_TackleStart.png";
const std::string_view NoiseState_Attack_Tackle::TackleLoop_AniFileName = "Noise_TackleLoop.png";
const std::pair<int, int> NoiseState_Attack_Tackle::TackleStart_AniCutFrame = std::pair<int, int>(5, 1);
const std::pair<int, int> NoiseState_Attack_Tackle::TackleLoop_AniCutFrame = std::pair<int, int>(5, 2);
const float NoiseState_Attack_Tackle::AniInterTime = 0.08f;
const int NoiseState_Attack_Tackle::Damage = 10;

NoiseState_Attack_Tackle::NoiseState_Attack_Tackle()
{

}

NoiseState_Attack_Tackle::~NoiseState_Attack_Tackle()
{

}

void NoiseState_Attack_Tackle::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void NoiseState_Attack_Tackle::LoadAnimation()
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(TackleStart_AniFileName).GetFullPath(), TackleStart_AniCutFrame.first, TackleStart_AniCutFrame.second);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(TackleLoop_AniFileName).GetFullPath(), TackleLoop_AniCutFrame.first, TackleLoop_AniCutFrame.second);
}

void NoiseState_Attack_Tackle::CreateAnimation()
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


void NoiseState_Attack_Tackle::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(TackleStart_AniFileName);
	EnemyState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 150.f);
}




void NoiseState_Attack_Tackle::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	if (false == IsLaunched)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
		if (false == Render->IsAnimationEnd())
			return;

		Render->ChangeAnimation(TackleLoop_AniFileName);
		IsLaunched = true;
		LaunchTime = GetLiveTime();

		
		GetVecToPlayer();

		TackleDir = BossState_AttackBase::GetVecToExpectPlayerPos();
		TackleDir.Normalize();

		//�̵��� �������� �ٶ󺻴�
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
	
	GetFSM()->ChangeState(NoiseStateType::Idle);
}




bool NoiseState_Attack_Tackle::TackleMove(float _DeltaTime)
{
	float TackleTimer = GetLiveTime() - LaunchTime;

	//�̵� �ð��� ���� ���
	if (TackleDuration < TackleTimer)
		return false;

	//���ӵ��� ���� ���� �Լ��� �ӵ��� ������
	float Ratio = (TackleTimer / TackleDuration);
	Ratio = std::clamp(Ratio, 0.1f, 1.f);
	const float SinValue = sinf(GameEngineMath::PIE * Ratio);

	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	float4 NowPos = EnemyTrans->GetLocalPosition();
	float4 NextPos = NowPos + (TackleDir * SinValue * MaxSpeed * _DeltaTime);

	//���� �ε��� ���1
	std::shared_ptr<BackGround> BGPtr = GetBackGround();
	if (true == BGPtr->IsBlockPos(NextPos))
	{
		CreateCollEffect();
		return false;
	}

	//���� �ε��� ���2
	std::pair<int,int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
	{
		CreateCollEffect();
		return false;
	}

	//������ �̵��ϴ� ���
	EnemyTrans->SetLocalPosition(NextPos);

	//�÷��̾�� �浹üũ
	if(true == EnemyState_AttackBase::AttackCheck())
	{
		CreateCollEffect();
		GetFSM()->ChangeState(NoiseStateType::Taunt);
	}

	return true;
}

void NoiseState_Attack_Tackle::CreateCollEffect()
{
	static const float4 Offset = float4::Up * 100.f;
	static const float4 Scale = float4{ 0.5f, 1.f };


	std::shared_ptr<HitEffect> Effect = nullptr;
	Effect = EnemyState_AttackBase::CreateEffect<HitEffect>(Offset, Scale);
	Effect->OffHitSpark();

	GetCamCtrl()->SetShakeState(0.5f);
}


void NoiseState_Attack_Tackle::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}


void NoiseState_Attack_Tackle::ExitState()
{
	BossState_AttackBase::ExitState();
	IsLaunched = false;
	TackleDir = float4::Zero;
	LaunchTime = 0.f;
}