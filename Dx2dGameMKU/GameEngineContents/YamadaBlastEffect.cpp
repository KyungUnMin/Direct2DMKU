#include "PrecompileHeader.h"
#include "YamadaBlastEffect.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

const std::vector<YamadaBlastEffect::RenderInfo> YamadaBlastEffect::ImageInfo =
{
	{"Yamada_Blast_DustBack.png"		, 4,	2,		float4{},	float4{}},
	{"Yamada_Blast_DustFront.png"	, 4,	4,		float4{},	float4{}},
	{"Yamada_Blast_EndRing.png"		, 4,	2,		float4{},	float4{}},
	{"Yamada_Blast_EnergyBall.png"	, 0,	0,		float4{150.f, 100.f,	0.f},		float4{128.f, 128.f , 1.f}},
	{"Yamada_Blast_EnergyRing.png"	, 0,	0,		float4{150.f, 100.f, -1.f},	float4{128.f, 128.f , 1.f}},
	{"Yamada_Blast_Spark.png"			, 1,	8,		float4{150.f, 100.f, -2.f},	float4{-256.f, 64.f, 1.f}},
};

const float4 YamadaBlastEffect::DarkPupple = { 0.25f, 0.f, 0.6f, 0.5f };

YamadaBlastEffect::YamadaBlastEffect()
{

}

YamadaBlastEffect::~YamadaBlastEffect()
{

}




void YamadaBlastEffect::Start()
{
	GameEngineActor::Start();

	ImageLoad();
	CreateRenders();
}



void YamadaBlastEffect::ImageLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	Dir.Move("EnemyAttack");
	Dir.Move("Yamada_Blast");

	for (size_t i = 0; i < RenderNames::COUNT; ++i)
	{
		const std::string& FullPath = Dir.GetPlusFileName(ImageInfo[i].Name).GetFullPath();

		if ((RenderNames::EnergyBall == i) || (RenderNames::EnergyRing == i))
		{
			GameEngineTexture::Load(FullPath);
			continue;
		}

		GameEngineSprite::LoadSheet(FullPath, ImageInfo[i].CurX, ImageInfo[i].CurY);
	}
}




void YamadaBlastEffect::CreateRenders()
{
	Renders.resize(RenderNames::COUNT, nullptr);
	for (size_t i = 0; i < Renders.size(); ++i)
	{
		Renders[i] = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
		Renders[i]->Off();

		GameEngineTransform* RenderTrans = Renders[i]->GetTransform();
		RenderTrans->SetLocalPosition(ImageInfo[i].Offset);
		RenderTrans->SetLocalScale(ImageInfo[i].Scale);
	}

	SetEnergyRender();
	SetSparkRender();
}

void YamadaBlastEffect::SetEnergyRender()
{
	Renders[RenderNames::EnergyBall]->SetTexture(ImageInfo[RenderNames::EnergyBall].Name);
	Renders[RenderNames::EnergyRing]->SetTexture(ImageInfo[RenderNames::EnergyRing].Name);

	//보라색
	Renders[RenderNames::EnergyBall]->ColorOptionValue.MulColor = DarkPupple;
}

void YamadaBlastEffect::SetSparkRender()
{
	const std::string_view& Name = ImageInfo[RenderNames::Spark].Name;
	Renders[RenderNames::Spark]->CreateAnimation
	({
		.AnimationName = Name,
		.SpriteName = Name,
	});

	Renders[RenderNames::Spark]->ChangeAnimation(Name);

	Renders[RenderNames::Spark]->ColorOptionValue.MulColor = DarkPupple;
}





void YamadaBlastEffect::Init(float _Duration, bool _IsDirRight)
{
	Duration = _Duration;
	
	//왼쪽을 바라보고 있을때만
	if (false == _IsDirRight)
	{
		GetTransform()->SetLocalNegativeScaleX();
	}

	//Renders[RenderNames::EnergyBall]->On();
	//Renders[RenderNames::EnergyRing]->On();
	Renders[RenderNames::Spark]->On();
}


void YamadaBlastEffect::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	if (Duration <= 0.f)
	{
		MsgAssert("YamadaBlastEffect를 사용하기 위해서는 Init함수를 호출해주어야 합니다");
		return;
	}

	switch (CurState)
	{
	case YamadaBlastEffect::State::OnAttack:
		Update_OnAttack(_DeltaTime);
		Update_Spark();
		break;
	case YamadaBlastEffect::State::Extinct:
		Update_Extinct(_DeltaTime);
		break;
	}
	
}

void YamadaBlastEffect::Update_OnAttack(float _DeltaTime)
{
	if (Duration < GetLiveTime())
	{
		CurState = State::Extinct;
		return;
	}

	static const float4 RotSpeed = float4::Forward * 1080.f;
	GameEngineTransform* EnergeyRingTrans = Renders[RenderNames::EnergyRing]->GetTransform();
	EnergeyRingTrans->AddLocalRotation(RotSpeed * _DeltaTime);
}

void YamadaBlastEffect::Update_Spark()
{
	const float OffsetY = 25.f;
	float NowOffsetY = GameEngineRandom::MainRandom.RandomFloat(-OffsetY, OffsetY);

	GameEngineTransform* SparkTrans = Renders[RenderNames::Spark]->GetTransform();
	const float4& OriginOffset = ImageInfo[RenderNames::Spark].Offset;
	SparkTrans->SetLocalPosition(OriginOffset + (float4::Up * NowOffsetY));

	/*float NowAngle = GameEngineRandom::MainRandom.RandomFloat(-10.f, 10.f);
	GameEngineTransform* SparkTrans = Renders[RenderNames::Spark]->GetTransform();
	SparkTrans->SetLocalRotation(float4::Forward * NowAngle);*/
}

void YamadaBlastEffect::Update_Extinct(float _DeltaTime) 
{
	Death();
}