#include "PrecompileHeader.h"
#include "ShaderTestActor.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>

ShaderTestActor::ShaderTestActor()
{

}

ShaderTestActor::~ShaderTestActor()
{

}

void ShaderTestActor::Start()
{
	const float OffsetRange = 100.f;

	for (size_t i = 0; i < 10; ++i)
	{
		std::shared_ptr<GameEngineRenderer> RenedrPtr = CreateComponent<GameEngineRenderer>();
		RenedrPtr->SetPipeLine("EnterEffect");
		RenedrPtr->GetTransform()->SetLocalScale(float4::One * 100.f);
		RenedrPtr->GetShaderResHelper().SetConstantBufferLink("SqaureInfo", ShaderInfo);

		float4 Offset = float4::Zero;
		Offset.x = GameEngineRandom::MainRandom.RandomFloat(-OffsetRange, OffsetRange);
		Offset.y = GameEngineRandom::MainRandom.RandomFloat(-OffsetRange, OffsetRange);
		RenedrPtr->GetTransform()->SetLocalPosition(Offset);
	}

	

	GetTransform()->SetLocalPosition(float4::Down * 100.f);
}

void ShaderTestActor::Update(float _DeltaTime)
{

	ShaderInfo.Timer += _DeltaTime;
}
