#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <memory>


class GameEngineDevice
{
public:
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator=(const GameEngineDevice&& _Other) noexcept = delete;


	//����̽� �ʱ�ȭ
	static void Initialize();

	//������ ���� HDC���� ����� �����
	static void CreateSwapChain();

	//�Ʒ� ������������ �� �ڵ鷯 ���� �����̴�.
	//������ ���α׷��� ����� �� Release���־�� �Ѵ�
	static void Release();

	//�������� �����ϱ� ���� ������ �̹������� �����
	static void RenderStart();
	//������۸��� �̿��� ������ ó��
	static void RenderEnd();

	//���� ���� �ӽ� ������ ���
	static void VideoRenderStart();
	static void VideoRenderEnd();

	static ID3D11Device* GetDevice()
	{
		return Device;
	}

	static ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

	static std::shared_ptr<class GameEngineRenderTarget> GetBackBufferTarget()
	{
		return BackBufferTarget;
	}

protected:

private:
	//���ҽ� �������̽�(���ҽ��� GPU ���� �ҷ����ų� �����ϴ� ���� �������̽�)
	static ID3D11Device* Device;

	//������ �������̽�(ȭ�鿡 �׸��� ���� �������̽�)
	static ID3D11DeviceContext* Context;

	//ȭ�鿡 �׸��� ���� ��ȭ��(WINAPI�� ���� ����� �̹����� ������ �ִ� Ŭ���� ���� ����)
	//�ɼ��� ���� ������۸��� ���������� �������ش�
	static IDXGISwapChain* SwapChain;

	//���� �������� ȭ�鿡 �̹����� �׸� ����� HDC
	static std::shared_ptr<class GameEngineRenderTarget> BackBufferTarget;

	//������ �ִ� �׷���ī���߿� �ְ� �ɼ��� 
	//GPU�� ������ �� �ִ� ��͸� ��ȯ�� (�ְ� ������ GPU ���� ������ GPU�� �پ��ִ� ��ũ��)
	static IDXGIAdapter* GetHighPerformanceAdater();

	GameEngineDevice();
	~GameEngineDevice();
};

