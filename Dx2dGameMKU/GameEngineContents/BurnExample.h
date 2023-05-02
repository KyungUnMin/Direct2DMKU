#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BurnExample : public GameEngineActor
{
public:
	BurnExample();
	~BurnExample() override;

	BurnExample(const BurnExample& _Other) = delete;
	BurnExample(BurnExample&& _Other) noexcept = delete;
	BurnExample& operator=(const BurnExample& _Other) = delete;
	BurnExample& operator=(const BurnExample&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	struct BurnShaderData
	{
		float NoiseFilterValue = 0.f;
		const float NoiseImageScale = 5.f;
		const float Garbage1 = 0.f;
		const float Garbage2 = 0.f;
	};

	BurnShaderData Data;
	float Timer = 0.f;
};

