#pragma once
#include "GameEngineResource.h"

//순수한 이미지 정보를 담는 리소스(API로 치면 HBITMAP)
class GameEngineTexture : public GameEngineResource<GameEngineTexture>
{
	friend GameEngineDevice;

public:
	GameEngineTexture();
	~GameEngineTexture() override;

	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(const GameEngineTexture&& _Other) noexcept = delete;

	//Core에서 이 함수를 호출시키므로써
	//만들려는 리소스를
	//static Resources 자료구조에 Texture별로 저장하게 됨
	//(이름이 키값인 Map or List)
	static void Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
	}

	static void Create(const std::string_view& _Name, ID3D11Texture2D* _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResCreate(_Value);
	}

	ID3D11RenderTargetView* GetRTV()
	{
		return RenderTarget;
	}

protected:

private:
	//HBITMAP
	ID3D11Texture2D* Texture2D = nullptr;

	//이 비트맵의 HDC
	ID3D11RenderTargetView* RenderTarget = nullptr;

	//GameEngineDevice에서 메인백버퍼 텍스처를 만들때 호출됨
	void ResCreate(ID3D11Texture2D* _Value);

	void CreateRenderTargetView();
};

