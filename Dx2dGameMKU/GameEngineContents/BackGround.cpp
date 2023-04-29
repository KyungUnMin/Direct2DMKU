#include "PrecompileHeader.h"
#include "BackGround.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"
#include "KeyMgr.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

void BackGround::Start()
{
	GetTransform()->SetLocalPosition(float4{ 0.f, 0.f, 500.f });
}

void BackGround::Update(float _DeltaTime)
{
	if (false == KeyMgr::IsDown(KeyNames::DebugF1))
		return;

	TileRender->IsUpdate() ? TileRender->Off() : TileRender->On();
}


void BackGround::AddBackImg(const std::string_view& _ResName, const float4& _Scale, const float4& _Offset /*= float4::Zero*/)
{
	std::shared_ptr<GameEngineSpriteRenderer> RendererPtr = CreateComponent<GameEngineSpriteRenderer>();
	RendererPtr->SetTexture(_ResName);
	if (false == _Offset.IsZero())
	{
		RendererPtr->GetTransform()->SetLocalPosition(_Offset);
	}
	
	TileRender = CreateComponent<GameEngineRenderer>();
	TileRender->SetPipeLine("Tile");
	TileRender->GetShaderResHelper().SetConstantBufferLink("TileInfo", TileInfo);

	RendererPtr->GetTransform()->SetLocalScale(_Scale);
	TileRender->GetTransform()->SetLocalScale(_Scale);
	TileRender->GetTransform()->AddLocalPosition(float4::Back * 10.f);
	TileRender->Off();
}



