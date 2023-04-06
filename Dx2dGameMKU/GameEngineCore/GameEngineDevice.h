#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>


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

protected:

private:
	//���ҽ� �������̽�(���ҽ��� GPU ���� �ҷ����ų� �����ϴ� ���� �������̽�)
	static ID3D11Device* Device;

	//������ �������̽�(ȭ�鿡 �׸��� ���� �������̽�)
	static ID3D11DeviceContext* Context;

	//ȭ�鿡 �׸��� ���� ��ȭ��(WINAPI�� ���� HDC���� ����)
	//�ɼ��� ���� ������۸��� ���������� �������ش�
	static IDXGISwapChain* SwapChain;


	//������ �ִ� �׷���ī���߿� �ְ� �ɼ��� 
	//GPU�� ������ �� �ִ� ��͸� ��ȯ�� (�ְ� ������ GPU ���� ������ GPU�� �پ��ִ� ��ũ��)
	static IDXGIAdapter* GetHighPerformanceAdater();

	GameEngineDevice();
	~GameEngineDevice();
};

