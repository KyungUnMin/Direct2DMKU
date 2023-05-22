#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;

class HitEffect : public GameEngineActor
{
public:
	HitEffect();
	~HitEffect() override;

	HitEffect(const HitEffect& _Other) = delete;
	HitEffect(HitEffect&& _Other) noexcept = delete;
	HitEffect& operator=(const HitEffect& _Other) = delete;
	HitEffect& operator=(const HitEffect&& _Other) noexcept = delete;

	void SetDuration(float _Duration)
	{
		Duration = _Duration;
	}

	void OffHitSpark();


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view HitAir_FileName;
	static const std::string_view HitSpark_FileName;
	static const float4 AirMaxScale;
	static float4 SparkScale;


	std::shared_ptr<GameEngineSpriteRenderer> AirRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> SparkRender = nullptr;

	float Duration = 0.2f;


	void LoadImages();
	void CreateRenders();
};

