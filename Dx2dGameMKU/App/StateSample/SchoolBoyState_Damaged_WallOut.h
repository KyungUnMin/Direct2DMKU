#pragma once
#include "EnemyState_DamagedBase.h"

class SchoolBoyState_Damaged_WallOut : public EnemyState_DamagedBase
{
public:
	SchoolBoyState_Damaged_WallOut();
	~SchoolBoyState_Damaged_WallOut() override;

	SchoolBoyState_Damaged_WallOut(const SchoolBoyState_Damaged_WallOut& _Other) = delete;
	SchoolBoyState_Damaged_WallOut(SchoolBoyState_Damaged_WallOut&& _Other) noexcept = delete;
	SchoolBoyState_Damaged_WallOut& operator=(const SchoolBoyState_Damaged_WallOut& _Other) = delete;
	SchoolBoyState_Damaged_WallOut& operator=(const SchoolBoyState_Damaged_WallOut&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	const float Duration = 0.3f;
	const float StartReflectSize = 700.f;

	void LoadAnimation();
	void CreateAnimation();
	void SetReflectDirection();
};

