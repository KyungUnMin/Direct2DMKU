#pragma once
#include "EnemyState_DamagedBase.h"

class NoiseState_NormalDamaged_Face : public EnemyState_DamagedBase
{
public:
	NoiseState_NormalDamaged_Face();
	~NoiseState_NormalDamaged_Face() override;

	NoiseState_NormalDamaged_Face(const NoiseState_NormalDamaged_Face& _Other) = delete;
	NoiseState_NormalDamaged_Face(NoiseState_NormalDamaged_Face&& _Other) noexcept = delete;
	NoiseState_NormalDamaged_Face& operator=(const NoiseState_NormalDamaged_Face& _Other) = delete;
	NoiseState_NormalDamaged_Face& operator=(const NoiseState_NormalDamaged_Face&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::pair<int, int> AniCutFrame;
	static const std::pair<size_t, size_t> AniFrameIndex;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

