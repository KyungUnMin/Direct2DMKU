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



	//�ٸ������� ���̵尡 �������̶�� ��ٸ���
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

	//���� Death ����� ��� ��������� �������� ��� ����
	//���̵忡�� ȭ�� �����̴°� ���� ���� �ּ��ϸ� �ذ��
	//RenderPtr->Off();
	IsFading = nullptr;
	Death();
}
