#pragma once
#include <GameEngineCore/GameEngineActor.h>


class OpeningDiaEffect : public GameEngineActor
{
public:
	OpeningDiaEffect();
	~OpeningDiaEffect() override;

	OpeningDiaEffect(const OpeningDiaEffect& _Other) = delete;
	OpeningDiaEffect(OpeningDiaEffect&& _Other) noexcept = delete;
	OpeningDiaEffect& operator=(const OpeningDiaEffect& _Other) = delete;
	OpeningDiaEffect& operator=(const OpeningDiaEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	float Timer = 0.f;
	const float Duration = 1.f;

	const float4 MaxScale = float4{ 64.f, 64.f };
	const float4 OffsetRange = float4{ 250.f, 100.f };

	void SetRandomOffset();
};


