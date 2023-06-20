#include "PrecompileHeader.h"
#include "NoiseAxe.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"

#include "FieldPlayer.h"
#include "FieldLevelBase.h"
#include "BackGround.h"

const std::string_view NoiseAxe::AniFileName = "Noise_AxeGrind.png";
const int NoiseAxe::Damage = 10;

NoiseAxe::NoiseAxe()
{

}

NoiseAxe::~NoiseAxe()
{

}

void NoiseAxe::Start()
{
	FieldActorBase::Start();

	ImageLoad();
	SettingRender();
	FieldActorBase::CreateCollider(CollisionOrder::EnemyAttack);
	FieldActorBase::SetShadowScale(1.5f);

	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
}


void NoiseAxe::ImageLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	Dir.Move("EnemyAttack");
	Dir.Move("Noise_Axe");

	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), 5, 2);
}

void NoiseAxe::SettingRender()
{
	const float4 RenderScale = float4{ 500.f, 500.f, 1.f };
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniFileName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 7,
		.FrameInter = 0.01f,
		.Loop = true,
	});

	Render->ChangeAnimation(AniFileName);

	GameEngineTransform* RenderTrans = Render->GetTransform();
	RenderTrans->SetLocalScale(RenderScale);
	RenderTrans->SetLocalPosition(float4::Up * 100.f);
}



void NoiseAxe::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);

	if (0.f == MoveDuration && 0.f == StayDuration)
	{
		MsgAssert("Init 함수를 호출시켜주어야 합니다");
		return;
	}

	switch (CurState)
	{
	case NoiseAxe::State::Launch:
		Update_Launch(_DeltaTime);
		break;
	case NoiseAxe::State::Stay:
		Update_Stay(_DeltaTime);
		break;
	case NoiseAxe::State::ComeBack:
		Update_ComeBack(_DeltaTime);
		break;
	}

	AttackTimer += _DeltaTime;
	if (AttackTimer < 0.1f)
		return;

	if (nullptr == GetAttackCollider()->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D))
		return;

	AttackTimer = 0.f;

	if (false == FieldPlayer::GetPtr()->OnDamage_BlowBack())
		return;

	DataMgr::MinusPlayerHP(Damage);
}

void NoiseAxe::Update_Launch(float _DeltaTime) 
{
	float Ratio = GetLiveTime() / MoveDuration;
	if (1.f < Ratio)
	{
		ResetLiveTime();
		CurState = State::Stay;
		return;
	}

	float SinValue = sinf(GameEngineMath::PIE * 0.5f * Ratio);
	float4 NextPos = float4::LerpClamp(StartPos, DestPos, SinValue);
	if (true == BGPtr->IsBlockPos(NextPos))
		return;

	GetTransform()->SetWorldPosition(NextPos);
}

void NoiseAxe::Update_Stay(float _DeltaTime)
{
	if (GetLiveTime() < StayDuration)
		return;

	ResetLiveTime();
	CurState = State::ComeBack;
}

void NoiseAxe::Update_ComeBack(float _DeltaTime)
{
	float Ratio = GetLiveTime() / MoveDuration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * 0.5f * ClampRatio);

	float4 NextPos = float4::LerpClamp(DestPos, StartPos, SinValue);
	if (true == BGPtr->IsBlockPos(NextPos))
		return;

	GetTransform()->SetWorldPosition(NextPos);

	if (Ratio < 1.f)
		return;

	Death();
}