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
	//렌더 유닛 만들고 메쉬, 파이프라인, 상수버퍼 연결
	RenderUnit = std::make_shared<GameEngineRenderUnit>();
	RenderUnit->SetMesh("FullRect");
	RenderUnit->SetPipeLine(RCGDefine::GetPipeName(PipeType::Burn));
	RenderUnit->ShaderResHelper.SetConstantBufferLink("NoiseFilter", CBufferData);


	//GarbageTrans.SetWorldPosition(float4::Zero);
	GarbageTrans.SetWorldScale(GameEngineWindow::GetScreenSize());
	RenderUnit->ShaderResHelper.SetConstantBufferLink("TransformData", GarbageTrans.GetTransDataRef());


	//렌더 타겟 만들기
	GameEnginePostProcess::ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}



void BossVersus_PostProcessing::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	if (false == Flag)
		return;

	if (false == Update_CalData(_DeltaTime))
		return;

	//이전에 그렸던 내용물 지우기
	GameEnginePostProcess::ResultTarget->Clear();

	//이 레벨의 카메라에 기록되었던 텍스처 받아서 세팅하기
	RenderUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	GameEnginePostProcess::ResultTarget->Setting();

	

	//렌더유닛을 이용해 그리기
	RenderUnit->Render(_DeltaTime);
	RenderUnit->ShaderResHelper.AllResourcesReset();

	//카메라에 있던 기존 내용은 지우고 렌더 유닛의 내용을 그리기
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
