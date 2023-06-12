#include "PrecompileHeader.h"
#include "YamadaState_Attack_WUPunch.h"

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"
#include "FieldCamController.h"

#include "YamadaFSM.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"



const std::string_view YamadaState_Attack_WUPunch::AniName = "Attack_WUPunch";
const std::string_view YamadaState_Attack_WUPunch::AniFileName = "Yamada_WUPunch.png";
const std::pair<int, int> YamadaState_Attack_WUPunch::AniCutFrame = std::pair<int, int>(5, 6);
const float YamadaState_Attack_WUPunch::AniInterTime = 0.08f;
const int YamadaState_Attack_WUPunch::Damage = 15;
const int YamadaState_Attack_WUPunch::AttackFrm = 17;

YamadaState_Attack_WUPunch::YamadaState_Attack_WUPunch()
{

}

YamadaState_Attack_WUPunch::~YamadaState_Attack_WUPunch()
{

}

void YamadaState_Attack_WUPunch::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	CreateOutLine();
	EnemyStateBase::SetUnbeatable();
}

void YamadaState_Attack_WUPunch::LoadAnimation()
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

void YamadaState_Attack_WUPunch::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 26,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, AttackFrm, true);
	Render->SetAnimationStartEvent(AniName, AttackFrm + 1, [this]()
	{
		FieldCamController* CamCtrl = this->GetCamCtrl();
		CamCtrl->SetZoom(CamCtrl->ZoomOrigin, 0.1f);
	});
}

void YamadaState_Attack_WUPunch::CreateOutLine()
{
	OutLineRender = GetEnemy()->CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	OutLineRender->GetShaderResHelper().SetConstantBufferLink("AtlasData", OutLineAtlas);
	OutLineRender->ColorOptionValue.MulColor = float4::Null;

	const float4 RenderScale = GetRenderer()->GetTransform()->GetLocalScale();
	GameEngineTransform* OutLineTrans = OutLineRender->GetTransform();
	OutLineTrans->SetLocalScale(RenderScale + float4::One * 20.f);
	OutLineTrans->AddLocalPosition(float4::Forward);

	OutLineRender->Off();
}




void YamadaState_Attack_WUPunch::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Right * 50.f, float4::One * 150.f);
	
	GetCamCtrl()->SetZoom(0.95f, AniInterTime * static_cast<float>(AttackFrm));
	OutLineRender->On();
}



void YamadaState_Attack_WUPunch::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	Update_OutLine();

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//공격을 적중 시킨 경우
	if (true == IsAttackHited)
	{
		GetFSM()->ChangeState(YamadaStateType::Taunt);
		return;
	}

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


void YamadaState_Attack_WUPunch::Update_OutLine()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();
	OutLineRender->SetTexture(EnemyRender->GetTexName());
	OutLineAtlas = EnemyRender->GetAtlasData();

	const float Duration = 1.f;
	float Ratio = GetLiveTime() / Duration;
	float4 NowColor = float4::LerpClamp(float4::Black, float4::Red, Ratio);
	OutLineRender->ColorOptionValue.MulColor = NowColor;
}




void YamadaState_Attack_WUPunch::Attack()
{
	if (true == IsAttackHited)
		return;
	
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack(true);
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
	IsAttackHited = true;
}

void YamadaState_Attack_WUPunch::ExitState()
{
	BossState_AttackBase::ExitState();

	FieldCamController* CamCtrl = this->GetCamCtrl();
	CamCtrl->SetZoom(CamCtrl->ZoomOrigin, 0.1f);
	IsAttackHited = false;
	OutLineRender->Off();
}