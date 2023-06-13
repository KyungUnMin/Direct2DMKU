#include "PrecompileHeader.h"
#include "YamadaBlastEffect.h"

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
	{"Yamada_Blast_Spark.png"			, 1,	8,		float4{},	float4{}},
};

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

	Renders[RenderNames::EnergyBall]->SetTexture(ImageInfo[RenderNames::EnergyBall].Name);
	Renders[RenderNames::EnergyRing]->SetTexture(ImageInfo[RenderNames::EnergyRing].Name);

	//보라색
	Renders[RenderNames::EnergyBall]->ColorOptionValue.MulColor = float4{ 0.25f, 0.f, 0.6f, 0.5f };

	Renders[RenderNames::EnergyBall]->On();
	Renders[RenderNames::EnergyRing]->On();
}





void YamadaBlastEffect::Init(float _Duration, bool _IsDirRight)
{
	Duration = _Duration;
	
	//왼쪽을 바라보고 있을때만
	if (true == _IsDirRight)
		return;

	GetTransform()->SetLocalNegativeScaleX();
}


void YamadaBlastEffect::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	if (Duration <= 0.f)
	{
		MsgAssert("YamadaBlastEffect를 사용하기 위해서는 Init함수를 호출해주어야 합니다");
		return;
	}


	if (Duration < GetLiveTime())
	{
		Death();
		return;
	}
	
	static const float4 RotSpeed = float4::Forward * 1080.f;
	GameEngineTransform* EnergeyRingTrans = Renders[RenderNames::EnergyRing]->GetTransform();
	EnergeyRingTrans->AddLocalRotation(RotSpeed * _DeltaTime);
}