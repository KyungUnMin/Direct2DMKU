#pragma once
#include "EnemyState_DamagedBase.h"

class NoiseState_Damaged_Dizzy : public EnemyState_DamagedBase
{
public:
	NoiseState_Damaged_Dizzy();
	~NoiseState_Damaged_Dizzy() override;

	NoiseState_Damaged_Dizzy(const NoiseState_Damaged_Dizzy& _Other) = delete;
	NoiseState_Damaged_Dizzy(NoiseState_Damaged_Dizzy&& _Other) noexcept = delete;
	NoiseState_Damaged_Dizzy& operator=(const NoiseState_Damaged_Dizzy& _Other) = delete;
	NoiseState_Damaged_Dizzy& operator=(const NoiseState_Damaged_Dizzy&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const std::pair<size_t, size_t> AniFrameIndex;
	static const float AniInterTime;

	const float Duration = 1.5f;

	void LoadAnimation();
	void CreateAnimation();
};

