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
	//이전에 렌더타겟에 그려졌던 내용 정리
	ResultTarget->Clear();

	//카메라 렌더타겟에 그려진 이미지들을 텍스처로 받아 세팅된다
	BlurUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));

	//ResultTarget를 GPU에 세팅
	ResultTarget->Setting();

	//그리기
	BlurUnit->Render(_DeltaTime);

	//렌더링 파이프라인에서 VS, PS 세팅을 해제한다
	BlurUnit->ShaderResHelper.AllResourcesReset();

	//이미지를 받아왔던 _Target에 ResultTarget의 내용을 다시 그린다.
	_Target->Clear();
	_Target->Merge(ResultTarget);
}
