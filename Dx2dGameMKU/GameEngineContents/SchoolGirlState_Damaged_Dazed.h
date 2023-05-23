#pragma once
#include "EnemyState_DamagedBase.h"

class SchoolGirlState_Damaged_Dazed : public EnemyState_DamagedBase
{
public:
	SchoolGirlState_Damaged_Dazed();
	~SchoolGirlState_Damaged_Dazed() override;

	SchoolGirlState_Damaged_Dazed(const SchoolGirlState_Damaged_Dazed& _Other) = delete;
	SchoolGirlState_Damaged_Dazed(SchoolGirlState_Damaged_Dazed&& _Other) noexcept = delete;
	SchoolGirlState_Damaged_Dazed& operator=(const SchoolGirlState_Damaged_Dazed& _Other) = delete;
	SchoolGirlState_Damaged_Dazed& operator=(const SchoolGirlState_Damaged_Dazed&& _Other) noexcept = delete;

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

	const float Duration = 5.0f;

	void LoadAnimation();
	void CreateAnimation();
};

