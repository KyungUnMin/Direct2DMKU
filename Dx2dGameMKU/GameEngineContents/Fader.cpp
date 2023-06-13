#include "PrecompileHeader.h"
#include "Fader.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "RCGDefine.h"
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
	RenderPtr->SetMesh("Rect");
	RenderPtr->SetPipeLine(RCGDefine::GetPipeName(PipeType::DirectColor));
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

	

	IsFading = nullptr;

	if (true == IsDestroy)
	{
		Death();
	}
}

void Fader::ClearOthers()
{
	const std::list<std::shared_ptr<GameEngineActor>>& UIGroup = GetLevel()->GetActorGroup(UpdateOrder::UI);

	for (std::shared_ptr<GameEngineActor> UIActor : UIGroup)
	{
		std::shared_ptr<Fader> FaderPtr = std::dynamic_pointer_cast<Fader>(UIActor);
		if (nullptr == FaderPtr)
			continue;

		if (FaderPtr.get() == this)
			continue;

		FaderPtr->Death();
	}
}
