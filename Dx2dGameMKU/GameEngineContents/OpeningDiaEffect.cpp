#include "PrecompileHeader.h"
#include "OpeningDiaEffect.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

OpeningDiaEffect::OpeningDiaEffect()
{

}

OpeningDiaEffect::~OpeningDiaEffect()
{

}

void OpeningDiaEffect::Start()
{
	RenderPtr = CreateComponent<GameEngineSpriteRenderer>();
	RenderPtr->SetTexture("fx_diamond01.png");
	SetRandomOffset();
}

void OpeningDiaEffect::Update(float _DeltaTime)
{
	Timer += _DeltaTime;

	if (Duration < Timer)
	{
		const float DelayTime = GameEngineRandom::MainRandom.RandomFloat(0.2f, 1.0f);
		Timer = -DelayTime;
		GameEngineTransform* RenderTrans = RenderPtr->GetTransform();
		RenderTrans->SetLocalScale(float4::Zero);

		SetRandomOffset();

		float NextAngle = GameEngineRandom::MainRandom.RandomFloat(-45.f, 45.f);
		RenderTrans->SetLocalRotation(float4::Forward * NextAngle);
	}

	if (Timer < 0.f)
		return;

	float TimeRatio = (Timer / Duration);
	float AngleRatio = sinf(TimeRatio * GameEngineMath::PIE);
	float ScaleRatio = (AngleRatio * 0.5f) + 0.5f;

	float4 NextScale = MaxScale * ScaleRatio;
	RenderPtr->GetTransform()->SetLocalScale(NextScale);
}

void OpeningDiaEffect::SetRandomOffset()
{
	float4 NextOffset = float4::Zero;
	NextOffset.x = GameEngineRandom::MainRandom.RandomFloat(-OffsetRange.x, OffsetRange.x);
	NextOffset.y = GameEngineRandom::MainRandom.RandomFloat(-OffsetRange.y, OffsetRange.y);
	RenderPtr->GetTransform()->SetLocalPosition(NextOffset);
}
