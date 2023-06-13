#include "PrecompileHeader.h"
#include "YamadaState_Attack_Blast.h"


#include "DataMgr.h"

#include "YamadaFSM.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"

#include "YamadaBlastEffect.h"
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

	
	Render->SetAnimationStartEvent(AniName, 7, [this]()
	{
		CreateEffect<YamadaBlastEffect>()->Init(AniInterTime * 7.f, IsRightDir());
	});


	for (size_t i = 8; i < 14; ++i)
	{
		EnemyState_AttackBase::SetAttackCheckFrame(AniName, i);
	}
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

	Update_AfterEffect(_DeltaTime);
	
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	
	GetFSM()->ChangeState(YamadaStateType::Idle);
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
}

