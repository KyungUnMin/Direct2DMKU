#include "PrecompileHeader.h"
#include "Fader.h"



#include "RCGEnums.h"

#include "ShaderUIRenderer.h"

Fader* Fader::IsFading = nullptr;

Fader::Fader()
{

}

Fader::~Fader()
{

}

void Fader::Start()
{
	UIBase::Start();

    RenderPtr = CreateComponent<ShaderUIRenderer>(FieldUIRenderOrder::Fade);
	RenderPtr->SetPipeLine("DirectColor");
	RenderPtr->GetShaderResHelper().SetConstantBufferLink("LinkColor", FadeColor);
	RenderPtr->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
}

void Fader::Update(float _DeltaTime)
{
	UIBase::Update(_DeltaTime);

	if (true == IsDeath())
		return;



	//다른곳에서 페이드가 진행중이라면 기다리기
	if (nullptr == IsFading)
	{
		IsFading = this;
	}
	if (this != IsFading)
		return;

	float LiveTime = GetLiveTime();
	float Ratio = (LiveTime / Duration);

	if (true == IsFadeIn)
	{
		FadeColor.w = Ratio;
	}
	else
	{
		FadeColor.w = (1.f - Ratio);
	}

	if (Ratio < 1.f)
		return;

	if (nullptr != Callback)
	{
		Callback();
	}

	//아직 Death 기능이 없어서 멤버변수로 렌더러를 들고 있음
	//페이드에서 화면 깜빡이는건 렌더 오프 주석하면 해결됨
	//RenderPtr->Off();
	IsFading = nullptr;
	Death();
}
