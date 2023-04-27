#pragma once
#include "GameEngineResource.h"
#include <GameEngineCore/ThirdParty/DirectXTex/inc/DirectXTex.h>


//������ �̹��� ������ ��� ���ҽ�(API�� ġ�� HBITMAP)
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

	//�������ʿ��� �̹��� �ؽ�ó�� �ε��Ҷ� ȣ���
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


	//�̸����� �ؽ�ó(�� �ؽ�ó)�� ���鶧 ���_�ַ� ���̹��ۿ� �ؽ�ó�� ���ȴ� (�������� ����̽� -> ����Ÿ���� ���ؼ� ȣ��ȴ�)
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

	//�� ��Ʈ���� HDC
	ID3D11RenderTargetView* RTV = nullptr;

	//���� ���� ��(�ܽ� ���ٽ� ��)
	ID3D11DepthStencilView* DSV = nullptr;

	//Shader Resource View(�� �ؽ�ó�� ����� �� �ִ� ����)
	ID3D11ShaderResourceView* SRV = nullptr;


	//���� �ؽ�ó�� ������ ����ϴ� �뵵
	D3D11_TEXTURE2D_DESC Desc;



	//�ؽ�ó�� ������ ��� �ִ� ����ü
	DirectX::TexMetadata Data = {};
	//�̹���
	DirectX::ScratchImage Image;



	//�ؽ�ó�� �ε��ϴ� �κ�
	void ResLoad(const std::string_view& _Path);


	//GameEngineDevice���� ���ι���� �ؽ�ó�� ���鶧 ���� ȣ���(����ü�ο� �����ϴ� �ؽ�ó�� ����)
	void ResCreate(ID3D11Texture2D* _Value);


	//�� �ؽ�ó�� ���鶧 ����(�ַ� ���̹��ۿ� �ؽ�ó�� ���鶧 ���)
	void ResCreate(const D3D11_TEXTURE2D_DESC& _Value);


	//�ؽ�ó�� ������ٸ� �װ��� ������ �� �ִ� RTV����
	void CreateRenderTargetView();

	//���� ���ۿ� �ؽ�ó�� ������ٸ� �װ��� ������ �� �ִ� DSV����
	void CreateDepthStencilView();

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};

