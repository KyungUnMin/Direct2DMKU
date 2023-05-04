#include "PrecompileHeader.h"
#include "GameEngineGUI.h"

#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineDevice.h"

std::map<std::string, std::shared_ptr<GameEngineGUIWindow>> GameEngineGUI::AllWindow;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

GameEngineGUI::GameEngineGUI()
{

}

GameEngineGUI::~GameEngineGUI()
{

}


void GameEngineGUI::Initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;      
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(GameEngineWindow::GetHWnd());
    ImGui_ImplDX11_Init(GameEngineDevice::GetDevice(), GameEngineDevice::GetContext());

    GameEngineWindow::SetUserMessageFunction(ImGui_ImplWin32_WndProcHandler);

    //한글 폰트 추가
    GameEngineDirectory Dir;
    Dir.MoveParentToDirectory("EngineResources");
    Dir.Move("EngineResources");
    Dir.Move("Font");
    io.Fonts->AddFontFromFileTTF(Dir.GetPlusFileName("malgun.ttf").GetFullPath().c_str(), 18.f, nullptr, io.Fonts->GetGlyphRangesKorean());
}



void GameEngineGUI::Render(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime)
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (const std::pair<std::string, std::shared_ptr<GameEngineGUIWindow>>& WindowPair : AllWindow)
    {
        std::shared_ptr<GameEngineGUIWindow> WindowPtr = WindowPair.second;

        //활성화 되어 있는 GUI만 실행
        if (false == WindowPtr->IsUpdate())
            continue;

        WindowPtr->Begin();
        WindowPtr->OnGUI(_Level, _DeltaTime);
        WindowPtr->End();
    }

    ImGui::Render();


    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    ImGuiIO& io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}



void GameEngineGUI::Release() 
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}