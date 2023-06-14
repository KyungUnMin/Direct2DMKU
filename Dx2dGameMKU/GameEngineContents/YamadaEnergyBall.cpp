#include "PrecompileHeader.h"
#include "YamadaEnergyBall.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

#include "LightEffect.h"

const std::string_view YamadaEnergyBall::Ball_FileName = "Yamada_EnergyBall.png";
const std::string_view YamadaEnergyBall::Ring_FileName = "Yamada_EnergyRing.png";
const std::string_view YamadaEnergyBall::Air_FileName = "Yamada_EnergyAir.png";
const float YamadaEnergyBall::AniInterTime = 0.08f;
const float4 YamadaEnergyBall::DarkPupple = float4{ 0.25f, 0.f, 0.6f, 0.5f };

YamadaEnergyBall::YamadaEnergyBall()
{

}

YamadaEnergyBall::~YamadaEnergyBall()
{

}

void YamadaEnergyBall::Start() 
{
	GameEngineActor::Start();

	ImageLoad();
	CreateRenders();
	CreateCollider();
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
	BallRender = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
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

void YamadaEnergyBall::CreateCollider()
{
	Collider = CreateComponent<GameEngineCollision>(CollisionOrder::EnemyAttack);
	Collider->GetTransform()->SetLocalScale(float4::One * 100.f);
	Collider->Off();
}



void YamadaEnergyBall::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	switch (CurState)
	{
	case YamadaEnergyBall::State::Create:
		Update_Create(_DeltaTime);
		break;
	case YamadaEnergyBall::State::Rot:
		Update_Rot(_DeltaTime);
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

	AirRender->Off();
	BallRender->On();
	Collider->On();
	CurState = State::Rot;
}

void YamadaEnergyBall::Update_Rot(float _DeltaTime)
{
	static const float4 RotSpeed = float4{ 0.f, 0.f ,1080.f };
	GameEngineTransform* RingTrans = RingRender->GetTransform();
	RingTrans->AddLocalRotation(RotSpeed * _DeltaTime);

	//AfterEffect Todo
}

void YamadaEnergyBall::Update_Destory(float _DeltaTime) 
{

}
