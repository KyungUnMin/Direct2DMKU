#include "PrecompileHeader.h"
#include "YamadaState_Attack_MatterCrush.h"

#include "SoundMgr.h"

#include "YamadaFSM.h"
#include "YamadaMatterBlock.h"
#include "FieldLevelBase.h"
#include "FieldPlayer.h"
#include "AfterImageEffect.h"

const std::string_view YamadaState_Attack_MatterCrush::AniName = "Attack_MatterCrusher";
const std::string_view YamadaState_Attack_MatterCrush::AniFileName = "Yamada_MatterCrusher.png";
const std::pair<int, int> YamadaState_Attack_MatterCrush::AniCutFrame = std::pair<int, int>(5, 4);
const float YamadaState_Attack_MatterCrush::AniInterTime = 0.08f;

YamadaState_Attack_MatterCrush::YamadaState_Attack_MatterCrush()
{

}

YamadaState_Attack_MatterCrush::~YamadaState_Attack_MatterCrush()
{

}

void YamadaState_Attack_MatterCrush::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();

	//슈퍼아머
	SetUnbeatable();
}

void YamadaState_Attack_MatterCrush::LoadAnimation()
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

void YamadaState_Attack_MatterCrush::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 17,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}




void YamadaState_Attack_MatterCrush::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	CreateBlocks();

	SoundMgr::PlaySFX("Yamada_MatterCrush_Voice.wav");
}

void YamadaState_Attack_MatterCrush::CreateBlocks()
{
	GameEngineTransform* PlayerTrans = FieldPlayer::GetPtr()->GetTransform();
	float4 PlayerPos = PlayerTrans->GetWorldPosition();

	std::shared_ptr<FieldLevelBase> Level = FieldLevelBase::GetPtr();
	GameEngineTransform* BlockTrans = nullptr;

	BlockTrans = Level->CreateActor<YamadaMatterBlock>(UpdateOrder::Effect)->GetTransform();
	BlockTrans->SetWorldPosition(PlayerPos);

	BlockTrans = Level->CreateActor<YamadaMatterBlock>(UpdateOrder::Effect)->GetTransform();
	BlockTrans->SetWorldPosition(PlayerPos);
	BlockTrans->SetLocalNegativeScaleX();
}



void YamadaState_Attack_MatterCrush::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	Update_AfterEffect(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//임시
	GetFSM()->ChangeState(YamadaStateType::TeleportDisappear);
	return;

	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(YamadaStateType::Idle);
		return;
	}

	GetFSM()->ChangeState(YamadaStateType::Idle);
}


void YamadaState_Attack_MatterCrush::Update_AfterEffect(float _DeltaTime)
{
	AfterEffectTimer += _DeltaTime;
	if (AfterEffectTimer < 0.05f)
		return;

	AfterEffectTimer = 0.f;

	std::shared_ptr<AfterImageEffect> Effect = nullptr;
	Effect = CreateEffect<AfterImageEffect>();
	Effect->Init(GetRenderer());
	Effect->SetPlusColor(float4::Red);
}


