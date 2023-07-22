#include "PrecompileHeader.h"
#include "YamadaState_Attack_QuickCombo.h"

#include "DataMgr.h"
#include "FieldCamController.h"
#include "SoundMgr.h"

#include "YamadaFSM.h"
#include "FieldPlayer.h"
#include "HitEffect.h"
#include "FieldEnemyBase.h"

const std::string_view YamadaState_Attack_QuickCombo::AniName = "Attack_QuickCombo";
const std::string_view YamadaState_Attack_QuickCombo::AniFileName = "Yamada_QuickCombo.png";
const std::pair<int, int> YamadaState_Attack_QuickCombo::AniCutFrame = std::pair<int, int>(5, 5);
const float YamadaState_Attack_QuickCombo::AniInterTime = 0.06f;
const int YamadaState_Attack_QuickCombo::Damage = 5;
const float4 YamadaState_Attack_QuickCombo::EffectScale = { 200.f ,200.f, 1.f };

const std::string_view YamadaState_Attack_QuickCombo::EffectName = "Yamada_QuickCombo_Effect.png";

YamadaState_Attack_QuickCombo::YamadaState_Attack_QuickCombo()
{

}

YamadaState_Attack_QuickCombo::~YamadaState_Attack_QuickCombo()
{
	
}

void YamadaState_Attack_QuickCombo::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	CreateAttackEffect();
	EnemyStateBase::SetSight(80.f);
}

void YamadaState_Attack_QuickCombo::LoadAnimation()
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(EffectName).GetFullPath(), 4, 2);
}

void YamadaState_Attack_QuickCombo::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	const std::vector<size_t> SfxFrm = { 3, 8, 17 };
	const std::vector<size_t> AttackFrm = { 4, 9, 18 };


	for (size_t i = 0; i < SfxFrm.size(); ++i)
	{
		Render->SetAnimationStartEvent(AniName, SfxFrm[i], []()
		{
			SoundMgr::PlaySFX("Enemy_CommonAttack.wav");
		});
	}

	for (size_t i = 0; i < AttackFrm.size(); ++i)
	{
		EnemyState_AttackBase::SetAttackCheckFrame(AniName, AttackFrm[i]);
	}

	Render->SetAnimationStartEvent(AniName, 19, [this]()
	{
		Effect->On();
		Effect->ChangeAnimation(EffectName);
	});
}

void YamadaState_Attack_QuickCombo::CreateAttackEffect()
{
	Effect = GetEnemy()->CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Effect->CreateAnimation
	({
		.AnimationName = EffectName,
		.SpriteName = EffectName,
		.FrameInter = 0.05f,
		.Loop = false,
	});

	GameEngineTransform* EffectTrans = Effect->GetTransform();
	EffectTrans->SetLocalScale(EffectScale);
	EffectTrans->SetLocalNegativeScaleX();
	EffectTrans->SetLocalPosition({30.f, EffectScale.hy(), -10.f });
	Effect->Off();
}


void YamadaState_Attack_QuickCombo::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 200.f);
}





void YamadaState_Attack_QuickCombo::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);


	if (false == GetRenderer()->IsAnimationEnd())
		return;



	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(YamadaStateType::TeleportDisappear);
		return;
	}

	//일정 범위 안에 있다면 공격
	GetFSM()->ChangeState(YamadaStateType::Blast);
}



void YamadaState_Attack_QuickCombo::Attack()
{
	size_t CurFrm = GetRenderer()->GetCurrentFrame();
	bool Result = false;

	if (4 == CurFrm)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Jaw(Damage);
	}
	else if (9 == CurFrm)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Face(Damage);
	}
	else if (18 == CurFrm)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Stun(Damage);
	}
	else
	{
		MsgAssert("해당 프레임에서는 공격하지 않습니다");
		return;
	}
}



void YamadaState_Attack_QuickCombo::ExitState()
{
	BossState_AttackBase::ExitState();
	Effect->Off();
}