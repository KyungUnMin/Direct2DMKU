#include "PrecompileHeader.h"
#include "BurnExample.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "RCGDefine.h"

BurnExample::BurnExample()
{

}

BurnExample::~BurnExample()
{

}

void BurnExample::Start()
{
	/*const float4 RenderScale = float4{ 200.f, 300.f, 1.f };

	std::shared_ptr<GameEngineRenderer> Render1 = CreateComponent<GameEngineRenderer>();
	Render1->SetPipeLine("Burn");
	Render1->GetShaderResHelper().SetConstantBufferLink("NoiseFilter", Data);
	Render1->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, "RCG_Kyoko_idle0001_anio.png");
	Render1->GetTransform()->SetLocalScale(RenderScale);*/
}


void BurnExample::Update(float _DeltaTime)
{
	/*Timer += _DeltaTime;
	Data.NoiseFilterValue = abs(sinf(Timer));*/
}

