#include "PrecompileHeader.h"
#include "GlichSideAttack.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

GlichSideAttack::GlichSideAttack()
{

}

GlichSideAttack::~GlichSideAttack()
{

}

void GlichSideAttack::Start()
{
	const float4 RenderScale = float4{ 550.f, 180.f, 1.f };

	std::shared_ptr<GameEngineRenderer> Render1 = CreateComponent<GameEngineRenderer>(FieldRenderOrder::ZOrder);
	Render1->SetMesh("Rect");
	Render1->SetPipeLine(RCGDefine::GetPipeName(PipeType::GlichStair));
	Render1->GetShaderResHelper().SetConstantBufferLink("GlichData", Data);
	Render1->GetTransform()->SetLocalScale(RenderScale);
	Render1->GetTransform()->AddLocalPosition(float4::Left * RenderScale.hx());

	std::shared_ptr<GameEngineRenderer> Render2 = CreateComponent<GameEngineRenderer>(FieldRenderOrder::ZOrder);
	Render2->SetMesh("Rect");
	Render2->SetPipeLine(RCGDefine::GetPipeName(PipeType::GlichStair));
	Render2->GetShaderResHelper().SetConstantBufferLink("GlichData", Data);
	Render2->GetTransform()->SetLocalScale(RenderScale * float4{ -1.f, 1.f, 1.f });
	Render2->GetTransform()->AddLocalPosition(float4::Right * RenderScale.hx());
}


void GlichSideAttack::Update(float _DeltaTime)
{
	Data.Timer += _DeltaTime;

	if (false == WaveOffValue)
		return;

	DecreaseTimer += _DeltaTime;

	float Ratio = (DecreaseTimer / DecreseDuration);
	if (1.f < Ratio)
	{
		Death();
		return;
	}

	Data.MaxWaveHeight = (1.f - Ratio);
}

