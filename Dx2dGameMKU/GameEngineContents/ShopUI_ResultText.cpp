#include "PrecompileHeader.h"
#include "ShopUI_ResultText.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGEnums.h"

ShopUI_ResultText* ShopUI_ResultText::GPtr = nullptr;

std::vector<std::string_view> ShopUI_ResultText::TexNames =
{
	"ShopUI_BuyOk.png",
	"ShopUI_MoneyLack.png",
	"ShopUI_InvenLack.png",
	"ShopUI_LevelLack.png",
	"ShopUI_SoldOut.png",
};

ShopUI_ResultText::ShopUI_ResultText()
{
	GPtr = this;
}

ShopUI_ResultText::~ShopUI_ResultText()
{

}



void ShopUI_ResultText::Start() 
{
	GameEngineActor::Start();
	TextRender = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::BuyResult);
	TextRender->Off();
}


void ShopUI_ResultText::TextOn(ShopResultType _Result)
{
	TextRender->SetScaleToTexture(TexNames[static_cast<size_t>(_Result)]);
	TextRender->On();
	ResetLiveTime();
}


void ShopUI_ResultText::LevelChangeStart()
{
	GameEngineActor::LevelChangeStart();
	GPtr = this;
}


void ShopUI_ResultText::Update(float _DeltaTime) 
{
	GameEngineActor::Update(_DeltaTime);

	if (false == TextRender->IsUpdate())
		return;

	static const float Duration = 1.f;
	static const float4 MaxOffset = float4{ 100.f, 200.f };

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);

	float4 NowOffset = float4::Lerp(float4::Zero, MaxOffset, ClampRatio);
	TextRender->GetTransform()->SetLocalPosition(NowOffset);
	TextRender->ColorOptionValue.MulColor.a = (1.f - ClampRatio);

	if (Ratio < 1.f)
		return;

	TextRender->Off();
}
