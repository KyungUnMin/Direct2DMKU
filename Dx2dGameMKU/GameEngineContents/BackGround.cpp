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
	GetTransform()->SetLocalPosition(float4::Forward * 500.f);
}


void BackGround::InitLevelArea(const float4& _Scale, const TileInfoData& _TileData)
{
	TileInfo = _TileData;

	TileRender = CreateComponent<GameEngineRenderer>();
	TileRender->SetPipeLine("Tile");
	TileRender->GetShaderResHelper().SetConstantBufferLink("TileInfo", TileInfo);

	TileRender->GetTransform()->SetLocalScale(_Scale);
	TileRender->GetTransform()->AddLocalPosition(float4::Back);
	TileRender->Off();
}




void BackGround::CreateBackImage(const std::string_view& _ResName, const float4& _Scale, const float4& _Offset /*= float4::Zero*/)
{
	std::shared_ptr<GameEngineSpriteRenderer> RendererPtr = CreateComponent<GameEngineSpriteRenderer>();
	RendererPtr->SetTexture(_ResName);
	if (false == _Offset.IsZero())
	{
		RendererPtr->GetTransform()->SetLocalPosition(_Offset);
	}

	RendererPtr->GetTransform()->SetLocalScale(_Scale);
}




void BackGround::Update(float _DeltaTime)
{
	if (nullptr == TileRender)
		return;

	if (false == KeyMgr::IsDown(KeyNames::DebugF1))
		return;

	TileRender->IsUpdate() ? TileRender->Off() : TileRender->On();
}




