#include "PrecompileHeader.h"
#include "BossVersus_PostProcessing.h"

#include "RCGDefine.h"

BossVersus_PostProcessing::BossVersus_PostProcessing()
{

}

BossVersus_PostProcessing::~BossVersus_PostProcessing()
{

}

void BossVersus_PostProcessing::Start(GameEngineRenderTarget* _Target)
{
	//���� ���� ����� �޽�, ����������, ������� ����
	RenderUnit = std::make_shared<GameEngineRenderUnit>();
	RenderUnit->SetMesh("FullRect");
	RenderUnit->SetPipeLine(RCGDefine::GetPipeName(PipeType::Burn));
	RenderUnit->ShaderResHelper.SetConstantBufferLink("NoiseFilter", CBufferData);


	//GarbageTrans.SetWorldPosition(float4::Zero);
	GarbageTrans.SetWorldScale(GameEngineWindow::GetScreenSize());
	RenderUnit->ShaderResHelper.SetConstantBufferLink("TransformData", GarbageTrans.GetTransDataRef());


	//���� Ÿ�� �����
	GameEnginePostProcess::ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}



void BossVersus_PostProcessing::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	if (false == Flag)
		return;

	if (false == Update_CalData(_DeltaTime))
		return;

	//������ �׷ȴ� ���빰 �����
	GameEnginePostProcess::ResultTarget->Clear();

	//�� ������ ī�޶� ��ϵǾ��� �ؽ�ó �޾Ƽ� �����ϱ�
	RenderUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	GameEnginePostProcess::ResultTarget->Setting();

	

	//���������� �̿��� �׸���
	RenderUnit->Render(_DeltaTime);
	RenderUnit->ShaderResHelper.AllResourcesReset();

	//ī�޶� �ִ� ���� ������ ����� ���� ������ ������ �׸���
	_Target->Clear();
	_Target->Merge(ResultTarget);
}


bool BossVersus_PostProcessing::Update_CalData(float _DeltaTime)
{
	Timer += _DeltaTime;
	float Ratio = (Timer / Duration);

	if (1.f < Ratio)
	{
		if (nullptr != CallBack)
		{
			CallBack();
			CallBack = nullptr;
		}

		Flag = false;
		return true;
	}

	CBufferData.NoiseFilterValue = (1.f - Ratio);
	return true;
}
