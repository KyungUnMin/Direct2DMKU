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
		MsgAssert("Com �ʱ�ȭ�� �����߽��ϴ�");
		return;
	}*/


	//(������ ���ڸ� �����ϰ�� ���̺귯���� �ִ� ���������Դϴ�)
	//IID_IGraphBuilder �������̽��� �����ϰ� �ڵ鷯�� �޾ƿ��µ��մϴ�. 
	Result = CoCreateInstance(
		CLSID_FilterGraph, 
		nullptr, 
		CLSCTX_INPROC_SERVER, 
		IID_IGraphBuilder, 
		reinterpret_cast<void**>(&GraphBuilderPtr));
	if (S_OK != Result)
	{
		MsgAssert("DirectShow IID_IGraphBuilder ������ �����߽��ϴ�");
		return;
	}


	//������ ���ҽ� �ҷ�����(.avi�� �����մϴ�)
	std::wstring UnicodePath = GameEngineString::AnsiToUniCode(_Path.data());
	Result = GraphBuilderPtr->RenderFile(UnicodePath.c_str(), nullptr);

	if (Result == VFW_E_UNSUPPORTED_STREAM)
	{
		MsgAssert(".AVI ������ �ε� �����մϴ�");
		return;
	}

	if (S_OK != Result)
	{
		MsgAssert("������ �ε忡 �����߽��ϴ�\n���� ���� ���� RenderFile�� ��ȯ���� Ȯ���غ�����");
		return;
	}

	
	//ù��° ���ڵ��� ��� ���̺귯���� �ִ� ���������Դϴ�
	GraphBuilderPtr->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(&Controller));
	GraphBuilderPtr->QueryInterface(IID_IMediaEventEx, reinterpret_cast<void**>(&Eventer));
	GraphBuilderPtr->QueryInterface(IID_IMediaSeeking, reinterpret_cast<void**>(&Seeker));
	GraphBuilderPtr->QueryInterface(IID_IMediaPosition, reinterpret_cast<void**>(&MediaPos));

	GraphBuilderPtr->QueryInterface(IID_IVideoWindow, reinterpret_cast<void**>(&VideoWindowPtr));
	GraphBuilderPtr->QueryInterface(IID_IBasicVideo, reinterpret_cast<void**>(&BasicVideoPtr));

	GraphBuilderPtr->QueryInterface(IID_IBasicAudio, reinterpret_cast<void**>(&BasicAudioPtr));

	
	//�̺�Ʈ �˸��� ó���� â�� ����մϴ�.
	Eventer->SetNotifyWindow(
		reinterpret_cast<OAHWND>(MainHwnd), 
		WM_USER + 13, 0);

	//�������� ��µ� HWND�� �����մϴ�
	VideoWindowPtr->put_Owner(reinterpret_cast<OAHWND>(MainHwnd));
	//������ â�� ��Ÿ���� �����մϴ�
	VideoWindowPtr->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	//���� ������ ũ��� ��ġ�� �ʱ�ȭ�մϴ�
	RECT VideoRect = {};
	GetClientRect(MainHwnd, &VideoRect);
	VideoWindowPtr->SetWindowPosition(VideoRect.left, VideoRect.top, VideoRect.right, VideoRect.bottom);

	//������ ������ �޾ƿ� �����մϴ�
	GraphBuilderPtr->QueryInterface(__uuidof(IVideoFrameStep), reinterpret_cast<void**>(&FrameStep));
	if (nullptr == FrameStep)
	{
		MsgAssert("������ ���� ������ �����߽��ϴ�");
		return;
	}

	//������ ������ �ܰ躰 ���� ����� �����մϴ�.(0L�� �׳� 0�Դϴ�)
	if (S_OK != FrameStep->CanStep(0L, nullptr))
	{
		FrameStep->Release();
		MsgAssert("������ ������ ������ �� �����ϴ�");
	}

}




void GameEngineVideo::Play()
{
	HWND MainHwnd = GameEngineWindow::GetHWnd();

	//������ Ȱ��ȭ(Ȥ�ó� �; �ִ� �Լ���)
	ShowWindow(MainHwnd, SW_SHOWNORMAL);
	UpdateWindow(MainHwnd);
	SetForegroundWindow(MainHwnd);
	SetFocus(MainHwnd);

	HRESULT Result = Controller->Run();
	if (FAILED(Result))
	{
		MsgAssert("������ ����� �����Ͽ����ϴ�");
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