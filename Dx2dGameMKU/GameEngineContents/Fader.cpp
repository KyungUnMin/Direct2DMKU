#include "PrecompileHeader.h"
#include "Fader.h"

#include <GameEngineCore/GameEngineRenderer.h>

Fader::Fader()
{
	
}

Fader::~Fader()
{

}

void Fader::Start()
{
	UIBase::Start();

	RenderPtr = CreateComponent<GameEngineRenderer>();
	RenderPtr->SetPipeLine("DirectColor");
	RenderPtr->GetShaderResHelper().SetConstantBufferLink("LinkColor", FadeColor);
	RenderPtr->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
}

void Fader::Update(float _DeltaTime)
{
	if (true == IsDeath())
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
	RenderPtr->Off();
	Death();
}
