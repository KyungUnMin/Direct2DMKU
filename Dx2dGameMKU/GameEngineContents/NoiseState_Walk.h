#pragma once
#include "EnemyState_WalkBase.h"

class NoiseState_Walk : public EnemyState_WalkBase
{
public:
	NoiseState_Walk();
	~NoiseState_Walk() override;

	NoiseState_Walk(const NoiseState_Walk& _Other) = delete;
	NoiseState_Walk(NoiseState_Walk&& _Other) noexcept = delete;
	NoiseState_Walk& operator=(const NoiseState_Walk& _Other) = delete;
	NoiseState_Walk& operator=(const NoiseState_Walk&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;

	bool ChangeStateWhenFarWithAwayPlayer() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	class BossFSMBase* BossFsmPtr = nullptr;

	void LoadAnimation();
	void CreateAnimation();
};

