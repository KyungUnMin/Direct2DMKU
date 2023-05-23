#pragma once
#include "EnemyState_WalkBase.h"

class SchoolBoyState_Walk : public EnemyState_WalkBase
{
public:
	SchoolBoyState_Walk();
	~SchoolBoyState_Walk() override;

	SchoolBoyState_Walk(const SchoolBoyState_Walk& _Other) = delete;
	SchoolBoyState_Walk(SchoolBoyState_Walk&& _Other) noexcept = delete;
	SchoolBoyState_Walk& operator=(const SchoolBoyState_Walk& _Other) = delete;
	SchoolBoyState_Walk& operator=(const SchoolBoyState_Walk&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

