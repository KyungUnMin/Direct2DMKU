#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineInput.h"

HWND                       GameEngineWindow::HWnd = nullptr;
HDC                          GameEngineWindow::WindowBackBufferHdc = nullptr;
                                
float4                       GameEngineWindow::WindowSize = { 800, 600 };
float4                       GameEngineWindow::WindowPos = { 100, 100 };
float4                       GameEngineWindow::ScreenSize = { 800, 600 };

GameEngineImage* GameEngineWindow::BackBufferImage = nullptr;
GameEngineImage* GameEngineWindow::DoubleBufferImage = nullptr;

bool                         GameEngineWindow::IsWindowUpdate = true;


//메세지에 따른 콜백 함수
LRESULT CALLBACK GameEngineWindow::MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_KEYDOWN:
    {
        GameEngineInput::IsAnyKeyOn();
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        IsWindowUpdate = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}



GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{

}



void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos)
{
    //윈도우 클래스를 만들기 위한 정보 기입
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;

    //메세지 처리 콜백
    wcex.lpfnWndProc = MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;

    //큰 아이콘 제거
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    //툴바(메뉴바) 제거
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowDefault";

    //작은 아이콘 제거
    wcex.hIconSm = nullptr;

    //예외처리
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("윈도우 클래스 등록에 실패했습니다.");
        return;
    }


    //윈도우 창 만들기
    HWnd = CreateWindow(
        "GameEngineWindowDefault",
        _TitleName.data(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT
        , 0, CW_USEDEFAULT, 0
        , nullptr, nullptr, _hInstance, nullptr);


    //예외처리
    if (nullptr == HWnd)
    {
        MsgAssert("윈도우 클래스 생성에 실패했습니다.");
        return;
    }

    WindowBackBufferHdc = GetDC(HWnd);

    //윈도우 창 띄우기
    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    //윈도우 크기 설정(내부에서 더블버퍼용 이미지 생성)
    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    //윈도우 백버퍼HDC를 Image클래스로 관리
    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);

    return;
}

void GameEngineWindow::DoubleBufferClear()
{
    DoubleBufferImage->ImageClear();
}

void GameEngineWindow::DoubleBufferRender()
{
    BackBufferImage->BitCopy(DoubleBufferImage, ScreenSize.half(), ScreenSize);
}


//실제 게임이 동작하는 부분
//콜백 방식을 이용해서 엔진과 컨텐츠 부분을 분리
int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    if (nullptr != _Start)
    {
        _Start();
    }

    MSG msg;

    while (IsWindowUpdate)
    {
        //메세지가 있다면 메세지 처리
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (nullptr != _Loop)
            {
                _Loop();
            }

            GameEngineInput::IsAnyKeyOff();
            continue;
        }

        if (nullptr != _Loop)
        {
            _Loop();
        }

        GameEngineInput::IsAnyKeyOff();
    }

    if (nullptr != _End)
    {
        _End();
    }


    if (nullptr != BackBufferImage)
    {
        //윈도우 백버퍼HDC의 Image객체 delete
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;

        //더블버퍼용 이미지 delete
        delete BackBufferImage;
        BackBufferImage = nullptr;
    }

    return (int)msg.wParam;
}



void GameEngineWindow::SettingWindowSize(float4 _Size)
{
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };
    ScreenSize = _Size;

    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);
    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);


    //이미지를 다시한번 재조정하는 경우
    if (nullptr != DoubleBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;
    }

    //더블 버퍼링 용 이미지 생성
    DoubleBufferImage = new GameEngineImage();
    DoubleBufferImage->ImageCreate(ScreenSize);
}


void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

float4 GameEngineWindow::GetMousePosition()
{
    POINT MoniterPoint;
    LPPOINT PointPtr = &MoniterPoint;

    //모니터 기준 마우스 좌표
    GetCursorPos(PointPtr);

    //모니터 기준 좌표 -> 윈도우 창 기준 좌표
    ScreenToClient(HWnd, PointPtr);

    //float4로 변경해서 return
    return { static_cast<float>(MoniterPoint.x),static_cast<float>(MoniterPoint.y) };
}