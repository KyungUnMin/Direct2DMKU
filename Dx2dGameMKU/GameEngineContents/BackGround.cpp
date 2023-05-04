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
	//GetTransform()->SetLocalPosition(float4::Forward * 500.f);
}


void BackGround::InitLevelArea(const float4& _Scale, const TileInfoData& _TileData)
{
	TileInfo = _TileData;
	MapScale = _Scale;

	TileRender = CreateComponent<GameEngineRenderer>();
	TileRender->SetPipeLine("Tile");
	TileRender->GetShaderResHelper().SetConstantBufferLink("TileInfo", TileInfo);

	TileRender->GetTransform()->SetLocalScale(_Scale);
	TileRender->GetTransform()->AddLocalPosition(float4::Back);
	TileRender->Off();
}




std::shared_ptr<GameEngineSpriteRenderer> BackGround::CreateBackImage(const std::string_view& _ResName, const float4& _Scale, const float4& _Offset /*= float4::Zero*/)
{
	std::shared_ptr<GameEngineSpriteRenderer> RendererPtr = CreateComponent<GameEngineSpriteRenderer>();
	RendererPtr->SetTexture(_ResName);
	GameEngineTransform* RenderTransform = RendererPtr->GetTransform();
	if (false == _Offset.IsZero())
	{
		float4 Offset = _Offset;
		if (0.f == Offset.z)
		{
			Offset.z = Offset.y;
		}
		RenderTransform->SetWorldPosition(Offset);
	}

	RenderTransform->SetLocalScale(_Scale);
	return RendererPtr;
}

void BackGround::CreateCollisionImage(const std::string_view& _ResName)
{
	ColRender = CreateComponent<GameEngineSpriteRenderer>();
	ColRender->SetScaleToTexture(_ResName);
	ColRender->GetTransform()->AddLocalPosition(float4::Back);
	ColRender->Off();
	
	ColTexture = GameEngineTexture::Find(_ResName);
}


bool BackGround::IsBlockPos(const float4& _Pos)
{
	if (nullptr == ColTexture)
	{
		MsgAssert("맵 픽셀 충돌할 텍스처를 설정해주지 않았습니다");
		return true;
	}

	float4 CheckPos = float4{ _Pos.x, -_Pos.y };
	CheckPos += MapScale.half();

	GameEnginePixelColor Pixel = ColTexture->GetPixel(CheckPos.ix(), CheckPos.iy());
	return (0 == Pixel.a);
}




void BackGround::Update(float _DeltaTime)
{
	if ((nullptr != TileRender) && (true == KeyMgr::IsDown(KeyNames::DebugF2)))
	{
		TileRender->IsUpdate() ? TileRender->Off() : TileRender->On();
	}

	if ((nullptr != ColTexture) && (true == KeyMgr::IsDown(KeyNames::DebugF3)))
	{
		ColRender->IsUpdate() ? ColRender->Off() : ColRender->On();
	}
}




