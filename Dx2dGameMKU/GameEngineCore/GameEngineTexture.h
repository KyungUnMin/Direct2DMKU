#pragma once
#include "GameEngineResource.h"
#include <GameEngineCore/ThirdParty/DirectXTex/inc/DirectXTex.h>


//순수한 이미지 정보를 담는 리소스(API로 치면 HBITMAP)
class GameEngineTexture : public GameEngineResource<GameEngineTexture>
{
	friend GameEngineDevice;
	friend class GameEngineTextureSetter;

public:
	GameEngineTexture();
	~GameEngineTexture() override;

	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(const GameEngineTexture&& _Other) noexcept = delete;

	
	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _Path)
	{
		GameEnginePath NewPath(_Path);
		return Load(_Path, NewPath.GetFileName());
	}

	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _Path, const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResLoad(_Path);
		return NewTexture;
	}


	static std::shared_ptr<GameEngineTexture>  Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		return NewTexture;
	}

	static std::shared_ptr<GameEngineTexture>  Create(const std::string_view& _Name, ID3D11Texture2D* _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResCreate(_Value);
		return NewTexture;
	}



	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

protected:

private:
	//HBITMAP
	ID3D11Texture2D* Texture2D = nullptr;

	//이 비트맵의 HDC
	ID3D11RenderTargetView* RTV = nullptr;

	//Shader Resource View(이 텍스처를 사용할 수 있는 권한)
	ID3D11ShaderResourceView* SRV = nullptr;

	//텍스처의 정보를 담고 있는 구조체
	DirectX::TexMetadata Data = {};
	//이미지
	DirectX::ScratchImage Image;


	//텍스처를 로드하는 부분
	void ResLoad(const std::string_view& _Path);


	//GameEngineDevice에서 메인백버퍼 텍스처를 만들때 호출됨
	void ResCreate(ID3D11Texture2D* _Value);

	void CreateRenderTargetView();

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};

