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


	//디바이스 초기화
	static void Initialize();

	//윈도우 메인 HDC같은 백버퍼 만들기
	static void CreateSwapChain();

	//아래 정적변수들은 다 핸들러 같은 개념이다.
	//때문에 프로그램이 종료될 때 Release해주어야 한다
	static void Release();

protected:

private:
	//리소스 인터페이스(리소스를 GPU 램에 불러오거나 접근하는 등의 인터페이스)
	static ID3D11Device* Device;

	//렌더링 인터페이스(화면에 그리기 위한 인터페이스)
	static ID3D11DeviceContext* Context;

	//화면에 그리기 위한 도화지(WINAPI의 메인 HDC같은 개념)
	//옵션을 통해 더블버퍼링도 내부적으로 제공해준다
	static IDXGISwapChain* SwapChain;


	//가지고 있는 그래픽카드중에 최고 옵션의 
	//GPU와 연결할 수 있는 어뎁터를 반환함 (최고 성능의 GPU 선택 기준은 GPU에 붙어있는 램크기)
	static IDXGIAdapter* GetHighPerformanceAdater();

	GameEngineDevice();
	~GameEngineDevice();
};

