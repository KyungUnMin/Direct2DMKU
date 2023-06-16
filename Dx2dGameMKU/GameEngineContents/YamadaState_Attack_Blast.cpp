#include "PrecompileHeader.h"
#include "YamadaState_Attack_Blast.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "DataMgr.h"

#include "YamadaFSM.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"

#include "AfterImageEffect.h"

const std::string_view YamadaState_Attack_Blast::AniName = "Attack_Blast";
const std::string_view YamadaState_Attack_Blast::AniFileName = "Yamada_Blast.png";
const std::pair<int, int> YamadaState_Attack_Blast::AniCutFrame = std::pair<int, int>(5, 4);
const float YamadaState_Attack_Blast::AniInterTime = 0.08f;

const int YamadaState_Attack_Blast::Damage = 5;
const float4 YamadaState_Attack_Blast::ColOffset = float4{ 100.f, 0.f, 0.f };
const float4 YamadaState_Attack_Blast::ColScale = float4{ 150.f, 150.f, 150.f };

const std::string_view YamadaState_Attack_Blast::BlastName = "Yamada_Blast_Effect.png";

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
	CreateBlastEffect();
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(BlastName).GetFullPath(), 1, 8);
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

	
	Render->SetAnimationStartEvent(AniName, 7, [this]()
	{
		EffectHandler->On();
	});


	for (size_t i = 8; i < 14; ++i)
	{
		EnemyState_AttackBase::SetAttackCheckFrame(AniName, i);
	}
}

void YamadaState_Attack_Blast::CreateBlastEffect()
{
	const float4 EffectRenderScale = float4{ 256.f, 64.f, 1.f };
	const float4 DarkPupple = { 0.25f, 0.f, 0.6f, 0.5f };

	FieldEnemyBase* Enemy = GetEnemy();

	EffectHandler = Enemy->CreateComponent<GameEngineComponent>();
	EffectRender = Enemy->CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);

	GameEngineTransform* EffectRenderTrans = EffectRender->GetTransform();
	GameEngineTransform* EffectHandlerTrans = EffectHandler->GetTransform();
	EffectRenderTrans->SetParent(EffectHandlerTrans);

	EffectRenderTrans->SetLocalScale(EffectRenderScale);
	EffectRenderTrans->SetLocalPosition(float4::Right * EffectRenderScale.hx());
	EffectHandlerTrans->SetLocalPosition(float4::Up * 100.f);


	EffectRender->CreateAnimation
	({
		.AnimationName = BlastName,
		.SpriteName = BlastName,
		.FrameInter = AniInterTime,
		.Loop = true,
	});
	EffectRender->ChangeAnimation(BlastName);
	EffectRender->ColorOptionValue.MulColor = DarkPupple;
	
	for (size_t i = 0; i < 8; ++i)
	{
		EffectRender->SetAnimationStartEvent(BlastName, i, [this]()
		{
			static const float RotOffset = 20.f;
			float RandRot = GameEngineRandom::MainRandom.RandomFloat(-RotOffset, RotOffset);

			EffectHandler->GetTransform()->SetLocalRotation(float4::Forward * RandRot);
		});
	}

	EffectHandler->Off();
}




void YamadaState_Attack_Blast::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(ColOffset, ColScale);

	GetCamCtrl()->SetZoom(0.98f, 0.05f);

	if (true == GetConvertFSM<YamadaFSM>()->IsLastPhase())
	{
		EffectRender->ColorOptionValue.MulColor = float4{ 0.6f, 0.f, 0.f, 0.6f };
	}
}




void YamadaState_Attack_Blast::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	Update_AfterEffect(_DeltaTime);
	
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	
	GetFSM()->ChangeState(YamadaStateType::Taunt);
}



void YamadaState_Attack_Blast::Update_AfterEffect(float _DeltaTime)
{
	AfterEffectTimer += _DeltaTime;
	if (AfterEffectTimer < 0.05f)
		return;

	AfterEffectTimer = 0.f;

	std::shared_ptr<AfterImageEffect> Effect = nullptr;
	Effect = CreateEffect<AfterImageEffect>();
	Effect->Init(GetRenderer());
	Effect->SetPlusColor(float4::Blue);
}


void YamadaState_Attack_Blast::Attack()
{
	size_t CurFrm = GetRenderer()->GetCurrentFrame();
	bool Result = false;

	//마지막 공격은 날라가기(방어 불가능)
	if (13 == CurFrm)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_BlowBack(true);
	}
	//짝수 프레임은 얼굴 공격
	else if(0 == CurFrm % 2)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Face(true);
	}
	//홀수 프레임은 턱 공격
	else
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Jaw(true);
	}

	//공격이 정상적으로 먹혔다면
	if (false == Result)
		return;

	if (false == FirstHit)
	{
		GetCamCtrl()->SetShakeState(0.5f);
		FirstHit = true;
	}
	

	//플레이어 데미지 감소
	DataMgr::MinusPlayerHP(Damage);
}

void YamadaState_Attack_Blast::ExitState()
{
	BossState_AttackBase::ExitState();
	FirstHit = false;
	EffectHandler->Off();

	FieldCamController* CamCtrl = GetCamCtrl();
	CamCtrl->SetZoom(CamCtrl->ZoomOrigin, 0.5f);
}

