#pragma once
#include "EnemyState_DamagedBase.h"

class SchoolGirlState_Damaged_WallHit : public EnemyState_DamagedBase
{
public:
	SchoolGirlState_Damaged_WallHit();
	~SchoolGirlState_Damaged_WallHit() override;

	SchoolGirlState_Damaged_WallHit(const SchoolGirlState_Damaged_WallHit& _Other) = delete;
	SchoolGirlState_Damaged_WallHit(SchoolGirlState_Damaged_WallHit&& _Other) noexcept = delete;
	SchoolGirlState_Damaged_WallHit& operator=(const SchoolGirlState_Damaged_WallHit& _Other) = delete;
	SchoolGirlState_Damaged_WallHit& operator=(const SchoolGirlState_Damaged_WallHit&& _Other) noexcept = delete;

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

	const float Duration = 0.15f;

	void LoadAnimation();
	void CreateAnimation();
};

