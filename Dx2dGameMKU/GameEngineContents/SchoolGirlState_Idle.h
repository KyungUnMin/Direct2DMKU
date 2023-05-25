#pragma once
#include "EnemyState_IdleBase.h"

 class SchoolGirlState_Idle : public EnemyState_IdleBase
{
public:
	SchoolGirlState_Idle();
	~SchoolGirlState_Idle() override;

	SchoolGirlState_Idle(const SchoolGirlState_Idle& _Other) = delete;
	SchoolGirlState_Idle(SchoolGirlState_Idle&& _Other) noexcept = delete;
	SchoolGirlState_Idle& operator=(const SchoolGirlState_Idle& _Other) = delete;
	SchoolGirlState_Idle& operator=(const SchoolGirlState_Idle&& _Other) noexcept = delete;

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

