#include "PrecompileHeader.h"
#include "GameEngineVideo.h"
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineVideo::GameEngineVideo()
{

}

GameEngineVideo::~GameEngineVideo()
{
	Release();
}



void GameEngineVideo::VideoLoad(const std::string_view& _Path)
{
	HWND MainHwnd = GameEngineWindow::GetHWnd();
	//UpdateWindow(MainHwnd);
	

	HRESULT Result;
	/*Result = CoInitialize(nullptr);
	if (S_OK != Result)
	{
		MsgAssert("Com 초기화에 실패했습니다");
		return;
	}*/


	//(마지막 인자를 제외하고는 라이브러리에 있는 전역변수입니다)
	//IID_IGraphBuilder 인터페이스를 생성하고 핸들러를 받아오는듯합니다. 
	Result = CoCreateInstance(
		CLSID_FilterGraph, 
		nullptr, 
		CLSCTX_INPROC_SERVER, 
		IID_IGraphBuilder, 
		reinterpret_cast<void**>(&GraphBuilderPtr));
	if (S_OK != Result)
	{
		MsgAssert("DirectShow IID_IGraphBuilder 생성에 실패했습니다");
		return;
	}


	//동영상 리소스 불러오기(.avi만 가능합니다)
	std::wstring UnicodePath = GameEngineString::AnsiToUniCode(_Path.data());
	Result = GraphBuilderPtr->RenderFile(UnicodePath.c_str(), nullptr);

	if (Result == VFW_E_UNSUPPORTED_STREAM)
	{
		MsgAssert(".AVI 동영상만 로드 가능합니다");
		return;
	}

	if (S_OK != Result)
	{
		MsgAssert("동영상 로드에 실패했습니다\n마소 공식 문서 RenderFile의 반환값을 확인해보세요");
		return;
	}

	
	//첫번째 인자들은 모두 라이브러리에 있는 전역변수입니다
	GraphBuilderPtr->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(&Controller));
	GraphBuilderPtr->QueryInterface(IID_IMediaEventEx, reinterpret_cast<void**>(&Eventer));
	GraphBuilderPtr->QueryInterface(IID_IMediaSeeking, reinterpret_cast<void**>(&Seeker));
	GraphBuilderPtr->QueryInterface(IID_IMediaPosition, reinterpret_cast<void**>(&MediaPos));

	GraphBuilderPtr->QueryInterface(IID_IVideoWindow, reinterpret_cast<void**>(&VideoWindowPtr));
	GraphBuilderPtr->QueryInterface(IID_IBasicVideo, reinterpret_cast<void**>(&BasicVideoPtr));

	GraphBuilderPtr->QueryInterface(IID_IBasicAudio, reinterpret_cast<void**>(&BasicAudioPtr));

	
	//이벤트 알림을 처리할 창을 등록합니다.
	Eventer->SetNotifyWindow(
		reinterpret_cast<OAHWND>(MainHwnd), 
		WM_USER + 13, 0);

	//동영상이 출력될 HWND를 설정합니다
	VideoWindowPtr->put_Owner(reinterpret_cast<OAHWND>(MainHwnd));
	//동영상 창의 스타일을 설정합니다
	VideoWindowPtr->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	//비디오 윈도우 크기와 위치를 초기화합니다
	RECT VideoRect = {};
	GetClientRect(MainHwnd, &VideoRect);
	VideoWindowPtr->SetWindowPosition(VideoRect.left, VideoRect.top, VideoRect.right, VideoRect.bottom);

	//프레임 스텝을 받아와 설정합니다
	GraphBuilderPtr->QueryInterface(__uuidof(IVideoFrameStep), reinterpret_cast<void**>(&FrameStep));
	if (nullptr == FrameStep)
	{
		MsgAssert("프레임 스텝 생성에 실패했습니다");
		return;
	}

	//지정된 필터의 단계별 실행 기능을 결정합니다.(0L은 그냥 0입니다)
	if (S_OK != FrameStep->CanStep(0L, nullptr))
	{
		FrameStep->Release();
		MsgAssert("프레임 스텝을 설정할 수 없습니다");
	}

}




void GameEngineVideo::Play()
{
	HWND MainHwnd = GameEngineWindow::GetHWnd();

	//윈도우 활성화(혹시나 싶어서 넣는 함수들)
	ShowWindow(MainHwnd, SW_SHOWNORMAL);
	UpdateWindow(MainHwnd);
	SetForegroundWindow(MainHwnd);
	SetFocus(MainHwnd);

	HRESULT Result = Controller->Run();
	if (FAILED(Result))
	{
		MsgAssert("동영상 재생에 실패하였습니다");
		return;
	}
}


void GameEngineVideo::Release()
{
	if (nullptr != VideoWindowPtr)
	{
		VideoWindowPtr->put_Visible(OAFALSE);
		VideoWindowPtr->put_Owner(reinterpret_cast<OAHWND>(GameEngineWindow::GetHWnd()));
	}

	if (nullptr != GraphBuilderPtr)
	{
		GraphBuilderPtr->Release();
		GraphBuilderPtr = nullptr;
	}

	if (nullptr != Controller)
	{
		Controller->Release();
		Controller = nullptr;
	}

	if (nullptr != Eventer)
	{
		Eventer->Release();
		Eventer = nullptr;
	}

	if (nullptr != MediaPos)
	{
		MediaPos->Release();
		MediaPos = nullptr;
	}

	if (nullptr != VideoWindowPtr)
	{
		VideoWindowPtr->Release();
		VideoWindowPtr = nullptr;
	}

	if (nullptr != BasicVideoPtr)
	{
		BasicVideoPtr->Release();
		BasicVideoPtr = nullptr;
	}

	if (nullptr != BasicAudioPtr)
	{
		BasicAudioPtr->Release();
		BasicAudioPtr = nullptr;
	}

	if (nullptr != FrameStep)
	{
		FrameStep->Release();
		FrameStep = nullptr;
	}

}