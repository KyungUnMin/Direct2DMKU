#include "PrecompileHeader.h"
#include "AfterImageEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGEnums.h"

AfterImageEffect::AfterImageEffect()
{

}

AfterImageEffect::~AfterImageEffect()
{

}




void AfterImageEffect::Init(std::shared_ptr<GameEngineSpriteRenderer> _OwnerRender)
{
	//렌더 생성
	EffectRender = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	EffectRender->GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);

	//텍스처 세팅
	EffectRender->SetTexture(_OwnerRender->GetTexName());
	AtlasData = _OwnerRender->GetAtlasData();

	GameEngineTransform* OwnerRenderTrans = _OwnerRender->GetTransform();
	GameEngineTransform* EffectTrans = GetTransform();

	EffectTrans->SetWorldPosition(OwnerRenderTrans->GetWorldPosition() + float4::Forward);
	EffectTrans->SetLocalScale(OwnerRenderTrans->GetLocalScale());
}


void AfterImageEffect::Update(float _DeltaTime)
{
	if (nullptr == EffectRender)
	{
		MsgAssert("Init 함수를 호출해주지 않았습니다");
		return;
	}

	GameEngineActor::Update(_DeltaTime);

	float Ratio = (GetLiveTime() / Duration);
	if (1.f < Ratio)
	{
		Death();
		return;
	}
	
	float4 MulColor = float4::One;
	MulColor.a = (1.f - Ratio) * AlphaRatio;
	EffectRender->ColorOptionValue.MulColor = MulColor;
}
