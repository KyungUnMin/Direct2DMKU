#include "PrecompileHeader.h"
#include "YamadaState_Attack_Blast.h"

#include "DataMgr.h"

#include "YamadaFSM.h"
#include "FieldPlayer.h"
#include "LightEffect.h"
#include "AfterImageEffect.h"

const std::string_view YamadaState_Attack_Blast::AniName = "Attack_Blast";
const std::string_view YamadaState_Attack_Blast::AniFileName = "Yamada_Blast.png";
const std::pair<int, int> YamadaState_Attack_Blast::AniCutFrame = std::pair<int, int>(5, 4);
const float YamadaState_Attack_Blast::AniInterTime = 0.08f;
const int YamadaState_Attack_Blast::Damage = 5;
const float4 YamadaState_Attack_Blast::ColOffset = float4{ 100.f, 0.f, 0.f };
const float4 YamadaState_Attack_Blast::ColScale = float4{ 150.f, 150.f, 150.f };

YamadaState_Attack_Blast::YamadaState_Attack_Blast()
{

}

YamadaState_Attack_Blast::~YamadaState_Attack_Blast()
{

}

void YamadaState_Attack_Blast::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	AfterEffectTimer = 0.f;
}

void YamadaState_Attack_Blast::LoadAnimation()
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_Attack_Blast::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 15,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	//BlastEffect 생성
	Render->SetAnimationStartEvent(AniName, 7, std::bind(&YamadaState_Attack_Blast::CreateBlastEffect, this));

	for (size_t i = 8; i < 14; ++i)
	{
		EnemyState_AttackBase::SetAttackCheckFrame(AniName, i);
	}
}

void YamadaState_Attack_Blast::CreateBlastEffect()
{
	float4 LightOffset = float4{ ColOffset.x ,100.f };
	const float4 LightScale = float4::One * 300.f;

	//왼쪽을 보고 있는 경우
	if (false == EnemyStateBase::IsRightDir())
	{
		LightOffset.x = -LightOffset.x;
	}

	std::shared_ptr<LightEffect> Effect = nullptr;
	Effect = CreateEffect<LightEffect>(LightOffset);

	//보라색 불빛
	float4 LightColor = float4::Red + float4::Blue;
	LightColor.a = 1.f;
	Effect->GetRenderTrans()->SetLocalScale(LightScale);

	//7프레임 동안
	Effect->Flicker(float4::Red, AniInterTime * 7.f);
}


void YamadaState_Attack_Blast::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue(ColOffset, ColScale);
}



void YamadaState_Attack_Blast::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	CreateAfterEffect(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(YamadaStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	YamadaStateType RandomAttack = static_cast<YamadaStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<YamadaStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(YamadaStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}

void YamadaState_Attack_Blast::CreateAfterEffect(float _DeltaTime)
{
	AfterEffectTimer += _DeltaTime;
	if (AfterEffectTimer < 0.05f)
		return;

	AfterEffectTimer = 0.f;
	static const float OffsetX = 100.f;
	const float4 OffsetPos = EnemyStateBase::IsRightDir() ? float4::Left * OffsetX : float4::Right * OffsetX;

	std::shared_ptr<AfterImageEffect> Effect = nullptr;
	Effect = CreateEffect<AfterImageEffect>(OffsetPos, float4::One * 1.5f);
	Effect->Init(GetRenderer());
	Effect->SetPlusColor(float4::Blue);
}


void YamadaState_Attack_Blast::Attack()
{
	size_t CurFrm = GetRenderer()->GetCurrentFrame();
	bool Result = false;

	//마지막 공격은 날라가기
	if (13 == CurFrm)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	}
	//짝수 프레임은 얼굴 공격
	else if(0 == CurFrm % 2)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Face();
	}
	//홀수 프레임은 턱 공격
	else
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Jaw();
	}

	//공격이 정상적으로 먹혔다면
	if (false == Result)
		return;

	//플레이어 데미지 감소
	DataMgr::MinusPlayerHP(Damage);
}
