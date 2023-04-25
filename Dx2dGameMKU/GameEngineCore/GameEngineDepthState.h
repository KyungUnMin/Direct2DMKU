#pragma once
#include "GameEngineResource.h"

class GameEngineDepthState : public GameEngineResource<GameEngineDepthState>
{
public:
	GameEngineDepthState();
	~GameEngineDepthState() override;

	GameEngineDepthState(const GameEngineDepthState& _Other) = delete;
	GameEngineDepthState(GameEngineDepthState&& _Other) noexcept = delete;
	GameEngineDepthState& operator=(const GameEngineDepthState& _Other) = delete;
	GameEngineDepthState& operator=(const GameEngineDepthState&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineDepthState> Create(const std::string_view& _Name, const D3D11_DEPTH_STENCIL_DESC& _Desc)
	{
		std::shared_ptr<GameEngineDepthState> Res = GameEngineResource::Create(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting() override;

	void ResCreate(const D3D11_DEPTH_STENCIL_DESC& _Value);

protected:

private:
	D3D11_DEPTH_STENCIL_DESC Desc = {};
	ID3D11DepthStencilState* State = nullptr;
};

