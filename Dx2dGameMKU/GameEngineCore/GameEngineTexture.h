#pragma once
#include "GameEngineResource.h"
#include <GameEngineCore/ThirdParty/DirectXTex/inc/DirectXTex.h>


class GameEnginePixelColor
{
public:
	static GameEnginePixelColor Black;

	union 
	{
		struct 
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};

		unsigned char ColorChar[4];
		int Color;
	};

	bool operator ==(const GameEnginePixelColor& _Other)
	{
		return Color == _Other.Color;
	}

	bool operator !=(const GameEnginePixelColor& _Other)
	{
		return !(*this == _Other);
	}

	float4 Tofloat4()
	{
		//TODO
	}

	GameEnginePixelColor()
	{

	}

	GameEnginePixelColor(unsigned char  _r, unsigned char  _g, unsigned char  _b, unsigned char  _a)
		:r(_r), g(_g), b(_b), a(_a)
	{

	}
};


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


	//�ؽ�ó�� �ε��Ҷ����� ���� ������ ����Ѵ�
	static void PathCheck(const std::string_view& _Path, const std::string_view& _Name);

	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _Path, const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);

		PathCheck(_Path, _Name);
		NewTexture->SetPath(_Path);
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


	//�ؽ�ó�� GPU�󿡼� �Ҹ��Ų��
	static std::shared_ptr<GameEngineTexture> UnLoad(const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineTexture> FindTexture = GameEngineResource::Find(_Name);

		if (nullptr == FindTexture)
		{
			MsgAssert("�������� �ʴ� �ؽ�ó�� ��ε� �Ϸ��� �߽��ϴ�.");
			return nullptr;
		}

		FindTexture->Release();
		return FindTexture;
	}

	//Unload��Ų �ؽ�ó�� �ٽ� �ε��Ѵ�
	static std::shared_ptr<GameEngineTexture> ReLoad(const std::string_view& _Path)
	{
		GameEnginePath NewPath(_Path);
		return ReLoad(_Path, NewPath.GetFileName());
	}

	//Unload��Ų �ؽ�ó�� �ٽ� �ε��Ѵ�
	static std::shared_ptr<GameEngineTexture> ReLoad(const std::string_view& _Path, const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineTexture> FindTexture = GameEngineResource<GameEngineTexture>::Find(_Name);

		if (nullptr == FindTexture)
		{
			MsgAssert("�������� �ʴ� �ؽ�ó�� �ε� �Ϸ��� �߽��ϴ�.");
			return nullptr;
		}

		FindTexture->ReLoad();
		return FindTexture;
	}



	ID3D11ShaderResourceView* GetSRV()
	{
		return SRV;
	}


	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}


	ID3D11DepthStencilView* GetDSV()
	{
		return DSV;
	}


	int GetWidth()
	{
		return Desc.Width;
	}

	int GetHeight()
	{
		return Desc.Height;
	}

	float4 GetScale()
	{
		return float4(static_cast<float>(Desc.Width), static_cast<float>(Desc.Height));
	}


	GameEnginePixelColor GetPixel(int _X, int _Y, const GameEnginePixelColor& _DefaultColor = GameEnginePixelColor::Black);

	void ReLoad();

	//�ؽ�ó�� GPU�󿡼� �Ҹ��Ų��
	void Release();

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


	void CreateShaderResourcesView();

	//���� ���ۿ� �ؽ�ó�� ������ٸ� �װ��� ������ �� �ִ� DSV����
	void CreateDepthStencilView();

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);


	//���������ο��� ������ �۾�
	//Camera�� CamTarget(����Ÿ��)��
	//���ؽ� ���̴������� ���̰�
	//�ƿ�ǲ ���������� ������ ����� ������ �����ϱ� ����
	void VSReset(UINT _Slot);
	void PSReset(UINT _Slot);


	
};

