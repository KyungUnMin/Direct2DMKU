#include "PrecompileHeader.h"
#include "YamadaEnergyBall.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"

#include "LightEffect.h"
#include "AfterImageEffect.h"
#include "FieldPlayer.h"
#include "BackGround.h"

const std::string_view YamadaEnergyBall::Ball_FileName = "Yamada_EnergyBall.png";
const std::string_view YamadaEnergyBall::Ring_FileName = "Yamada_EnergyRing.png";
const std::string_view YamadaEnergyBall::Air_FileName = "Yamada_EnergyAir.png";
const float YamadaEnergyBall::AniInterTime = 0.08f;
const float4 YamadaEnergyBall::DarkPupple = float4{ 0.25f, 0.f, 0.6f, 0.5f };
const int YamadaEnergyBall::Damage = 5;

YamadaEnergyBall::YamadaEnergyBall()
{

}

YamadaEnergyBall::~YamadaEnergyBall()
{

}

void YamadaEnergyBall::Start() 
{
	FieldActorBase::Start();

	ImageLoad();
	CreateRenders();
	SettingCollider();
	CreateLight();
}

void YamadaEnergyBall::ImageLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	Dir.Move("EnemyAttack");
	Dir.Move("Yamada_EnergyBalls");
	
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Air_FileName).GetFullPath(), 4, 2);
	GameEngineTexture::Load(Dir.GetPlusFileName(Ball_FileName).GetFullPath());
	GameEngineTexture::Load(Dir.GetPlusFileName(Ring_FileName).GetFullPath());
}

void YamadaEnergyBall::CreateRenders()
{
	CreateRender_Air();
	CreateRender_Ball();
}

void YamadaEnergyBall::CreateRender_Air()
{
	AirRender = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	AirRender->CreateAnimation
	({
		.AnimationName = Air_FileName,
		.SpriteName = Air_FileName,
		.FrameInter = AniInterTime,
		.Loop = false,
		.ScaleToImage = true,
		});

	AirRender->ChangeAnimation(Air_FileName);
	AirRender->GetTransform()->SetLocalPosition(float4::Up * 100.f);
}

void YamadaEnergyBall::CreateRender_Ball() 
{
	std::shared_ptr<GameEngineSpriteRenderer> BallRender = GetRenderer();
	BallRender->SetScaleToTexture(Ball_FileName);
	BallRender->ColorOptionValue.MulColor = DarkPupple;

	RingRender = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	RingRender->SetScaleToTexture(Ring_FileName);
	
	GameEngineTransform* BallTrans = BallRender->GetTransform();
	GameEngineTransform* RingTrans = RingRender->GetTransform();
	RingTrans->SetParent(BallTrans);

	BallTrans->SetLocalPosition(float4::Up * 100.f);
	BallRender->Off();
}


void YamadaEnergyBall::SettingCollider()
{
	FieldActorBase::CreateCollider(CollisionOrder::EnemyAttack);

	std::shared_ptr<GameEngineCollision> Collider = GetAttackCollider();
	GameEngineTransform* ColTrans = Collider->GetTransform();
	ColTrans->SetLocalScale(float4::One * 100.f);
	Collider->Off();
}

void YamadaEnergyBall::CreateLight()
{
	std::shared_ptr<LightEffect> Light = nullptr;
	Light = GetLevel()->CreateActor<LightEffect>(UpdateOrder::Effect);
	GameEngineTransform* LightTrans = Light->GetTransform();
	LightTrans->SetParent(GetTransform());
	LightTrans->SetLocalPosition(float4::Up * 100.f);

	Light->Flicker(DarkPupple);
}



void YamadaEnergyBall::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);



	switch (CurState)
	{
	case YamadaEnergyBall::State::Create:
		Update_Create(_DeltaTime);
		break;
	case YamadaEnergyBall::State::Rot:
		Update_Rot(_DeltaTime);
		Update_CheckCol();
		Update_Shadow();
		break;
	case YamadaEnergyBall::State::Destory:
		Update_Destory(_DeltaTime);
		break;
	}
}

void YamadaEnergyBall::Update_Create(float _DeltaTime)
{
	if (false == AirRender->IsAnimationEnd())
		return;

	std::shared_ptr<GameEngineSpriteRenderer> BallRender = GetRenderer();
	std::shared_ptr<GameEngineCollision> Collider = GetAttackCollider();

	AirRender->Off();
	BallRender->On();
	Collider->On();
	CurState = State::Rot;
}

void YamadaEnergyBall::Update_Rot(float _DeltaTime)
{
	//∏µ »∏¿¸
	static const float4 RotSpeed = float4{ 0.f, 0.f ,-1080.f };
	GameEngineTransform* RingTrans = RingRender->GetTransform();
	RingTrans->AddLocalRotation(RotSpeed * _DeltaTime);

	//¿‹ªÛ
	AfterImgTimer += _DeltaTime;
	if (AfterImgTimer < AfterImgTime)
		return;

	AfterImgTimer = 0.f;
	std::shared_ptr<AfterImageEffect> AfterImg = nullptr;
	AfterImg = GetLevel()->CreateActor<AfterImageEffect>(UpdateOrder::Effect);
	std::shared_ptr<GameEngineSpriteRenderer> BallRender = GetRenderer();
	AfterImg->Init(BallRender);
	AfterImg->SetPlusColor(DarkPupple);
}

void YamadaEnergyBall::Update_CheckCol()
{
	float LiveTime = GetLiveTime();
	if (LiveTime < LastAttackTime + 0.1f)
		return;

	LastAttackTime = LiveTime;

	std::shared_ptr<GameEngineCollision> PlayerCol = nullptr;
	std::shared_ptr<GameEngineCollision> Collider = GetAttackCollider();

	PlayerCol = Collider->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D);
	if (nullptr == PlayerCol)
		return;

	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	bool Result = Player->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}

void YamadaEnergyBall::Update_Shadow()
{
	float4 ThisPos = GetTransform()->GetWorldPosition();

	if (true == GetBackGround()->IsBlockPos(ThisPos))
	{
		GetShadowRender()->Off();
	}
	else
	{
		GetShadowRender()->On();
	}
}


void YamadaEnergyBall::DestroyBall()
{
	AirRender->On();

	if (State::Create != CurState)
	{
		AirRender->ChangeAnimation(Air_FileName);
	}

	std::shared_ptr<GameEngineSpriteRenderer> BallRender = GetRenderer();
	std::shared_ptr<GameEngineCollision> Collider = GetAttackCollider();

	BallRender->Off();
	Collider->Off();
	GetShadowRender()->Off();
	CurState = State::Destory;
}

void YamadaEnergyBall::Update_Destory(float _DeltaTime) 
{
	if (false == AirRender->IsAnimationEnd())
		return;

	Death();
}


