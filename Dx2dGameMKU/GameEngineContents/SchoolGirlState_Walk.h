#pragma once
#include "EnemyState_WalkBase.h"

class SchoolGirlState_Walk : public EnemyState_WalkBase
{
public:
	SchoolGirlState_Walk();
	~SchoolGirlState_Walk() override;

	SchoolGirlState_Walk(const SchoolGirlState_Walk& _Other) = delete;
	SchoolGirlState_Walk(SchoolGirlState_Walk&& _Other) noexcept = delete;
	SchoolGirlState_Walk& operator=(const SchoolGirlState_Walk& _Other) = delete;
	SchoolGirlState_Walk& operator=(const SchoolGirlState_Walk&& _Other) noexcept = delete;

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



