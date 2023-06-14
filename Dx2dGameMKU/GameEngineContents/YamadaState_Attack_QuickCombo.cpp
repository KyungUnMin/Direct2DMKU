#include "PrecompileHeader.h"
#include "YamadaState_Attack_QuickCombo.h"

#include "DataMgr.h"
#include "FieldCamController.h"

#include "YamadaFSM.h"
#include "FieldPlayer.h"
#include "HitEffect.h"

const std::string_view YamadaState_Attack_QuickCombo::AniName = "Attack_QuickCombo";
const std::string_view YamadaState_Attack_QuickCombo::AniFileName = "Yamada_QuickCombo.png";
const std::pair<int, int> YamadaState_Attack_QuickCombo::AniCutFrame = std::pair<int, int>(5, 5);
const float YamadaState_Attack_QuickCombo::AniInterTime = 0.06f;
const int YamadaState_Attack_QuickCombo::Damage = 5;

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

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 4);
	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 9);
	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 18);
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


	GetFSM()->ChangeState(YamadaStateType::TeleportDisappear);


	////일정 범위 밖에 있다면 idle
	//if (GetSightRadius() < GetVecToPlayer().Size())
	//{
	//	GetFSM()->ChangeState(YamadaStateType::Idle);
	//	return;
	//}

	////일정 범위 안에 있다면 공격
	//GetFSM()->ChangeState(YamadaStateType::Blast);
}



void YamadaState_Attack_QuickCombo::Attack()
{
	size_t CurFrm = GetRenderer()->GetCurrentFrame();
	bool Result = false;

	if (4 == CurFrm)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Jaw();
	}
	else if (9 == CurFrm)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Face();
	}
	else if (18 == CurFrm)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Stun();
	}
	else
	{
		MsgAssert("해당 프레임에서는 공격하지 않습니다");
		return;
	}
	
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}


void YamadaState_Attack_QuickCombo::ExitState()
{
	BossState_AttackBase::ExitState();
}