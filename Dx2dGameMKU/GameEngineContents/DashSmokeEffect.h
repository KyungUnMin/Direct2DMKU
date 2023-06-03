#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;

class DashSmokeEffect : public GameEngineActor
{
public:
	DashSmokeEffect();
	~DashSmokeEffect() override;

	DashSmokeEffect(const DashSmokeEffect& _Other) = delete;
	DashSmokeEffect(DashSmokeEffect&& _Other) noexcept = delete;
	DashSmokeEffect& operator=(const DashSmokeEffect& _Other) = delete;
	DashSmokeEffect& operator=(const DashSmokeEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view FileName;
	static const float AniInter;
	static const float4 RenderScale;

	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;

	void ImageLoad();
	void CreateAnimation();
};

