#pragma once
#include <string>
#include <Windows.h>
#include <functional>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineImage;

class GameEngineWindow
{
	static LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	//윈도우 메세지를 처리하기 전에 실행될 콜백
	static std::function<LRESULT(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)> UserMessageFunction;

public:
	static void SetUserMessageFunction(std::function<LRESULT(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)> _UserMessageFunction)
	{
		UserMessageFunction = _UserMessageFunction;
	}

	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

	static void SettingWindowSize(float4 _Size);
	static void SettingWindowPos(float4 _Pos);

	static float4 GetScreenSize()
	{
		return ScreenSize;
	}

	static HWND GetHWnd()
	{
		return HWnd;
	}

	static HDC GetWindowBackBufferHdc()
	{
		return WindowBackBufferHdc;
	}

	static GameEngineImage* GetDoubleBufferImage()
	{
		return DoubleBufferImage;
	}

	static void AppOff()
	{
		IsWindowUpdate = false;
	}

	static void DoubleBufferClear();
	static void DoubleBufferRender();

	static int WindowLoop(
		std::function<void()> _Start,
		std::function<void()> _Loop,
		std::function<void()> _End);

	static float4 GetMousePosition();

	static void Release();

	GameEngineWindow();
	~GameEngineWindow();

	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

protected:

private:
	static	float4							WindowSize;
	static	float4							ScreenSize;
	static	float4							WindowPos;

	static	HWND							HWnd;
	static	HDC								WindowBackBufferHdc;

	static	GameEngineImage*		BackBufferImage;
	static	GameEngineImage*		DoubleBufferImage;

	static	bool								IsWindowUpdate;
	static	WNDCLASSEX				wcex;
};

