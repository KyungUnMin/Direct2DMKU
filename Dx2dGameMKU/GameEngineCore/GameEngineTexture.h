#pragma once
#include "GameEngineResource.h"

//������ �̹��� ������ ��� ���ҽ�(API�� ġ�� HBITMAP)
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

	//Core���� �� �Լ��� ȣ���Ű�Ƿν�
	//������� ���ҽ���
	//static Resources �ڷᱸ���� Texture���� �����ϰ� ��
	//(�̸��� Ű���� Map or List)
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

	//�� ��Ʈ���� HDC
	ID3D11RenderTargetView* RenderTarget = nullptr;

	//GameEngineDevice���� ���ι���� �ؽ�ó�� ���鶧 ȣ���
	void ResCreate(ID3D11Texture2D* _Value);

	void CreateRenderTargetView();
};

