#pragma once
#include "StateBase.h"

class GameEngineSpriteRenderer;

class BossVersusState_Fire : public StateBase
{
public:
	BossVersusState_Fire();
	~BossVersusState_Fire() override;

	BossVersusState_Fire(const BossVersusState_Fire& _Other) = delete;
	BossVersusState_Fire(BossVersusState_Fire&& _Other) noexcept = delete;
	BossVersusState_Fire& operator=(const BossVersusState_Fire& _Other) = delete;
	BossVersusState_Fire& operator=(const BossVersusState_Fire&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view Light_FileName;
	static const std::string_view Fire_FileName;

	const float4 FireArea = float4{ 100.f, 50.f };
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> Fires;
	std::shared_ptr<GameEngineSpriteRenderer> Light = nullptr;

	const float4 LightMaxScale = float4{ 720.f, 720.f };
	const float LightDuration = 0.5f;

	void LoadFireAniSprite();
	void CreateRenderers();
};

