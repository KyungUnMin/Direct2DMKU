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


	//디바이스 초기화
	static void Initialize();

	//윈도우 메인 HDC같은 백버퍼 만들기
	static void CreateSwapChain();

	//아래 정적변수들은 다 핸들러 같은 개념이다.
	//때문에 프로그램이 종료될 때 Release해주어야 한다
	static void Release();

	//렌더링을 시작하기 전에 이전의 이미지들을 지운다
	static void RenderStart();
	//더블버퍼링을 이용한 렌더링 처리
	static void RenderEnd();

	//비디오 전용 임시 렌더링 기능
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
	//리소스 인터페이스(리소스를 GPU 램에 불러오거나 접근하는 등의 인터페이스)
	static ID3D11Device* Device;

	//렌더링 인터페이스(화면에 그리기 위한 인터페이스)
	static ID3D11DeviceContext* Context;

	//화면에 그리기 위한 도화지(WINAPI의 메인 백버퍼 이미지를 가지고 있는 클래스 같은 느낌)
	//옵션을 통해 더블버퍼링도 내부적으로 제공해준다
	static IDXGISwapChain* SwapChain;

	//실제 윈도우의 화면에 이미지를 그릴 백버퍼 HDC
	static std::shared_ptr<class GameEngineRenderTarget> BackBufferTarget;

	//가지고 있는 그래픽카드중에 최고 옵션의 
	//GPU와 연결할 수 있는 어뎁터를 반환함 (최고 성능의 GPU 선택 기준은 GPU에 붙어있는 램크기)
	static IDXGIAdapter* GetHighPerformanceAdater();

	GameEngineDevice();
	~GameEngineDevice();
};

