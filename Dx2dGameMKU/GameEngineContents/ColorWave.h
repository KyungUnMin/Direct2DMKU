#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ColorWave : public GameEngineActor
{
public:
	ColorWave();
	~ColorWave() override;

	ColorWave(const ColorWave& _Other) = delete;
	ColorWave(ColorWave&& _Other) noexcept = delete;
	ColorWave& operator=(const ColorWave& _Other) = delete;
	ColorWave& operator=(const ColorWave&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	struct WaveData
	{
		float4 Color = float4::Zero;
		float Time = 0.0f;
		float Duration = 0.5f;
	};

	std::vector<std::pair<std::shared_ptr<class GameEngineRenderer>, WaveData>> Waves;
	int OffIndex = -1;
};

