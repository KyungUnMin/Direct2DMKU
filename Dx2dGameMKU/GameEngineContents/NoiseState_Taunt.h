#pragma once
#include "EnemyStateBase.h"

class NoiseState_Taunt : public EnemyStateBase
{
public:
	NoiseState_Taunt();
	~NoiseState_Taunt() override;

	NoiseState_Taunt(const NoiseState_Taunt& _Other) = delete;
	NoiseState_Taunt(NoiseState_Taunt&& _Other) noexcept = delete;
	NoiseState_Taunt& operator=(const NoiseState_Taunt& _Other) = delete;
	NoiseState_Taunt& operator=(const NoiseState_Taunt&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

