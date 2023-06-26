#pragma once
#include "EnemyStateBase.h"

class NoiseState_Defeat : public EnemyStateBase
{
public:
	NoiseState_Defeat();
	~NoiseState_Defeat() override;

	NoiseState_Defeat(const NoiseState_Defeat& _Other) = delete;
	NoiseState_Defeat(NoiseState_Defeat&& _Other) noexcept = delete;
	NoiseState_Defeat& operator=(const NoiseState_Defeat& _Other) = delete;
	NoiseState_Defeat& operator=(const NoiseState_Defeat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const float AniInterTime;

	bool IsCrying = false;

	void LoadAnimation();
	void CreateAnimation();
};

