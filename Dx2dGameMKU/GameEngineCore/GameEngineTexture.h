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

	//컨텐츠쪽에서 이미지 텍스처를 로드할때 호출됨
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


	/*static std::shared_ptr<GameEngineTexture>  Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		return NewTexture;
	}

	static std::shared_ptr<GameEngineTexture>  Create(const std::string_view& _Name, ID3D11Texture2D* _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResCreate(_Value);
		return NewTexture;
	}*/


	//이름없는 텍스처(빈 텍스처)를 만들때 사용_주로 깊이버퍼용 텍스처에 사용된다 (아직까진 디바이스 -> 렌더타겟을 통해서 호출된다)
	static std::shared_ptr<GameEngineTexture> Create(const D3D11_TEXTURE2D_DESC& _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::CreateUnNamed();
		NewTexture->ResCreate(_Value);
		return NewTexture;
	}



	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}


	ID3D11DepthStencilView* GetDSV()
	{
		return DSV;
	}


	unsigned int GetWidth()
	{
		return Desc.Width;
	}

	unsigned int GetHeight()
	{
		return Desc.Height;
	}

protected:

private:
	//HBITMAP
	ID3D11Texture2D* Texture2D = nullptr;

	//이 비트맵의 HDC
	ID3D11RenderTargetView* RTV = nullptr;

	//깊이 버퍼 뷰(텝스 스텐실 뷰)
	ID3D11DepthStencilView* DSV = nullptr;

	//Shader Resource View(이 텍스처를 사용할 수 있는 권한)
	ID3D11ShaderResourceView* SRV = nullptr;


	//만든 텍스처의 정보를 기록하는 용도
	D3D11_TEXTURE2D_DESC Desc;



	//텍스처의 정보를 담고 있는 구조체
	DirectX::TexMetadata Data = {};
	//이미지
	DirectX::ScratchImage Image;



	//텍스처를 로드하는 부분
	void ResLoad(const std::string_view& _Path);


	//GameEngineDevice에서 메인백버퍼 텍스처를 만들때 직접 호출됨(스왑체인에 존재하는 텍스처를 얻어옴)
	void ResCreate(ID3D11Texture2D* _Value);


	//빈 텍스처를 만들때 사용됨(주로 깊이버퍼용 텍스처를 만들때 사용)
	void ResCreate(const D3D11_TEXTURE2D_DESC& _Value);


	//텍스처를 만들었다면 그것을 제어할 수 있는 RTV생성
	void CreateRenderTargetView();

	//깊이 버퍼용 텍스처를 만들었다면 그것을 제어할 수 있는 DSV생성
	void CreateDepthStencilView();

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};

