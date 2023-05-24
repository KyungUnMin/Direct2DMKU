#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;

class AfterImageEffect : public GameEngineActor
{
public:
	AfterImageEffect();
	~AfterImageEffect() override;

	AfterImageEffect(const AfterImageEffect& _Other) = delete;
	AfterImageEffect(AfterImageEffect&& _Other) noexcept = delete;
	AfterImageEffect& operator=(const AfterImageEffect& _Other) = delete;
	AfterImageEffect& operator=(const AfterImageEffect&& _Other) noexcept = delete;

	void Init(std::shared_ptr<GameEngineSpriteRenderer> _OwnerRender);

protected:
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> EffectRender = nullptr;
	float4 AtlasData = float4::Zero;

	const float AlphaRatio = 0.5f;
	const float Duration = 0.2f;
};

