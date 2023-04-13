#pragma once
#include "GameEngineResource.h"

class GameEngineRasterizer : public GameEngineResource<GameEngineRasterizer>
{
public:
	GameEngineRasterizer();
	~GameEngineRasterizer() override;

	GameEngineRasterizer(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer(GameEngineRasterizer&& _Other) noexcept = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineRasterizer> Create(const std::string_view& _Name, const D3D11_RASTERIZER_DESC& _Desc)
	{
		std::shared_ptr<GameEngineRasterizer> Res = GameEngineResource::Create(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}


	//레스터라이저를 GPU에 세팅
	void Setting() override;


	//Fill모드 바꾸기
	inline void SetFILL_MODE(D3D11_FILL_MODE _Value)
	{
		switch (_Value)
		{
		case D3D11_FILL_WIREFRAME:
			CurState = WireframeState;
			break;
		case D3D11_FILL_SOLID:
			CurState = SolidState;
			break;
		default:
			break;
		}
	}


	//Cull모드 바꾸기
	inline void SetCULL_MODE(D3D11_CULL_MODE _Value)
	{
		Desc.CullMode = _Value;
		ResCreate(Desc);
	}

protected:

private:
	D3D11_RASTERIZER_DESC Desc = {};

	ID3D11RasterizerState* CurState = nullptr;
	ID3D11RasterizerState* SolidState = nullptr;
	ID3D11RasterizerState* WireframeState = nullptr;

	void ResCreate(const D3D11_RASTERIZER_DESC& _Value);
	void Release();
};

