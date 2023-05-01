#include "PrecompileHeader.h"
#include "ColorWave.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>


ColorWave::ColorWave()
{

}

ColorWave::~ColorWave()
{

}

void ColorWave::Start()
{
	const float4 WaveScale = float4{ 25.f, 150.f };
	Waves.reserve(50);
	for (size_t i = 0; i < Waves.capacity(); ++i)
	{
		std::pair<std::shared_ptr<GameEngineRenderer>, WaveData>& Pair = Waves.emplace_back();
		Pair.first = CreateComponent<GameEngineRenderer>();
		Pair.first->SetPipeLine("ColorWave");
		Pair.first->GetTransform()->SetLocalScale(WaveScale);
		Pair.first->GetShaderResHelper().SetConstantBufferLink("WaveData", Pair.second);

		Pair.second.Color = float4
		(
			GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.f),
			GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.f),
			GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.f)
		);

		const float FloatIndex = static_cast<float>(i);
		Pair.second.Duration += FloatIndex * 0.001f;

		const float OffsetX = 10.f;
		if (0 == (i % 2))
		{
			Pair.first->GetTransform()->SetLocalPosition(float4::Left * FloatIndex * OffsetX);
		}
		else
		{
			Pair.first->GetTransform()->SetLocalPosition(float4::Right * FloatIndex * OffsetX);
		}
	}

}

#include "KeyMgr.h"

void ColorWave::Update(float _DeltaTime)
{
	if (true == IsDeath())
		return;

	if (true == KeyMgr::IsDown(KeyNames::Space) && OffIndex < 0)
	{
		OffIndex = 0;
	}


	bool NowFrameOff = false;
	for (size_t i = 0; i < Waves.size(); ++i)
	{
		std::pair<std::shared_ptr<GameEngineRenderer>, WaveData>& WavePair = Waves[i];
		WavePair.second.Time += _DeltaTime;

		if (OffIndex < 0 || Waves.size() <= OffIndex || true == NowFrameOff)
			continue;

		Waves[OffIndex++].first->Off();
		NowFrameOff = true;
	}

	if (static_cast<int>(Waves.size()) == OffIndex)
	{
		Waves.clear();
		Death();
	}
}

