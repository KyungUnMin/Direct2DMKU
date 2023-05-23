#pragma once
#include "EnemyState_DamagedBase.h"

class SchoolBoyState_Damaged_Dazed : public EnemyState_DamagedBase
{
public:
	SchoolBoyState_Damaged_Dazed();
	~SchoolBoyState_Damaged_Dazed() override;

	SchoolBoyState_Damaged_Dazed(const SchoolBoyState_Damaged_Dazed& _Other) = delete;
	SchoolBoyState_Damaged_Dazed(SchoolBoyState_Damaged_Dazed&& _Other) noexcept = delete;
	SchoolBoyState_Damaged_Dazed& operator=(const SchoolBoyState_Damaged_Dazed& _Other) = delete;
	SchoolBoyState_Damaged_Dazed& operator=(const SchoolBoyState_Damaged_Dazed&& _Other) noexcept = delete;

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

