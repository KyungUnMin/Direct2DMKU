#include "PrecompileHeader.h"
#include "GameEngineFontRenderer.h"


GameEngineFontRenderer::GameEngineFontRenderer()
{

}

GameEngineFontRenderer::~GameEngineFontRenderer()
{

}

void GameEngineFontRenderer::SetFont(const std::string_view& _Font)
{
	Font = GameEngineFont::Find(_Font);
}

void GameEngineFontRenderer::SetText(const std::string_view& _Text)
{
	Text = _Text;
}



void GameEngineFontRenderer::Render(float _DeltaTime)
{
	if (nullptr == Font)
	{
		return;
	}

	if ("" == Text)
	{
		return;
	}

	

	//이 렌더러의 월드 위치에
	float4 Pos = GetTransform()->GetWorldPosition();
	GameEngineCamera* Camera = GetCamera();

	//뷰 프로젝션 뷰포트를 곱해서 윈도우 좌표로 만든다
	Pos *= Camera->GetView();
	Pos *= Camera->GetProjection();
	Pos *= Camera->GetViewPort();

	Font->FontDraw(Text, Pos, FontScale, FontColor, FwTextFlag);


	//파이프라인은 다른 누군가가 빼주지 않으면 계속 박혀있는다
	//폰트와퍼는 지오메트리 쉐이더를 사용한다
	// 
	// 지오메트리는 버텍스 쉐이더의 정보를 입력받아야 한다
	// 즉 버텍스쪽에서 정보를 건내주지 않으면 오류가 발생한다
	// 
	// 이 폰트 렌더러는 문제가 없지만
	// 다른 렌더러의 파이프를 진행할때는
	// 여전히 지오메트리 쉐이더가 박혀있다
	//그래서 오류를 예방하기 위해 때문에 지오메트리쉐이더를 파이프에서 빼준다
	GameEngineDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);
}


void GameEngineFontRenderer::Start()
{
	GameEngineRenderer::Start();
}