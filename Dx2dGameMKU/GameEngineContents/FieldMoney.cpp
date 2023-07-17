#include "PrecompileHeader.h"
#include "FieldMoney.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "DataMgr.h"
#include "SoundMgr.h"
#include "RCGDefine.h"
#include "RCGEnums.h"

const std::vector<FieldMoney::MoneyInfo> FieldMoney::MoneyInfoes =
{
	MoneyInfo{"FieldMoney_Coin.png",		1,		13	},
	MoneyInfo{"FieldMoney_Blue.png",		10,	11	},
	MoneyInfo{"FieldMoney_Green.png",	100,	11	},
	MoneyInfo{"FieldMoney_Pupple.png",	500,	11	},
};

const float FieldMoney::ShadowOffsetRange = 15.f;

const std::vector<float> FieldMoney::BillShadowOffsetX =
{
	ShadowOffsetRange * 0.f,		ShadowOffsetRange * 1.f,		ShadowOffsetRange  * 	2.f,	ShadowOffsetRange  *	3.f,
	ShadowOffsetRange * 2.f,		ShadowOffsetRange * 1.f,		ShadowOffsetRange  * 0.f,		ShadowOffsetRange  * -1.f,
	ShadowOffsetRange * -2.f,	ShadowOffsetRange * -3.f,	ShadowOffsetRange  * -2.f,	ShadowOffsetRange  * -1.f,
};

const float FieldMoney::ShadowOffetY = -10.f;

const float FieldMoney::MaxLiveTime = 10.f;

FieldMoney::FieldMoney()
{
	
}

FieldMoney::~FieldMoney()
{

}


void FieldMoney::Start()
{
	GameEngineActor::Start();

	LoadImageRes();
	CreateCollision();
	CreateShadow();
}


void FieldMoney::LoadImageRes()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Money");

	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineSprite::LoadSheet(File.GetFullPath(), 4, 4);
	}

	IsLoad = true;
}

void FieldMoney::CreateCollision()
{
	static const float4 ColScale = float4{ 30.f, 30.f, 1.f };

	Collider = CreateComponent<GameEngineCollision>(CollisionOrder::FieldItem);
	Collider->GetTransform()->SetLocalScale(ColScale);
}

void FieldMoney::CreateShadow()
{
	const float4 ShadowScale = float4{ 32.f, 8.f, 1.f };

	Shadow = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Shadow->SetTexture("FieldCharShadow.png");

	GameEngineTransform* ShadowTrans = Shadow->GetTransform();
	ShadowTrans->SetLocalScale(ShadowScale);
	ShadowTrans->SetLocalPosition(float4::Up * ShadowOffetY);
}




void FieldMoney::Init(MoneyType _Type)
{
	Type = _Type;

	if (MoneyType::UNKNOWN == Type)
	{
		MsgAssert("UNKNOWN 타입의 Money는 존재하지 않습니다");
		return;
	}

	if (MoneyType::Coin == Type)
	{
		SoundMgr::PlaySFX("FieldMoney_Coin_Create.mp3");
	}
	else
	{
		SoundMgr::PlaySFX("FieldMoney_Bill_Create.wav");
	}

	CreateRender();
	CreateOutLine();
}


void FieldMoney::CreateRender() 
{
	static const float4 RenderScale = float4{ 128.f, 128.f, 1.f };

	Render = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Render->GetTransform()->SetLocalScale(RenderScale);

	const MoneyInfo& Info = MoneyInfoes[static_cast<size_t>(Type)];

	Render->CreateAnimation
	({
		.AnimationName = Info.SpriteName,
		.SpriteName = Info.SpriteName,
		.Start = 0,
		.End = Info.EndFrm,
		.Loop = true,
	});

	Render->ChangeAnimation(Info.SpriteName);

	if (MoneyType::Coin == Type)
		return;
	
	for (size_t i = 0; i < BillShadowOffsetX.size(); ++i)
	{
		Render->SetAnimationStartEvent(Info.SpriteName, i, [this]()
		{
			size_t CurFrm = Render->GetCurrentFrame();
			const float4 ShadowOffset = float4{ BillShadowOffsetX[CurFrm],  ShadowOffetY };
			Shadow->GetTransform()->SetLocalPosition(ShadowOffset);
		});
	}
}



void FieldMoney::CreateOutLine()
{
	OutLine = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	OutLine->GetShaderResHelper().SetConstantBufferLink("AtlasData", OutLineAtlas);

	const float4 LocalScale = { 1.08f, 1.08f, 1.f };

	GameEngineTransform* OutLineTrans = OutLine->GetTransform();
	OutLineTrans->SetParent(Render->GetTransform(), false);
	OutLineTrans->SetLocalScale(LocalScale);
	OutLineTrans->SetLocalPosition(float4::Forward);
	
	OutLine->Off();
}



void FieldMoney::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	if (MoneyType::UNKNOWN == Type)
	{
		MsgAssert("FieldMoney의 Init함수를 호출시켜주지 않았습니다");
		return;
	}

	if (MaxLiveTime < GetLiveTime())
	{
		Death();
		return;
	}


	if (false == IsLand)
	{
		if (MoneyType::Coin == Type)
		{
			Update_Coin(_DeltaTime);
		}
		else
		{
			Update_Bill(_DeltaTime);
		}
	}
	else
	{
		if (MoneyType::Coin != Type)
		{
			size_t CurFrm = Render->GetCurrentFrame();
			if (0 == CurFrm || 6 == CurFrm)
			{
				Render->SetAnimPauseOn();
			}
		}

		Update_Collision();
		Update_OutLine(_DeltaTime);
	}
}



void FieldMoney::Update_Coin(float _DeltaTime)
{
	static const float MaxHeight = 150.f;
	static const float Duration = 0.5f;

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * ClampRatio);

	Render->GetTransform()->SetLocalPosition(float4::Up * SinValue * MaxHeight);

	if (Ratio < 1.f)
		return;

	IsLand = true;
}

void FieldMoney::Update_Bill(float _DeltaTime) 
{
	static const float MaxHeight = 100.f;
	static const float Duration = 1.5f;

	float Ratio = GetLiveTime() / Duration;
	Ratio = std::clamp(Ratio, 0.f, 1.f);
	float CosValue = cosf(GameEngineMath::PIE * Ratio * 0.5f);

	Render->GetTransform()->SetLocalPosition(float4::Up * CosValue * MaxHeight);

	if (Ratio < 1.f)
		return;

	IsLand = true;
}

void FieldMoney::Update_OutLine(float _DeltaTime)
{
	OutLine->On();
	OutLine->SetTexture(Render->GetTexName());
	OutLineAtlas = Render->GetAtlasData();
	
	float LiveTime = GetLiveTime();
	float SinValue = abs(sinf(LiveTime));
	float CosValue = abs(cosf(LiveTime));

	float4 Color = float4::Null;
	Color.r = SinValue;
	Color.g = SinValue;
	Color.b = CosValue;

	OutLine->ColorOptionValue.MulColor = float4{ 0.f, 0.f, 0.f, 1.0f };
	OutLine->ColorOptionValue.PlusColor = Color;
}

void FieldMoney::Update_Collision()
{
	if (nullptr == Collider->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D))
		return;


	DataMgr::PlusPlayerMoney(MoneyInfoes[static_cast<size_t>(Type)].Value);

	if (MoneyType::Coin == Type)
	{
		SoundMgr::PlaySFX("FieldMoney_Coin_Pick.wav");
	}
	else
	{
		SoundMgr::PlaySFX("FieldMoney_Bill_Pick.wav");
	}

	Death();
}