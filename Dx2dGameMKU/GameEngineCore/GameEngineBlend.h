#pragma once
#include "GameEngineResource.h"

/*
	아웃풋 머저 단계에서
		소스컬러와 목적지 컬러를 어떻게 합칠지에 대한 방법(곱하기, 빼기 등등)
		소스 컬러 : 이 렌더타겟에 추가될 색상값
		목적지 컬러 : 기존에 있었던 색상값
*/
class GameEngineBlend : public GameEngineResource<GameEngineBlend>
{
public:
	GameEngineBlend();
	~GameEngineBlend() override;

	GameEngineBlend(const GameEngineBlend& _Other) = delete;
	GameEngineBlend(GameEngineBlend&& _Other) noexcept = delete;
	GameEngineBlend& operator=(const GameEngineBlend& _Other) = delete;
	GameEngineBlend& operator=(const GameEngineBlend&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineBlend> Create(const std::string_view& _Name, const D3D11_BLEND_DESC& _Desc)
	{
		std::shared_ptr<GameEngineBlend> Res = GameEngineResource::Create(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting() override;

protected:

private:
	D3D11_BLEND_DESC Desc = {};
	ID3D11BlendState* State = nullptr;

	//2자리씩 끝어서 알파 블렌드를 수행할 색상값
	UINT Mask = 0xFFFFFFFF;

	void ResCreate(const D3D11_BLEND_DESC& _Value);
};

