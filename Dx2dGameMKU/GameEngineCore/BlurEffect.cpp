#include "PrecompileHeader.h"
#include "BlurEffect.h"

BlurEffect::BlurEffect()
{
}

BlurEffect::~BlurEffect()
{
}

void BlurEffect::Start(GameEngineRenderTarget* _Target)
{
	BlurUnit = std::make_shared<GameEngineRenderUnit>();
	BlurUnit->SetMesh("FullRect");
	BlurUnit->SetPipeLine("Blur");

	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void BlurEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	//������ ����Ÿ�ٿ� �׷����� ���� ����
	ResultTarget->Clear();

	//ī�޶� ����Ÿ�ٿ� �׷��� �̹������� �ؽ�ó�� �޾� ���õȴ�
	BlurUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));

	//ResultTarget�� GPU�� ����
	ResultTarget->Setting();

	//�׸���
	BlurUnit->Render(_DeltaTime);

	//������ ���������ο��� VS, PS ������ �����Ѵ�
	BlurUnit->ShaderResHelper.AllResourcesReset();

	//�̹����� �޾ƿԴ� _Target�� ResultTarget�� ������ �ٽ� �׸���.
	_Target->Clear();
	_Target->Merge(ResultTarget);
}
