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
	if ((0 == _TileData.XCount) || (0 == _TileData.YCount))
	{
		MsgAssert("그리드의 가로 및 세로의 갯수가 0일수는 없습니다");
		return;
	}
	
	TileInfo = _TileData;
	MapScale = _Scale;
	GridScale = float4{ MapScale.x / static_cast<float>(TileInfo.XCount), MapScale.y / static_cast<float>(TileInfo.YCount) };

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

		if (DeepMostZ < Offset.z)
		{
			DeepMostZ = Offset.z;
		}
	}

	RenderTransform->SetLocalScale(_Scale);
	return RendererPtr;
}

void BackGround::CreateCollisionImage(const std::string_view& _ResName)
{
	ColRender = CreateComponent<GameEngineSpriteRenderer>();
	ColRender->SetScaleToTexture(_ResName);
	ColRender->GetTransform()->AddLocalPosition(float4::Forward * DeepMostZ + float4::Back);
	ColRender->Off();
	
	ColTexture = GameEngineTexture::Find(_ResName);
}


bool BackGround::IsBlockPos(const float4& _Pos) const
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


const float4& BackGround::GetPosFromGrid(int _X, int _Y) const
{
	static float4 WinPos = float4::Zero;
	WinPos.x = GridScale.x * static_cast<float>(_X);
	WinPos.y = GridScale.y * static_cast<float>(_Y);
	WinPos += GridScale.half();

	static float4 FieldPos = float4::Zero;
	FieldPos = WinPos - MapScale.half();
	FieldPos.y *= -1.f;
	return FieldPos;
}



const std::pair<int, int> BackGround::GetGridFromPos(const float4& _Pos) const
{
	float4 WinPos = float4{ _Pos.x, -_Pos.y };
	WinPos += MapScale.half();

	std::pair<int, int> ReturnValue;

	ReturnValue.first = static_cast<int>(WinPos.x / GridScale.x);
	ReturnValue.second = static_cast<int>(WinPos.y / GridScale.y);

	return ReturnValue;
}




void BackGround::Update(float _DeltaTime)
{
	if ((nullptr != TileRender) && (true == KeyMgr::IsDown(KeyNames::DebugF2)))
	{
		TileRender->IsUpdate() ? TileRender->Off() : TileRender->On();
	}

	if ((nullptr != ColTexture) && (true == KeyMgr::IsDown(KeyNames::DebugF2)))
	{
		ColRender->IsUpdate() ? ColRender->Off() : ColRender->On();
	}
}




